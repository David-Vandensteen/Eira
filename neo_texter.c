#include "neo_core.h"
#include "neo_texter.h"
#include <stdlib.h>
#include <video.h>
#include <math.h>
#include "neo_db.h"

texter texter8Make(char *string, vec2int pos){
	texter r;
	WORD i = 0;
    r.spriteId = get_current_sprite();
    r.currentSpriteId = r.spriteId;
	r.headPlayStr = 0;
	r.headPlaySpr = 0;
	r.size = vec2u16Make(16, 16);
	r.zoom = vec2u16Make(7, 128);
	r.string = string;
	r.pos = pos;
	r.charMaker = 8;
	for (i = 0; i < TEXTER_SPRITES_QTY; i++){
		r.sprs[i].idSpr = 0;
		r.sprs[i].pos = vec2intMakeZero();
	}
    set_current_sprite(r.spriteId + TEXTER_SPRITES_QTY);
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

	if (ascii >= 33 && ascii <= 79){//fontA
		if (ascii == 33) {  spriteIndex = 0; }			// !
		if (ascii == 42) {  spriteIndex = 1; }			// *
		if (ascii == 44) {  spriteIndex = 2; }			// ,
		if (ascii == 46) {	spriteIndex = 3; }			// .
		if (ascii == 47) {  spriteIndex = 4; }			// /
		if (ascii == 58) {  spriteIndex = 15; }			// :
		if (ascii == 63) {  spriteIndex = 16; }			// ?

		if (ascii >= 48 && ascii <= 57){ // 0 - 9
			spriteIndex = ascii - 43;
		}
		if (ascii >= 65 && ascii <= 80){ // A - P
			spriteIndex = ascii - 48;
		}
		if (ascii != 32) write_sprite_data(pos.x, pos.y, zoom.x, zoom.y, tileSizeClipping(size.x), tileSizeNB(size.y), (const PTILEMAP)&fontA16[spriteIndex]);
	}
	else{//fontB
		spriteIndex = ascii - 80;
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
spr sprChar8Make(WORD spriteId,WORD ascii, vec2int pos){
	spr r;
	if (ascii != 32) {
		r = sprMake(spriteId, pos, vec2intMakeZero(), vec2u16Make(16, 16), 0, vec2u16Make(7, 128), vec2intMake(0, 0), 0);
		texterOneAscii(r.idSpr, ascii, pos, r.size, r.zoom);
	}else{
		r.idSpr = 0;
	}
	return r;    
}
void texterPush(texter *text){
	if (text->headPlaySpr < TEXTER_SPRITES_QTY){
        text->sprs[text->headPlaySpr] = sprChar8Make(text->currentSpriteId,text->string[text->headPlayStr], text->pos);
        if (text->string[text->headPlayStr] != 32) {
            text->currentSpriteId++;
        }
		text->headPlayStr++;
		text->headPlaySpr++;
	}
}
void texterRemoveAt(texter *text, WORD arrayId){
	if (text->sprs[arrayId].idSpr != 0){
        sprClear(text->sprs[arrayId].idSpr);
		text->sprs[arrayId].idSpr = 0;
		text->sprs[arrayId].pos = vec2intMakeZero();
		if (text->headPlaySpr >= TEXTER_SPRITES_QTY ){
			text->headPlaySpr = 0;
            text->currentSpriteId = text->spriteId;
		}
	}
}
WORD texter8SinScrollEffect(texter *text, WORD sin){
	WORD i,j;
    if(text->headPlayStr > texterCount(text->string)){
        return 1;
    }
	text->charMaker--;
	if (text->charMaker <= 0){
		texterPush(text);
		text->charMaker = 8;
	}
	//position update
	j = text->headPlaySpr;
	for (i = 0; i <= TEXTER_SPRITES_QTY; i++){
		if (text->sprs[j].idSpr != 0){
			text->sprs[j].pos.x--;
			text->sprs[j].pos.y = (ifmuli(fsin((sin - i * 1) * 8), 24) + 152); //128
			change_sprite_pos(text->sprs[j].idSpr, text->sprs[j].pos.x, text->sprs[j].pos.y, text->sprs[j].clipping);
			if (text->sprs[j].pos.x <= 0){
				texterRemoveAt(text, j);
			}
		}
        if (j < TEXTER_SPRITES_QTY - 1 ) { j++; } else { j = 0;}
    }
    return 0;
}
void texter8SinScrollEffectDebug(texter text){
	WORD j = 0, k = 0, i = 0;
	for (i = 0; i < TEXTER_SPRITES_QTY; i++) {
		printWord(text.sprs[i].idSpr, vec2intMake(j, k));
		k++;
		if(k > 20){ k = 0; j += 3;}
	}
}
void testerUpdateZoom(WORD spriteId, WORD count, vec2u16 size, WORD zoom){
	WORD i = spriteId;
	change_sprite_zoom(spriteId, zoom, mapTo_yz(zoom), size.x);
	for (i = spriteId; i < spriteId + count; i++){
		change_sprite_zoom(i, zoom, mapTo_yz(zoom), size.x);
	}
}
WORD texterCount(char *string){
	WORD r = 0;
	while (string[r] != '\0'){
		r++;
	}
	return r;
}
