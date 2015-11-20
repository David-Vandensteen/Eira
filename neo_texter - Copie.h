#ifndef NEO_TEXTER_H
#define NEO_TEXTER_H
#include "neo_core.h"

#ifdef __NEOGEO__
#include <stdlib.h>
#include <video.h>
#endif

#ifdef __NEOGEO__
#define TEXTER_RESERVED_SPRITE	42
typedef struct texter texter;
struct texter{
	WORD spritesIds[TEXTER_RESERVED_SPRITE];
	vec2u16 size; //sprite size
	vec2u16 zoom;
	vec2int posSprites[TEXTER_RESERVED_SPRITE];
	vec2int pos;
	WORD headPlay;		//internal
	WORD numChar;		//internal
	WORD counter;		//internal
	char *string;
}__ALIGN16__;

extern TILEMAP fontA16[], fontB16[];
#endif

#ifdef __NEOGEO__
texter texter8Make(WORD spriteId, char *string, vec2int pos);
texter texter8MakeZero();
void texterOneAscii(WORD spriteId,WORD ascii, vec2int pos, vec2u16 size, vec2u16 zoom);
void testerUpdateZoom(WORD spriteId, WORD count, vec2u16 size, WORD zoom); // zoom 0...15
void texterUpdatePos(WORD spriteId, char *string, vec2s16 pos, vec2u16 size, WORD spacing);
void texterUpdatePosSin(texter *text, WORD sin);
void texterTranslateX(texter *text, int value);
void texter8SinScrollEffect(texter *text, WORD sin);
#endif

WORD texterCount(char *string);

#endif