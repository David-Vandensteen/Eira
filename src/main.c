#include <stdlib.h>
#include <video.h>
#include <input.h>
//#include <cddactrl.h>
#include <math.h>
#include "neo_core.h"
#include "neo_db.h"
#include "logoEffect.h"
#include "neo_texter.h"
#include "snowField.h"
#include "triangles.h"
#include "backdropcolor.h"

#define itofix(value)	value * FIXEDCOEF

#define TRIANGLES_ON
#define LOGO
#define TEXT_ON
#define SNOW
//#define TEXTERDB_ON
//#define STEPDB_ON

typedef struct Triangle Triangle;
struct Triangle {
	TILEMAP *tilemap;
	int id;
	int x;
	int zoom_yz;
	int zoom_polarity;
	WORD clipping;
	FIXED y;
};

extern PALETTE	palettes[];
extern TILEMAP  triangle03down, triangle03up, triangle02down, triangle02up, triangle01down, triangle01up;

static Triangle triangles[6];

static void triangle_init(
		Triangle *triangle,
		int x,
		FIXED y,
		int clipping,
		const TILEMAP *tilemap
	) {
	triangle->zoom_yz = 0xFF;
	triangle->id = write_sprite_data(x, fixtoi(y) , 0xF, triangle->zoom_yz, clipping, tileSizeNB(512), (const PTILEMAP)tilemap);
	triangle->x = x;
	triangle->y = y;
	triangle->clipping = clipping;
	triangle->zoom_polarity= 0xF;
}

static void triangles_init() {
	triangle_init(&triangles[0], 0, 0, tileSizeClipping(48), (const PTILEMAP)&triangle03up);
	triangle_init(&triangles[1], 0, 0, tileSizeClipping(32), (const PTILEMAP)&triangle02up);
	triangle_init(&triangles[2], 0, 0, tileSizeClipping(16), (const PTILEMAP)&triangle01up);

	triangle_init(&triangles[3], 0, itofix(176), tileSizeClipping(48), (const PTILEMAP)&triangle03down);
	triangle_init(&triangles[4], 0, itofix(192), tileSizeClipping(32), (const PTILEMAP)&triangle02down);
	triangle_init(&triangles[5], 0, itofix(208), tileSizeClipping(16), (const PTILEMAP)&triangle01down);
}

static void triangle_move(Triangle *triangle, int x) {
	change_sprite_pos(triangle->id, x, triangle->y, triangle->clipping);
	triangle->x = x;
}

static void triangles_move() {
	int x = triangles[0].x += 1;
	triangle_move(&triangles[0], x);
}

void init() {

}

int main(void){
    /* DECLARATION */
	logoZoomEffect logoZoomEffect;
	snowField snowFieldBig, snowFieldMedium, snowFieldLittle;
	WORD sinText = 0;
	WORD sinLogo = 0;
	WORD backdropColorIndex = 0;

	#ifdef TEXT_ON
	texter text;
	#endif

	#ifdef TRIANGLES_ON
	// TRIANGLE01U_INIT
	// TRIANGLE02U_INIT
	// TRIANGLE03U_INIT
	// TRIANGLE01D_INIT
	// TRIANGLE02D_INIT
	// TRIANGLE03D_INIT
	#endif

    /* INIT */
	// playcdda();
	setpalette(0, 60, (const PPALETTE)&palettes);
	backdropColorNext(&backdropColorIndex);

	logoZoomEffect = logoZoomEffectMake(0,75,2);
	set_current_sprite(3);

	/* INIT SPRITE & STRUCT SPRITE */
	/*	SNOW */
	#ifdef SNOW
	snowFieldBig = snowFieldMake(1);
	#endif

	#ifdef LOGO
	logoZoomEffect.spriteId = get_current_sprite();
	logoZoomEffectUpdate(&logoZoomEffect, sinLogo);
	#endif

	#ifdef SNOW
	snowFieldLittle = snowFieldMake(3);
	snowFieldMedium = snowFieldMake(2);
	#endif

	#ifdef TRIANGLES_ON

	triangles_init();
	/*
	triangle03U_id = write_sprite_data(0, 0, 15, 255, tileSizeClipping(48), tileSizeNB(512), (const PTILEMAP)&triangle03up);
	triangle02U_id = write_sprite_data(0, 0, 15, 255, tileSizeClipping(32), tileSizeNB(512), (const PTILEMAP)&triangle02up);
	triangle01U_id = write_sprite_data(0, 0, 15, 255, tileSizeClipping(16), tileSizeNB(512), (const PTILEMAP)&triangle01up);
	triangle03D_id = write_sprite_data(0, (FIXED)triangle03D_y, 15, 255, tileSizeClipping(48), tileSizeNB(512), (const PTILEMAP)&triangle03down);
	triangle02D_id = write_sprite_data(0, (FIXED)triangle02D_y, 15, 255, tileSizeClipping(32), tileSizeNB(512), (const PTILEMAP)&triangle02down);
	triangle01D_id = write_sprite_data(0, (FIXED)triangle01D_y, 15, 255, tileSizeClipping(16), tileSizeNB(512), (const PTILEMAP)&triangle01down);
	*/

	#endif

	#ifdef TEXT_ON
	#define TEXT00 "*** THE BOYS FROM RSE BACK ONCE AGAIN ***  THIS TIME ON THE MIGHTY NEO GEO CD! ENJOY THIS LITTLE ONE SCRENER, NOW GO MAKE ONE YOURSELF FOR THIS BEAUTIFUL PLATFORM ***                       * TEXT * 4PLAY                            * GRAPHICS AND DESIGN * GRASS        * CODE AND MUSIC * NAINAIN           GRASS SEND A PERSONNAL GREETING TO NEO-GEO.HU * THE HUNGARIAN NEO-GEO COMMUNITY.                                              "
	text = texter8Make(TEXT00, vec2intMake(328,100));
	#endif

	while(1){
		wait_vbl();
		#ifdef TRIANGLES_ON
		triangles_move();
		// triangle01Dmove(triangle01D_id, &triangle01D_x, &triangle01D_y, &triangle01D_yz, &triangle01D_zoomPol);
		// triangle02Dmove(triangle02D_id, &triangle02D_x, &triangle02D_y, &triangle02D_yz, &triangle02D_zoomPol);
		// triangle03Dmove(triangle03D_id, &triangle03D_x, &triangle03D_y, &triangle03D_yz, &triangle03D_zoomPol);

		// triangle01Umove(triangle01U_id, &triangle01U_x, &triangle01U_yz, &triangle01U_zoomPol);
		// triangle02Umove(triangle02U_id, &triangle02U_x, &triangle02U_yz, &triangle02U_zoomPol);
		// triangle03Umove(triangle03U_id, &triangle03U_x, &triangle03U_yz, &triangle03U_zoomPol);
		#endif

		//texter sin
		#ifdef TEXT_ON
		if (_vbl_count % 2 == 0){
			sinText++;
		}
		#endif
		#ifdef SNOW
		if(_vbl_count > 80){
			snowFieldUpdate(&snowFieldBig);
			snowFieldUpdate(&snowFieldMedium);
			snowFieldUpdate(&snowFieldLittle);
		}
		#endif

		#ifdef LOGO
		logoZoomEffectUpdate(&logoZoomEffect, sinLogo);
		#endif

		//BACKDROP COLOR
		if (backdropColorIndex <= 15 && _vbl_count % 20 == 0){
			backdropColorNext(&backdropColorIndex);
		}

		#ifdef TEXT_ON
		if (_vbl_count > 200) {
			texter8SinScrollEffect(&text, sinText);
			#ifdef TEXTERDB_ON
			texter8SinScrollEffectDebug(text);
			#endif
		}
		if(_vbl_count % 4200 == 0) { // TEXT RESTART
			text.headPlaySpr = 0;
			text.headPlayStr = 0;
			text.isComplete = 0;
		}
		#endif
		#ifdef LOGO
		sinLogo++;
		#endif

		#ifdef STEPDB_ON
		vblStepByStepUpdate(&vblSbS);
		#endif
	}
}
