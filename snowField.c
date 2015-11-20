#include <stdlib.h>
#include <video.h>
#include <input.h>
#include "neo_core.h"
#include "snowField.h"

#define XSCREEN_OFFSET 120
#define YSCREEN_OFFSET 224
extern TILEMAP snow;

snowField snowFieldMake(WORD type){
	WORD i = 0;
	snowField r;
	r.type = type;
	
	if (type == 1){ // BIG
		r.spriteQty = SNOWBIG_QTY;
		for (i = 0; i < SNOWBIG_QTY; i++){
			r.sprs[i] = sprMake(
				get_current_sprite(),
				vec2intMake((RAND320)-XSCREEN_OFFSET, RAND224 - YSCREEN_OFFSET),
				vec2intMake(1, 1 + rand() % 1), //
				vec2u16Make(16, 16),
				4 + rand() % 2 , //4
				vec2u16Make(15, 255),
				vec2intMake(-1, 0),
				10
				);
			write_sprite_data_nn(r.sprs[i], (const PTILEMAP)&snow);
		}
	}
	if (type == 2){ // medium
		r.spriteQty = SNOWMEDIUM_QTY;
		for (i = 0; i < SNOWMEDIUM_QTY; i++){
			r.sprs[i] = sprMake(
				get_current_sprite(),
				vec2intMake((RAND320)-XSCREEN_OFFSET, RAND224 - YSCREEN_OFFSET),
				vec2intMake(1, 1 + rand() % 1), //
				vec2u16Make(16, 16),
				2 + rand() % 5, //2
				vec2u16Make(7, 128),
				vec2intMake(-1, 0),
				6
				);
			write_sprite_data_nn(r.sprs[i], (const PTILEMAP)&snow);
		}
	}
		if (type == 3){ // little
			r.spriteQty = SNOWLITTLE_QTY;
			for (i = 0; i < SNOWLITTLE_QTY; i++){
				r.sprs[i] = sprMake(
					get_current_sprite(),
					vec2intMake((RAND320)-XSCREEN_OFFSET, RAND224 - YSCREEN_OFFSET),
					vec2intMake(1, 1 + rand() % 1), //
					vec2u16Make(16, 16),
					3 + rand() % 2, //0
					vec2u16Make(5, mapTo_yz(5)),
					vec2intMake(-1, 0),
					3
					);
				write_sprite_data_nn(r.sprs[i], (const PTILEMAP)&snow);
			}
		}
	return r;
}

void snowFieldUpdate(snowField *sf){
	WORD i = 0;
	for (i = 0; i < sf->spriteQty; i++){
		if (sf->sprs[i].pos.x > 320 || sf->sprs[i].pos.y > 170){
			sf->sprs[i].pos.x = (RAND320) - XSCREEN_OFFSET;
			sf->sprs[i].pos.y = 0;
		}
		sprUpdate(&sf->sprs[i]);
		switch (sf->type) {
			case 1:
				sprZoomEffectPingPong(&sf->sprs[i], 15, 7);
				break;
			case 2:
				sprZoomEffectPingPong(&sf->sprs[i], 7, 3);
				break;
			case 3:
				sprZoomEffectPingPong(&sf->sprs[i], 5, 2);
				break;
				
			default:
				break;
		}
	}
}
