#ifndef NEO_TEXTER_H
#define NEO_TEXTER_H
#include "neo_core.h"
#include <stdlib.h>
#include <video.h>

#define TEXTER_SPRITES_QTY 44 //43
extern TILEMAP fontA16[], fontB16[];
typedef struct texter texter;
struct texter{
    WORD spriteId;
    WORD currentSpriteId;
	WORD headPlayStr;
	WORD headPlaySpr;
	WORD charMaker;
	WORD isComplete;
	vec2int pos;
	spr sprs[TEXTER_SPRITES_QTY];
	char *string;
}__ALIGN16__;
texter texter8Make(char *string, vec2int pos);
texter texter8MakeZero();
spr sprChar8Make(WORD spriteId,WORD ascii, vec2int pos);
void texterPush(texter *text);
void texterRemoveAt(texter *text, WORD arrayId);
void texterOneAscii(WORD spriteId,WORD ascii, vec2int pos, vec2u16 size, vec2u16 zoom);
void texterUpdatePosSin(texter *text, WORD sin);
WORD texter8SinScrollEffect(texter *text, WORD sin);
void texter8SinScrollEffectDebug(texter text);
WORD texterCount(char *string);
#endif
