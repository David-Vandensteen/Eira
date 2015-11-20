#include "neo_core.h"
#include "neo_texter.h"

#ifdef __NEOGEO__
#include <stdlib.h>
#include <video.h>
#include <math.h>
#include "neo_db.h"
#endif

#ifdef __NEOGEO__
texter texter8Make(char *string, vec2int pos){
	texter r;
	r.headPlay = 0;
	r.size = vec2u16Make(16, 16);
	r.zoom = vec2u16Make(7, 128);
	r.string = string;
	r.pos = pos;
	r.triggerMakeChar = 8;
	r.headSpriteList = NULL;
	return r;
}
texter texter8MakeZero(){
	texter r;
	return r;
}
spr *sprChar8Make(WORD ascii, vec2int pos){
	spr *r = (spr *)malloc(sizeof(800));
	r->idSpr = get_current_sprite();
	r->pos = pos;
	r->posInc = vec2intMakeZero();
	r->size = vec2u16Make(16, 16);
	r->vblSkipTranslation = 0;
	r->zoom = vec2u16Make(7, 128);
	r->zoomInc = vec2intMakeZero();
	r->vblSkipZoom = 0;
	r->clipping = 1;
	r->next = NULL;
	r->prev = NULL;
	texterOneAscii(r->idSpr, ascii, r->pos, r->size, r->zoom);
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
	// update headSpriteList
	if (text->headSpriteList != NULL){
		text->headSpriteList = sprListReturnFirst(text->headSpriteList);
	}
	////Position
	if (text->headSpriteList != NULL){
		spr *tmp = sprListReturnFirst(text->headSpriteList);
		spr *toTrash;
		while (tmp != NULL){
			toTrash = tmp;
			tmp->pos.x--;
            change_sprite_pos(tmp->idSpr, tmp->pos.x, tmp->pos.y, tmp->clipping);
            printDword(tmp->pos.x, vec2intMake(1, 1));
			tmp = tmp->next;
			if (toTrash->pos.x <= -8) { // -8
                sprClear(toTrash->idSpr);
				sprListRemove(toTrash);
				text->headSpriteList = sprListReturnFirst(tmp);
			}
		}
	}
	// New sprite
	if (text->triggerMakeChar <= 1){
		spr *tmp = sprChar8Make(text->string[text->headPlay], text->pos);
		sprListAdd(sprListReturnLast(text->headSpriteList), tmp);
		text->headSpriteList = sprListReturnFirst(tmp);
		text->triggerMakeChar = 8;
        text->headPlay++;
	}
	else{
		text->triggerMakeChar--;
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

