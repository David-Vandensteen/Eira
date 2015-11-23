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
//#define LOGO
//#define TEXT_ON
//#define SNOW


extern PALETTE	palettes[];
extern TILEMAP background, triangle03down, triangle03up, triangle02down, triangle02up, triangle01down, triangle01up;

void trianglesDownEffect(spr *triangle01, spr *triangle02, spr *triangle03){
	if (triangle01->zoom.y >= 250){
		triangle03->zoomInc.y = -2; //-2
		triangle02->zoomInc.y = -2; //-2
		triangle01->zoomInc.y = -3; //-3
	}
	if (triangle01->zoom.y <= 1){//1
		triangle03->zoomInc.y = 2; // 2
		triangle02->zoomInc.y = 2; // 2
		triangle01->zoomInc.y = 3; // 3
	}
}
void trianglesUpEffect(spr *triangle01, spr *triangle02, spr *triangle03){
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
	WORD i, j, k;
	vblStepByStep vblSbS;
	logoZoomEffect logoZoomEffect;
	spr backgroundSpr, triangle03downSpr, triangle03upSpr, triangle02downSpr, triangle02upSpr, triangle01downSpr, triangle01upSpr;
	snowField snowFieldBig, snowFieldMedium, snowFieldLittle;
	WORD sin = 0;

    #ifdef TEXT_ON
    texter text;
    #endif
    
	WORD logoZoomEffectPol = 0;
	fadeIn fadeInBackground;

    /* INIT */
	playcdda();
	setpalette(0, 60, (const PPALETTE)&palettes);
	vblSbS = vblStepByStepMake();
	logoZoomEffect = logoZoomEffectMake(0, 50, 1);
	set_current_sprite(3);

	fadeInBackground = fadeInMake((const PPALETTE)&palettes);

	/* INIT SPRITE & STRUCT SPRITE */
	
	/*	BACKGROUND SPRITE*/	
	backgroundSpr = sprMakeDefault(get_current_sprite());
	write_sprite_data_nn(backgroundSpr, (const PTILEMAP)&background);

	/*	SNOW */
	#ifdef SNOW
	snowFieldBig = snowFieldMake(1);
	#endif
	
	#ifdef LOGO
	logoZoomEffect.spriteId = get_current_sprite();
	logoZoomEffectUpdate(logoZoomEffect);
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
	triangle03upSpr.size = vec2u16Make(512, 48);
	write_sprite_data_nn(triangle03upSpr, (const PTILEMAP)&triangle03up);
	#endif
	
	/* TRIANGLE02UP SPRITE	- AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle02upSpr = sprMakeDefault(get_current_sprite());
	triangle02upSpr.pos.y = 0;
	triangle02upSpr.posInc.x--;
	triangle02upSpr.vblSkipTranslation = 10;
	triangle02upSpr.size = vec2u16Make(512, 48);
	write_sprite_data_nn(triangle02upSpr, (const PTILEMAP)&triangle02up);
	#endif
	
	/*	TRIANGLE01UP SPRITE	- AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle01upSpr = sprMakeDefault(get_current_sprite());
	triangle01upSpr.pos.y = 0;
	triangle01upSpr.posInc.x--;
	triangle01upSpr.vblSkipTranslation = 5;
	triangle01upSpr.size = vec2u16Make(512, 48);
	write_sprite_data_nn(triangle01upSpr, (const PTILEMAP)&triangle01up);
	#endif
	
	/*	TRIANGLE03DOWN SPRITE	- AUTOMOVE		*/
	#ifdef TRIANGLES
	triangle03downSpr = sprMakeDefault(get_current_sprite());
	triangle03downSpr.pos.y = 196; //176
	triangle03downSpr.posInc.x--;
	triangle03downSpr.vblSkipTranslation = 15;
	triangle03downSpr.size = vec2u16Make(512,48);
	write_sprite_data_nn(triangle03downSpr, (const PTILEMAP)&triangle03down);
	#endif
	
	/*	TRIANGLE02DOWN SPRITE - AUTOMOVE			*/
	#ifdef TRIANGLES
	triangle02downSpr = sprMakeDefault(get_current_sprite());
	triangle02downSpr.pos.y = 196; //176
	triangle02downSpr.posInc.x--;
	triangle02downSpr.vblSkipTranslation = 10;
	triangle02downSpr.size = vec2u16Make(512, 48);
	write_sprite_data_nn(triangle02downSpr, (const PTILEMAP)&triangle02down);
	#endif
	
	/*	TRIANGLE01DOWN SPRITE - AUTOMOVE			*/
	#ifdef TRIANGLES
	triangle01downSpr = sprMakeDefault(get_current_sprite());
	triangle01downSpr.pos.y = 206; //176
	triangle01downSpr.posInc.x--;
	triangle01downSpr.vblSkipTranslation = 5;
	triangle01downSpr.size = vec2u16Make(512, 48);
	write_sprite_data_nn(triangle01downSpr, (const PTILEMAP)&triangle01down);
	#endif
	
	
	#ifdef TEXT_ON
	#define TEXT00 "** NEO GEO CD INTRO RELEASED BY RESISTANCE ** MUSIC AND CODE : NAINAIN  ** GRAPHICS AND DESIGN GRASS     THIS IS OUR FIRST RELEASE IN NEO GEO SCENE   WWW.RESISTANCE.NO   ENJOY!                         ***     ****   *****         *********                                                             "
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

		#ifdef TEXT_ON
		#endif
		
		/* VBL CONDITIONS */
		//fade 
		if (_vbl_count % 3 == 0 && fadeInBackground.step > 0){
            fadeInUpdate(&fadeInBackground, 1, 1);
		}

		//texter sin
		#ifdef TEXT_ON
		if (_vbl_count % 2 == 0){
			sin++;
		}
		#endif

		#ifdef LOGO
		if (_vbl_count % logoZoomEffect.vblSkip == 0){
			logoZoomEffectUpdate(logoZoomEffect);
			if(logoZoomEffectPol == 0) logoZoomEffect.zoom++;
			if (logoZoomEffectPol > 0) logoZoomEffect.zoom--;
		}
		if (logoZoomEffect.zoom >= 100){ logoZoomEffectPol = 1; }
		if (logoZoomEffect.zoom <= 50) { logoZoomEffectPol = 0; }
		#endif
		
		#ifdef TEXT_ON
		texter8SinScrollEffect(&text,sin);
		#endif

		vblStepByStepUpdate(&vblSbS);
	}
}
