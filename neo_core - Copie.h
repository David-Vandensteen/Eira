#ifndef NEO_CORE_H
#define NEO_CORE_H
#ifdef __NEOGEO__
	#include <stdlib.h>
	#include <video.h>
	#include <input.h>
#endif

/*	MEMO :	NEOGEO	
	RES		: 320 x 224
	MaxSpr	: 380
	Colors	: 4096 (simultanées)
	ScaleXZ	: 000  -  015
	ScaleYZ : 000  -  255
	NB * 16 = WIDTH
	CLIPPING * 16 = HEIGHT ?
	NB = rSprite.size.x / 16;
	CLIPPING = rSprite.size.y / 16;

	MULTIPLE 16
	16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 256, 272, 288, 304, 320, 336, 352, 368, 384, 400, 416, 432, 448, 464, 480, 496, 512,
	528, 544, 560, 576, 592, 608, 624, 640, 656, 672, 688, 704, 720, 736, 752, 768, 784, 800, 816, 832, 848, 864, 880, 896, 912, 928, 944, 960, 976, 992, 1008,
	1024, 1040, 1056,

	MEMO INTRO
	TRIANGLE SPRITE LOOPED	:	WIDTH = 512
*/

/* GLOBALS VAR CONST */
#ifdef __GENESIS__
s16 _vbl_count = 0;
#endif

/*	TYPE: */
#ifdef __NEOGEO__
#define s8      char
#define s16     short
#define s32     long
#define u8      unsigned char
#define u16     unsigned short
#define u32     unsigned long
#endif
 
#ifdef __GENESIS__
#define char	s8
#define short	s16
#define long	s32
#define unsigned char	u8
#define unsigned short	u16
#define unsigned long	u32
#endif

/* STRUCT */
typedef struct vec2int vec2int;
struct vec2int{
	int x;
	int y;
};
typedef struct vec2word vec2word;
struct vec2word{
	WORD x;
	WORD y;
};
typedef struct scrolling scrolling;
struct scrolling{
	vec2word pos;
	vec2word posInc;
	WORD vblFrameSkip;
};

/* STRUCT NEOGEO  */
#ifdef __NEOGEO__
typedef struct Vect2D_s8 Vect2D_s8;
struct Vect2D_s8{
	s8 x;
	s8 y;
};

typedef struct Vect2D_s16 Vect2D_s16;
struct Vect2D_s16{
	s16 x;
	s16 y;
};

typedef struct Vect2D_s32 Vect2D_s32;
struct Vect2D_s32{
	s32 x;
	s32 y;
};

typedef struct Vect2D_u8 Vect2D_u8;
struct Vect2D_u8{
	u8 x;
	u8 y;
};

typedef struct Vect2D_u16 Vect2D_u16;
struct Vect2D_u16{
	u16 x;
	u16 y;
};

typedef struct Vect2D_u32 Vect2D_u32;
struct Vect2D_u32{
	u32 x;
	u32 y;
};
typedef struct joystick joystick;
struct joystick{
	WORD up;
	WORD left;
	WORD right;
	WORD down;

	WORD a;
};
typedef struct spr spr;
struct spr{
    WORD idSpr;
	vec2int size;
	WORD nb;
	WORD clipping;
    vec2int pos;
    vec2int posInc;
	WORD vblSkipTranslation;
    vec2int zoom;
    vec2int zoomInc;
	WORD vblSkipZoom;
    
    //INTERNAL
	WORD firstUpdate;
    vec2int origPos;
	vec2int origPosInc;
	vec2int origZoom;
	vec2int origZoomInc;
    
};
typedef struct fadeIn fadeIn;
struct fadeIn{
    PFADE_TABLE table;
    FADER fader;
    WORD step;
};
#endif

/* MACRO NEOGEO */
#ifdef __NEOGEO__
#define SIZE_SPR_DEFAULT	15, 255
#define RAND512	rand() >> 7 //randon 16bits décalé de 7bits
#define RAND224 rand() / 292 //random sur 224 
#endif

/*	VECTOR */
vec2int vec2intMake(int x, int y);
vec2int vect2intMakeZero();
Vect2D_s8 Vect2D_s8Make(s8 x, s8 y);
Vect2D_s16 Vect2D_s16Make(s16 x, s16 y);
Vect2D_s32 Vect2D_s32Make(s32 x, s32 y);
Vect2D_u8 Vect2D_u8Make(u8 x, u8 y);
Vect2D_u16 Vect2D_u16Make(u16 x, u16 y);
Vect2D_u32 Vect2D_u32Make(u32 x, u32 y);
Vect2D_s8 Vect2D_s8MakeZero();
Vect2D_s16 Vect2D_s16MakeZero();
Vect2D_s32 Vect2D_s32MakeZero();
Vect2D_u8 Vect2D_u8MakeZero();
Vect2D_u16 Vect2D_u16MakeZero();
Vect2D_u32 Vect2D_u32MakeZero();

/* SPRITE NEOGEO */
#ifdef __NEOGEO__
spr sprMake(WORD idSpr, vec2int pos, vec2int posInc, vec2int size, WORD vblSkipTranslation, vec2int zoom, vec2int zoomInc, WORD vblSkipZoom);
spr sprMakeDefault(WORD idSpr);
spr sprMakeZero();
DWORD write_sprite_data_nn(spr sprite,const PTILEMAP tilemap);
#endif
/* SPRITE	*/
void sprUpdate(spr *spr);

/*	TRANSFORM NEOGEO */
#ifdef __NEOGEO__
void sprZoomEffectPingPong(spr *spr, WORD minTresh, WORD maxTresh);
#endif

/* PALETTE NEOGEO */
#ifdef __NEOGEO__
fadeIn fadeInMake(PPALETTE palettes);
void fadeInUpdate(fadeIn *fadeIn, WORD palstart, WORD nb);
#endif

/* UTILS */
scrolling scrollingMake(vec2word pos, vec2word posInc, WORD vblFrameSkip);
scrolling ScrollingMakeZero();
void scrollingUpdate(scrolling *scrolling);
void pause(WORD vblTempo);

/* UTILS NEOGEO */
vec2int tileSize(vec2int sizePixels);
WORD tileSizeNB(WORD xPixelsWidth);
WORD tileSizeClipping(WORD yPixelsHeigt);
WORD mapTo_xz(WORD yz);
WORD mapTo_yz(WORD xz);
joystick joystickMake();
void joystickUpdate(joystick *joy);

/* UTILS GENESIS */
#ifdef __GENESIS__
void sceneInit(s16 spriteCacheSize);
void scenePlansPositionZero();
#endif


/* UTILS KONAMI CODE */
#define KONAMICODEINIT		u16 konButtonSeqState[12] = {0,0,0,0,0,0,0,0,0,0,0,0}
#define KONAMICODEUPDATE	konamiCodeUpdate(&konButtonSeqState)
u16 konamiCodeUpdate(u16 *buttonSeq); //return TRUE when code is complete
#endif
