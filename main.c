#include <stdlib.h>
#include <video.h>
#include <input.h>
#include <cddactrl.h>
#include <math.h>
#include "neo_core.h"
#include "neo_db.h"
#include "logoEffect.h"
#include "neo_texter.h"
#include "snowField.h"
#include "triangles.h"
#include "backdropcolor.h"

//#define TRIANGLES_ON
//#define LOGO
//#define TEXT_ON
//#define SNOW
#define STEPDB_ON


extern PALETTE	palettes[];
extern TILEMAP  triangle03down, triangle03up, triangle02down, triangle02up, triangle01down, triangle01up;

int main(void){
    /* DECLARATION */
	#ifdef STEPDB_ON
	vblStepByStep vblSbS;
	#endif
	logoZoomEffect logoZoomEffect;
	snowField snowFieldBig, snowFieldMedium, snowFieldLittle;
	WORD sinText = 0;
	WORD sinLogo = 0;
	WORD backdropColorIndex = 0;

    #ifdef TEXT_ON
    texter text;
    #endif

	#ifdef TRIANGLES_ON
	TRIANGLE01U_INIT
	TRIANGLE02U_INIT
	TRIANGLE03U_INIT
	TRIANGLE01D_INIT
	TRIANGLE02D_INIT
	TRIANGLE03D_INIT
	#endif

    /* INIT */
	playcdda();
	setpalette(0, 60, (const PPALETTE)&palettes);	
	backdropColorNext(&backdropColorIndex);

	#ifdef STEPDB_ON
	vblSbS = vblStepByStepMake();
	#endif
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
	triangle03U_id = write_sprite_data(0, 0, 15, 255, tileSizeClipping(48), tileSizeNB(512), (const PTILEMAP)&triangle03up);
	triangle02U_id = write_sprite_data(0, 0, 15, 255, tileSizeClipping(32), tileSizeNB(512), (const PTILEMAP)&triangle02up);
	triangle01U_id = write_sprite_data(0, 0, 15, 255, tileSizeClipping(16), tileSizeNB(512), (const PTILEMAP)&triangle01up);
	triangle03D_id =  write_sprite_data(0, (FIXED)triangle03D_y, 15, 255, tileSizeClipping(48), tileSizeNB(512), (const PTILEMAP)&triangle03down);
	triangle02D_id =  write_sprite_data(0, (FIXED)triangle02D_y, 15, 255, tileSizeClipping(32), tileSizeNB(512), (const PTILEMAP)&triangle02down);
	triangle01D_id =  write_sprite_data(0, (FIXED)triangle01D_y, 15, 255, tileSizeClipping(16), tileSizeNB(512), (const PTILEMAP)&triangle01down);
	#endif

	#ifdef TEXT_ON
	//#define TEXT00 "** NEO GEO CD INTRO RELEASED BY RESISTANCE ** MUSIC AND CODE NAINAIN ** GRAPHICS AND DESIGN GRASS THIS IS OUR FIRST RELEASE IN NEO GEO SCENE WWW.RESISTANCE.NO ENJOY!                                           "
	//FIX a texter bug ... a strange space between c & ouleurs
	#define TEXT00 "LES TILES DU FIX NE PEUVENT UTILISER QUE LES PALETTES 0 A 15, SOIT LES 256 PREMIERES COULEURS …   **LES SPRITES PEUVENT UTILISER TOUTES LES PALETTE 0 A 255, SOIT TOUTES LES 4096 COULEURS.                                                         "
	text = texter8Make(TEXT00, vec2intMake(328,100));
	#endif
	while(1){
		wait_vbl();
		#ifdef TRIANGLES_ON
		triangle01Dmove(triangle01D_id, &triangle01D_x, &triangle01D_y, &triangle01D_yz, &triangle01D_zoomPol);
		triangle02Dmove(triangle02D_id, &triangle02D_x, &triangle02D_y, &triangle02D_yz, &triangle02D_zoomPol);
		triangle03Dmove(triangle03D_id, &triangle03D_x, &triangle03D_y, &triangle03D_yz, &triangle03D_zoomPol);

		triangle01Umove(triangle01U_id, &triangle01U_x, &triangle01U_yz, &triangle01U_zoomPol);
		triangle02Umove(triangle02U_id, &triangle02U_x, &triangle02U_yz, &triangle02U_zoomPol);
		triangle03Umove(triangle03U_id, &triangle03U_x, &triangle03U_yz, &triangle03U_zoomPol);
		#endif
		
		#ifdef SNOW
		snowFieldUpdate(&snowFieldBig);
		snowFieldUpdate(&snowFieldMedium);
		snowFieldUpdate(&snowFieldLittle);
		#endif
		
		/* VBL CONDITIONS */
		//texter sin
		#ifdef TEXT_ON
		if (_vbl_count % 2 == 0){
			sinText++;
		}
		#endif

		#ifdef LOGO
		logoZoomEffectUpdate(&logoZoomEffect, sinLogo);
		#endif

		//BACKDROP COLOR 
		if (backdropColorIndex <= 15 && _vbl_count % 5 == 0){
			backdropColorNext(&backdropColorIndex);
		}
		
		#ifdef TEXT_ON
		if (_vbl_count > 200) {
			texter8SinScrollEffect(&text, sinText);
			//texter8SinScrollEffectDebug(text);
		}
		if(_vbl_count % 2000 == 0) { // TEXT RESTART
			text.headPlaySpr = 0;
			text.headPlayStr = 0;
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
