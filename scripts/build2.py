#!/usr/bin/env python
 
from glob import glob
import os
import itertools
import hashlib
import subprocess
import sys

PATH = 'C:/devkitPro/devkitPro/devkitARM/bin'
PREFIX = '/arm-none-eabi-'
AS = (PATH + PREFIX + 'as')
CC = (PATH + PREFIX + 'gcc')
LD = (PATH + PREFIX + 'ld')
OBJCOPY = (PATH + PREFIX + 'objcopy')
SRC = './src'
BUILD = './build'
ASFLAGS = ['-mthumb']
LDFLAGS = ['-z','muldefs','-T', 'linker.ld', '-T', 'BPRE.ld', '-r']
CFLAGS= ['-Isrc/include', '-mthumb', '-mno-thumb-interwork', '-mcpu=arm7tdmi',
         '-fno-inline', '-mlong-calls', '-march=armv4t', '-fno-builtin', '-Wall', '-O2']
 
def run_command(cmd):
    try:
        subprocess.check_output(cmd)
    except subprocess.CalledProcessError as e:
        print(e.output.decode(), file=sys.stderr)
        sys.exit(1)
 
def make_output_file(filename):
    '''Return hash of filename to use as object filename'''
    m = hashlib.md5()
    m.update(filename.encode())
    #print("AAAAAAAAAAAAAAA " + filename + " = " + m.hexdigest())
    return os.path.join(BUILD, m.hexdigest() + '.o')
 
def process_assembly(in_file):
    '''Assemble'''
    out_file = make_output_file(in_file)
    cmd = [AS] + ASFLAGS + ['-c', in_file, '-o', out_file]
    run_command(cmd)
    return out_file
 
def process_c(in_file):
    '''Compile C'''
    out_file = make_output_file(in_file)
    cmd = [CC] + CFLAGS + ['-c', in_file, '-o', out_file]
    run_command(cmd)
    return out_file
 
def link(objects):
    '''Link objects into one binary'''
    linked = 'build/linked.o'
    cmd = [LD] + LDFLAGS + ['-o', linked] + list(objects)
    #print(cmd)
    run_command(cmd)
    return linked
 
def objcopy(binary):
    cmd = [OBJCOPY, '-O', 'binary', binary, 'build/output.bin']
    run_command(cmd)
 
def run_glob(globstr, fn):
    '''Glob recursively and run the processor function on each file in result'''
    files = glob(os.path.join(SRC, globstr), recursive=True)
    return map(fn, files)
 
def main():
    globs = {
        #'**/*.s': process_assembly,
        '**/*.c': process_c
    }
	
 
    # Create output directory
    try:
        os.makedirs(BUILD)
    except FileExistsError:
        pass
 
    # Gather source files and process them
    objects = itertools.starmap(run_glob, globs.items())
 
    # Link and extract raw binary
    linked = link(itertools.chain.from_iterable(objects))
    objcopy(linked)
	
	#ARMPIS
    cmd = ['armips', './src/main.s','-sym','symbols.txt']
    run_command(cmd)
 
if __name__ == '__main__':
    main()
