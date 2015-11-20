#include "neo_core.h"
#include "neo_db.h"

#ifdef __NEOGEO__
#include <stdlib.h>
#include <video.h>
#endif

#ifdef __GENESIS__
void printS32(char *pLib, s32 value, u16 plan, vec2s16 pos){
	int i = 0; for (i = 0; i < 6; i++){ VDP_clearTextBG(plan, pos.x + i, pos.y, 1); }
	VDP_drawTextBG(plan, pLib, 0, pos.x, pos.y);
	char valueStr[6];
	intToStr(value, valueStr, 6);
	VDP_clearTextBG(plan, pos.x, pos.y + 1, 1);
	VDP_drawTextBG(plan, valueStr, 0, pos.x, pos.y + 1);
}
void printU32(char *pLib, u32 value, u16 plan, vec2s16 pos){
	int i = 0; for (i = 0; i < 6; i++){ VDP_clearTextBG(plan, pos.x + i, pos.y, 1); }
	VDP_drawTextBG(plan, pLib, 0, pos.x, pos.y);
	char valueStr[6];
	intToStr(value, valueStr, 6);
	VDP_clearTextBG(plan, pos.x, pos.y + 1, 1);
	VDP_drawTextBG(plan, valueStr, 0, pos.x, pos.y + 1);
}
void printU16(char *pLib, u16 value, u16 plan, vec2s16 pos){
	int i = 0; for (i = 0; i < 6; i++){ VDP_clearTextBG(plan, pos.x + i, pos.y, 1); }
	VDP_drawTextBG(plan, pLib, 0, pos.x, pos.y);
	char valueStr[6];
	intToStr(value, valueStr, 6);
	VDP_clearTextBG(plan, pos.x, pos.y + 1, 1);
	VDP_drawTextBG(plan, valueStr, 0, pos.x, pos.y + 1);
}
void printS16(char *pLib, s16 value, u16 plan, vec2s16 pos){
	int i = 0; for (i = 0; i < 7; i++){ VDP_clearTextBG(plan, pos.x + i, pos.y + 1, 1); }
	VDP_drawTextBG(plan, pLib, 0, pos.x, pos.y);
	char valueStr[6];
	intToStr(value, valueStr, 6);
	VDP_clearTextBG(plan, pos.x, pos.y + 1, 1);
	VDP_drawTextBG(plan, valueStr, 0, pos.x, pos.y + 1);
}
void printU8(char *pLib, u8 value, u16 plan, vec2s16 pos){
	int i = 0; for (i = 0; i < 7; i++){ VDP_clearTextBG(plan, pos.x + i, pos.y + 1, 1); }
	VDP_drawTextBG(plan, pLib, 0, pos.x, pos.y);
	char valueStr[6];
	intToStr(value, valueStr, 6);
	VDP_clearTextBG(plan, pos.x, pos.y + 1, 1);
	VDP_drawTextBG(plan, valueStr, 0, pos.x, pos.y + 1);
}
void printString(char *string, u16 plan, vec2s16 pos){
	int i = 0; for (i = 0; i < 20; i++){ VDP_clearTextBG(plan, pos.x + i, pos.y + 1, 1); }
	VDP_drawTextBG(plan, string, 0, pos.x, pos.y);
}
#endif

#ifdef __NEOGEO__
void sprDb(spr spr){
    textoutf(0, 0, 0, 0, " sprite idSpr:%d ", spr.idSpr);
    textoutf(0, 1, 0, 0, " sprite clipping:%d ", spr.size.y/16);
    textoutf(0, 2, 0, 0, " sprite nb:%d ", spr.size.x/16);
    textoutf(0, 3, 0, 0, " sprite pos:%d %d",spr.pos.x, spr.pos.y );
    textoutf(0, 4, 0, 0, " sprite posInc:%d %d", spr.posInc.x, spr.posInc.y );
    textoutf(0, 5, 0, 0, " sprite vblSkipTranslation:%d ", spr.vblSkipTranslation);
    textoutf(0, 6, 0, 0, " sprite zoom:%d %d", spr.zoom.x, spr.zoom.y );
    textoutf(0, 7, 0, 0, " sprite zoomInc:%d %d", spr.zoomInc.x, spr.zoomInc.y );
    textoutf(0, 8, 0, 0, " sprite vblSkipZoom:%d ", spr.vblSkipZoom);
}

void printString(char *string, vec2int pos){
	textoutf(pos.x, pos.y, 0, 0, string);
}

void printDword(DWORD value, vec2int pos){
	textoutf(pos.x, pos.y, 0, 0, " %d ", value);
}

void printWord(WORD value, vec2int pos){
	textoutf(pos.x, pos.y, 0, 0, " %d ", value);
}

void printChar(char value, vec2int pos){
	textoutf(pos.x, pos.y, 0, 0, " %c ", value);
}

vblStepByStep vblStepByStepMake(){
	vblStepByStep r;
	r.isActive = 0;
	r.joy = joystickMake();
	return r;
}
void vblStepByStepUpdate(vblStepByStep *vblSbS){
	joystickUpdate(&vblSbS->joy);
	if (vblSbS->joy.a == 1){
		vblSbS->isActive = 1;
	}
	if (vblSbS->isActive){
		while (vblSbS->joy.a == 0){
			joystickUpdate(&vblSbS->joy);
			pause(7);
		}
	}
}
#endif
