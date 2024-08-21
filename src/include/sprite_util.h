#ifndef SPRITE_UTIL_H
#define SPRITE_UTIL_H

#include <pokeagb/pokeagb.h>
#include "oam_pal_table.h"
#include "oam_table.h"

extern void gpu_tile_obj_decompress_alloc_tag_and_upload_small_decompression_buffer(struct SpriteTiles* tile);

extern u8 display_sprite(u8 sprite_w, u8 sprite_h, u8 sprite_x, u8 sprite_y,
					u16 tiles_tag, void *ptr_to_tile,
					u16 pals_tag,  void *ptr_to_pal,
					u8 filp_h, u8 flip_v);



extern u8 display_compressed_sprite(u8 sprite_w, u8 sprite_h, u8 sprite_x, u8 sprite_y,
								u16 tiles_tag, void *ptr_to_tile,
								u16 pals_tag,  void *ptr_to_pal,
								u8 filp_h, u8 flip_v);

extern u8 display_npc(u8 oam_id, u8 sprite_x, u8 sprite_y, u8 tiles_tag);

#endif