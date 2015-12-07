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

#define TRIANGLES
#define LOGO
#define TEXT_ON
#define SNOW
#define STEPDB_ON


extern PALETTE	palettes[];
extern TILEMAP  triangle03down, triangle03up, triangle02down, triangle02up, triangle01down, triangle01up;

static void trianglesDownEffect(spr *triangle01, spr *triangle02, spr *triangle03){
	if (triangle02->zoom.y >= 250){
		triangle03->zoomInc.y = -2; //-2
		triangle02->zoomInc.y = -2; //-2
		triangle01->zoomInc.y = -1; //-3
	}
	if (triangle02->zoom.y <= 141){//1 //140 //130
		triangle03->zoomInc.y = 2; // 2
		triangle02->zoomInc.y = 2; // 2
		triangle01->zoomInc.y = 1; // 3
	}
}
static void trianglesUpEffect(spr *triangle01, spr *triangle02, spr *triangle03){
	if (triangle01->zoom.y >= 250){
		triangle03->zoomInc.y = -2;
		triangle02->zoomInc.y = -2;
		triangle01->zoomInc.y = -3;
	}
	if (triangle01->zoom.y <= 1){
		triangle03->zoomInc.y = 2;
		triangle02->zoomInc.y = 2;
		triangle01->zoomInc.y = 3;
	}
}
int main(void){
    /* DECLARATION */
	#ifdef STEPDB_ON
	vblStepByStep vblSbS;
	#endif
	logoZoomEffect logoZoomEffect;
	spr triangle03downSpr, triangle03upSpr, triangle02downSpr, triangle02upSpr, triangle01downSpr, triangle01upSpr;
	snowField snowFieldBig, snowFieldMedium, snowFieldLittle;
	WORD sinText = 0;
	WORD sinLogo = 0;

    #ifdef TEXT_ON
    texter text;
    #endif
	
    /* INIT */
	playcdda();
	setpalette(0, 60, (const PPALETTE)&palettes);	
	asm("move #0x1157,0x401FFE"); //background color //136
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
	
	/*	TRIANGLE03UP SPRITE	 - AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle03upSpr = sprMakeDefault(get_current_sprite());
	triangle03upSpr.pos.y = 0;
	triangle03upSpr.posInc.x--;
	triangle03upSpr.vblSkipTranslation = 15;
	triangle03upSpr.size = vec2u16Make(512, 48); //512, 48
	write_sprite_data_nn(triangle03upSpr, (const PTILEMAP)&triangle03up);
	#endif
	
	/* TRIANGLE02UP SPRITE	- AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle02upSpr = sprMakeDefault(get_current_sprite());
	triangle02upSpr.pos.y = 0;
	triangle02upSpr.posInc.x--;
	triangle02upSpr.vblSkipTranslation = 10;
	triangle02upSpr.size = vec2u16Make(512, 32);
	write_sprite_data_nn(triangle02upSpr, (const PTILEMAP)&triangle02up);
	#endif
	
	/*	TRIANGLE01UP SPRITE	- AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle01upSpr = sprMakeDefault(get_current_sprite());
	triangle01upSpr.pos.y = 0;
	triangle01upSpr.posInc.x--;
	triangle01upSpr.vblSkipTranslation = 5;
	triangle01upSpr.size = vec2u16Make(512, 16);
	write_sprite_data_nn(triangle01upSpr, (const PTILEMAP)&triangle01up);
	#endif
	
	/*	TRIANGLE03DOWN SPRITE	- AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle03downSpr = sprMakeDefault(get_current_sprite());
	triangle03downSpr.pos.y = 196; 
	triangle03downSpr.posInc.x--;
	triangle03downSpr.vblSkipTranslation = 15;
	triangle03downSpr.size = vec2u16Make(512,48);
	write_sprite_data_nn(triangle03downSpr, (const PTILEMAP)&triangle03down);
	#endif
	
	/*	TRIANGLE02DOWN SPRITE - AUTOMOVE			*/
	#ifdef TRIANGLES
	triangle02downSpr = sprMakeDefault(get_current_sprite());
	triangle02downSpr.pos.y = 207; //208
	triangle02downSpr.posInc.x--;
	triangle02downSpr.vblSkipTranslation = 10;
	triangle02downSpr.size = vec2u16Make(512, 32);
	write_sprite_data_nn(triangle02downSpr, (const PTILEMAP)&triangle02down);
	#endif
	
	/*	TRIANGLE01DOWN SPRITE - AUTOMOVE			*/
	#ifdef TRIANGLES
	triangle01downSpr = sprMakeDefault(get_current_sprite());
	triangle01downSpr.pos.y = 213; //214
	triangle01downSpr.posInc.x--;
	triangle01downSpr.vblSkipTranslation = 5;
	triangle01downSpr.size = vec2u16Make(512, 16);
	write_sprite_data_nn(triangle01downSpr, (const PTILEMAP)&triangle01down);
	#endif
	
	
	#ifdef TEXT_ON
	#define TEXT00 "** NEO GEO CD INTRO RELEASED BY RESISTANCE ** MUSIC AND CODE NAINAIN ** GRAPHICS AND DESIGN GRASS THIS IS OUR FIRST RELEASE IN NEO GEO SCENE WWW.RESISTANCE.NO ENJOY!                                           "
//	#define TEXT00 "A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U                                            "
	text = texter8Make(TEXT00, vec2intMake(328,100));
	#endif
	while(1){
		wait_vbl();
		#ifdef TRIANGLES
		sprUpdate(&triangle03upSpr);
		sprUpdate(&triangle02upSpr);
		sprUpdate(&triangle01upSpr);

		sprUpdate(&triangle03downSpr);
		sprUpdate(&triangle02downSpr);
		sprUpdate(&triangle01downSpr);
		trianglesUpEffect(&triangle01upSpr, &triangle02upSpr, &triangle03upSpr);
		trianglesDownEffect(&triangle01downSpr, &triangle02downSpr, &triangle03downSpr);
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
