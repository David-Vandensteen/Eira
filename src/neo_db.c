#include "neo_core.h"
#include "neo_db.h"
#include <stdlib.h>
#include <video.h>

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

/*
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
*/