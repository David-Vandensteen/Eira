#include "neo_core.h"
#include "neo_texter.h"

#ifdef __NEOGEO__
#include <stdlib.h>
#include <video.h>
#include <math.h>
#include "neo_db.h"
#endif

#ifdef __NEOGEO__
texter texter8Make(WORD spriteId, char *string, vec2int pos){
	texter r;
	WORD i = 0;
	r.headPlay = 0;
	r.string = string;
	r.pos = pos;
	r.size = vec2u16Make(16, 16);
	r.zoom = vec2u16Make(7, 128);
	r.numChar = texterCount(r.string);
	r.counter = 8;
	for (i = 0; i <= TEXTER_RESERVED_SPRITE; i++){
		r.spritesIds[i] = get_current_sprite() + i;
		r.posSprites[i] = pos;
	}
	set_current_sprite(r.spritesIds[0] + TEXTER_RESERVED_SPRITE);

	printWord(r.counter, vec2intMake(0, 0));
	//printWord(r.zoom.y, vec2intMake(0, 1));


	//DEBUG
	//printWord(r.spritesIds[0], vec2intMake(0, 0));
	//printWord(r.spritesIds[1], vec2intMake(0, 1));
	//printWord(r.spritesIds[2], vec2intMake(0, 2));
	//printWord(r.spritesIds[3], vec2intMake(0, 3));
	//printWord(get_current_sprite(), vec2intMake(0, 5));
	//printWord(r.headPlay, vec2intMake(0, 6));
	//printWord(r.numChar, vec2intMake(0, 7));
	return r;
}
texter texter8MakeZero(){
	texter r;
	return r;
}
void texterOneAscii(WORD spriteId, WORD ascii, vec2int pos, vec2u16 size, vec2u16 zoom){
	//Possible d'optimiser, rien q'en organisant differement le bitmap afin d'alleger les tests conditionnels

	// ! - P	-> fontA	-> 33 - 80
	// Q - Z	-> fontB	-> 81 - 90

	// !		-> 33
	// ,		-> 44
	// /		-> 47
	// 0 - 9	-> 48 - 57
	// :		-> 58
	// ?		-> 63
	// A - Z	-> 65 - 90
	WORD spriteIndex = 0;
	//WORD curSprite = get_current_sprite();
	set_current_sprite(spriteId);

	if (ascii >= 33 && ascii <= 80){//fontA
		if (ascii == 33) {  spriteIndex = 0; }			// !
		if (ascii == 44) {  spriteIndex = 1; }			// ,
		if (ascii == 47) {  spriteIndex = 3; }			// /
		if (ascii == 58) {  spriteIndex = 14; }			// :
		if (ascii == 63) {  spriteIndex = 15; }			// ?

		if (ascii >= 48 && ascii <= 57){ // 0 - 9
			spriteIndex = ascii - 44;
		}
		if (ascii >= 65 && ascii <= 80){ // A - P
			spriteIndex = ascii - 49;
		}
		if (ascii != 32) write_sprite_data(pos.x, pos.y, zoom.x, zoom.y, tileSizeClipping(size.x), tileSizeNB(size.y), (const PTILEMAP)&fontA16[spriteIndex]);
	}
	else{//fontB
		spriteIndex = ascii - 81;
		if (ascii != 32) write_sprite_data(pos.x, pos.y, zoom.x, zoom.y, tileSizeClipping(size.x), tileSizeNB(size.y), (const PTILEMAP)&fontB16[spriteIndex]);
	}
	//set_current_sprite(curSprite);
}

void texterUpdatePos(WORD spriteId, char *string, vec2s16 pos, vec2u16 size, WORD spacing){
	WORD i = spriteId;
	WORD j = 0; //char index
	while (i < spriteId + texterCount(string)){
		if (string[j] != 32) {
			change_sprite_pos(i, pos.x + (j * spacing), pos.y, tileSizeClipping(size.y));
			i++;
		}
		j++;
	}
}


void texterUpdatePosSin(texter *text, WORD sin){
//	WORD i = text->spriteId;
//	WORD j = 0; //char index

	/*
    while (i < text->spriteId + text->headPlay){

		if (text->string[j] != 32) {
            change_sprite_pos(i,
                              text->pos.x + (j * text->spacing),
                              (ifmuli(fsin((sin - j * 1) * 8), 24) + 128), 
                              tileSizeClipping(text->size.y));
            i++;
        }
        j++;
    }
	*/
}

void texter8SinScrollEffect(texter *text, WORD sin){
	WORD i = 0;
	WORD curSprite = get_current_sprite();
	if (text->counter == 0 && text->headPlay <= text->numChar && text->headPlay <= TEXTER_RESERVED_SPRITE){
		text->posSprites[text->headPlay].x-=8;
		//if (text->headPlay == 0) text->posSprites[text->headPlay].x -= 8;
		texterOneAscii(text->spritesIds[text->headPlay], text->string[text->headPlay], text->posSprites[text->headPlay], text->size, text->zoom);
		text->counter = 8;
		text->headPlay++;
	}
	else{
		for (i = 0; i <= text->headPlay; i++){
			text->posSprites[i].x--;
			change_sprite_pos(text->spritesIds[i], text->posSprites[i].x, text->posSprites[i].y, tileSizeClipping(text->size.y));
		}
		text->counter--;
	}
}
void texterTranslateX(texter *text, int value){
}

void testerUpdateZoom(WORD spriteId, WORD count, vec2u16 size, WORD zoom){
	WORD i = spriteId;
	change_sprite_zoom(spriteId, zoom, mapTo_yz(zoom), size.x);
	for (i = spriteId; i < spriteId + count; i++){
		change_sprite_zoom(i, zoom, mapTo_yz(zoom), size.x);
	}
}
#endif
WORD texterCount(char *string){
	WORD r = 0;
	while (string[r] != '\0'){
		r++;
	}
	return r;
}

