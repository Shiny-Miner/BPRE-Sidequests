
//{{BLOCK(gui)

//======================================================================
//
//	gui, 256x160@4, 
//	Transparent color : 00,00,00
//	+ palette 14 entries, lz77 compressed
//	+ 77 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x20 
//	Total size: 28 + 796 + 324 = 1148
//
//	Time-stamp: 2021-01-18, 22:58:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GUI_H
#define GRIT_GUI_H

#define guiTilesLen 796
extern const unsigned char guiTiles[796];

#define guiMapLen 324
extern const unsigned short guiMap[162];

#define guiPalLen 28
extern const unsigned char guiPal[28];

#endif // GRIT_GUI_H

//}}BLOCK(gui)
