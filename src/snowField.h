#ifndef SNOWFIELD_H
#define SNOWFIELD_H
#include "neo_core.h"
#define SNOWBIG_QTY			5
#define SNOWMEDIUM_QTY		5
#define SNOWLITTLE_QTY		15
#define SNOWMAX_QTY			15

typedef struct snowField snowField;
struct snowField{
	spr sprs[SNOWMAX_QTY];
	WORD spriteQty;
	WORD type;
	vec2u16	zoom;
	vec2int	zoomInc;
};

snowField snowFieldMake(WORD type);
void snowFieldUpdate(snowField *sf);
#endif