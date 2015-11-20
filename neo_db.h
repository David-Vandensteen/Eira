#ifndef NEO_DB_H
#define NEO_DB_H
#include "neo_core.h"

#include <stdlib.h>
#include <video.h>

typedef struct vblStepByStep vblStepByStep;
struct vblStepByStep{
	joystick joy;
	int isActive;
};
void sprDb(spr spr);
vblStepByStep vblStepByStepMake();
void vblStepByStepUpdate(vblStepByStep *vblSbS);
void printString(char *string, vec2int pos);
void printWord(WORD value, vec2int pos);
void printDword(DWORD value, vec2int pos);
void printChar(char value, vec2int pos);
void printS32(char *pLib, s32 value, u16 plan, vec2s16 pos);
void printU32(char *pLib, u32 value, u16 plan, vec2s16 pos);
void printU16(char *pLib, u16 value, u16 plan, vec2s16 pos);
void printS16(char *pLib, s16 value, u16 plan, vec2s16 pos);
void printU8(char *pLib, u8 value, u16 plan, vec2s16 pos);
#endif
