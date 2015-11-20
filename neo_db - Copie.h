#ifndef NEO_DB_H
#define NEO_DB_H
#include <stdlib.h>
#include <video.h>
#include "neo_core.h"

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

#endif