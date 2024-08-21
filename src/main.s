.gba
.thumb
.open "./BPRE0.gba","./multi.gba", 0x08000000

.org 0x806F282
.thumb
.align 2
LDR r0, =input_handler|1
BX r0
.pool


.org 0x08810000



.importobj "./build/linked.o"

.word super, 0x030030F0
input_handler:
	LDR r0, =super
	LDRH r1, [r0, 0x2E]
	MOV r0, 4
	AND r0, r1
	CMP r0, #0
	BEQ back_to_normal
	BL goto_menu
	B goto_0806F358
	
back_to_normal:
	LDR r0, =super
	LDRH r1, [r0, 0x2E]
	LDR r0, =0x40
	AND r0, r1
	CMP r0, #0
	
	BEQ goto_0806F2D2
	LDR r0, =0x0806F28D
	BX r0
	
goto_menu:
	LDR r0, =sm_poketools|1
	BX r0
	
goto_0806F358:
	LDR r0, =0x0806F359
	BX r0
	
goto_0806F2D2:
	LDR r0, =0x0806F2D3
	BX r0

.pool

.close
