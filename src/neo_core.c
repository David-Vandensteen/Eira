#include "neo_core.h"
#include <stdlib.h>
#include <video.h>

/*	VECTOR */
vec2int vec2intMake(int x, int y){
	vec2int rvec2;
	rvec2.x = x;
	rvec2.y = y;
	return rvec2;
}
vec2int vec2intMakeZero(){
	vec2int rvec2;
	rvec2.x = 0;
	rvec2.y = 0;
	return rvec2;
}
vec2s16 vec2s16Make(s16 x, s16 y){
	vec2s16 r;
	r.x = x;
	r.y = y;
	return r;
}
vec2s32 vec2s32Make(s32 x, s32 y){
	vec2s32 r;
	r.x = x;
	r.y = y;
	return r;
}
vec2u16 vec2u16Make(u16 x, u16 y){
	vec2u16 r;
	r.x = x;
	r.y = y;
	return r;
}
vec2u32 vec2u32Make(u32 x, u32 y){
	vec2u32 r;
	r.x = x;
	r.y = y;
	return r;
}
vec2s16 vec2s16MakeZero(){
	vec2s16 r;
	r.x = 0;
	r.y = 0;
	return r;
}
vec2s32 vec2s32MakeZero(){
	vec2s32 r;
	r.x = 0;
	r.y = 0;
	return r;
}
vec2u16 vec2u16MakeZero(){
	vec2u16 r;
	r.x = 0;
	r.y = 0;
	return r;
}
vec2u32 vec2u32MakeZero(){
	vec2u32 r;
	r.x = 0;
	r.y = 0;
	return r;
}
Vect2D_s16 Vect2D_s16Make(s16 x, s16 y){
	Vect2D_s16 r;
	r.x = x;
	r.y = y;
	return r;

}
Vect2D_s32 Vect2D_s32Make(s32 x, s32 y){
	Vect2D_s32 r;
	r.x = x;
	r.y = y;
	return r;
}
Vect2D_u16 Vect2D_u16Make(u16 x, u16 y){
	Vect2D_u16 r;
	r.x = x;
	r.y = y;
	return r;
}
Vect2D_u32 Vect2D_u32Make(u32 x, u32 y){
	Vect2D_u32 r;
	r.x = x;
	r.y = y;
	return r;
}
Vect2D_s16 Vect2D_s16MakeZero(){
	Vect2D_s16 r;
	r.x = 0;
	r.y = 0;
	return r;
}
Vect2D_s32 Vect2D_s32MakeZero(){
	Vect2D_s32 r;
	r.x = 0;
	r.y = 0;
	return r;
}
Vect2D_u16 Vect2D_u16MakeZero(){
	Vect2D_u16 r;
	r.x = 0;
	r.y = 0;
	return r;
}
Vect2D_u32 Vect2D_u32MakeZero(){
	Vect2D_u32 r;
	r.x = 0;
	r.y = 0;
	return r;
}


/* UTILS */
scrolling scrollingMake(vec2word pos, vec2word posInc, WORD vblFrameSkip){
	scrolling rScrolling;
	rScrolling.pos = pos;
	rScrolling.posInc = posInc;
	rScrolling.vblFrameSkip = vblFrameSkip;
	return rScrolling;

}
scrolling ScrollingMakeZero(){
	scrolling rScrolling;
	rScrolling.pos.x = 0;
	rScrolling.pos.y = 0;
	rScrolling.posInc.x = 0;
	rScrolling.posInc.y = 0;
	rScrolling.vblFrameSkip = 0;
	return rScrolling;
}
void scrollingUpdate(scrolling *scrolling){

}
u16 konamiCodeUpdate(u16 *buttonSeq){
	return 0;
}

/* UTILS NEOGEO */
vec2int tileSize(vec2int sizePixels){
	return vec2intMake(sizePixels.x / 16, sizePixels.y / 16);
}
WORD tileSizeNB(WORD xPixelsWidth){
	return xPixelsWidth / 16;
}
WORD tileSizeClipping(WORD yPixelsHeigt){
	return yPixelsHeigt / 16;
}
WORD mapTo_xz(WORD yz){
	// permet de convertir yz sur le range xz
	return yz / 17;
}
WORD mapTo_yz(WORD xz){
	return xz * 17;
}
joystick joystickMake(){
	joystick j;
	j.up = j.left = j.right = j.down = j.a = 0;
	return j;
}

void pause(WORD vblTempo){
	WORD i = 0;
	for (i = 0; i <= vblTempo; i++){
		wait_vbl();
	}
	_vbl_count -= i;
}

/*	SPRITE NEOGEO */
spr sprMake(WORD idSpr, vec2int pos, vec2int posInc, vec2u16 size, WORD vblSkipTranslation, vec2u16 zoom, vec2int zoomInc, WORD vblSkipZoom){
    spr rSprite;
    rSprite.pos = pos;
    rSprite.posInc = posInc;
    rSprite.zoom = zoom;
    rSprite.zoomInc = zoomInc;
    rSprite.idSpr = idSpr;
    rSprite.size = size;
    rSprite.nb = size.x/16;
    rSprite.clipping = size.y/16;
    rSprite.vblSkipTranslation = vblSkipTranslation;
    rSprite.vblSkipZoom = vblSkipZoom;
    rSprite.firstUpdate = 0;
    return rSprite;
}
spr sprMakeZero(){
    spr rSprite;
    rSprite.idSpr = 0;
    rSprite.size = vec2u16MakeZero();
    rSprite.nb = 0;
    rSprite.clipping = 0;
    rSprite.pos = vec2intMakeZero();
    rSprite.posInc = vec2intMakeZero();
    rSprite.vblSkipTranslation = 0;
    rSprite.zoom = vec2u16MakeZero();
    rSprite.zoomInc = vec2intMakeZero();
    rSprite.vblSkipZoom = 0;
    rSprite.firstUpdate = 0;
    return rSprite;

}
spr sprMakeDefault(WORD idSpr){
	spr rSprite;
	rSprite.idSpr = idSpr;
	rSprite.size = vec2u16Make(320, 224);
	rSprite.nb = rSprite.size.x/16;
	rSprite.clipping = rSprite.size.y/16;
	rSprite.pos = vec2intMakeZero();
	rSprite.posInc = vec2intMakeZero();
	rSprite.vblSkipTranslation = 0;
	rSprite.zoom = vec2u16Make(SIZE_SPR_DEFAULT);
	rSprite.zoomInc = vec2intMakeZero();
	rSprite.vblSkipZoom = 0;
	rSprite.firstUpdate = 0;
	return rSprite;
}
DWORD write_sprite_data_nn(spr sprite,const PTILEMAP tilemap){
	return write_sprite_data(sprite.pos.x, sprite.pos.y, sprite.zoom.x, sprite.zoom.y, sprite.size.y/16, sprite.size.x/16, tilemap);
}
void sprClear(WORD spriteId){
	WORD curSprite = get_current_sprite();
	set_current_sprite(spriteId);
	erase_sprites(1);
	set_current_sprite(curSprite);
}

/*	SPRITE	*/
void sprUpdate(spr *spr){
	if (!spr->firstUpdate){
		//Memorisation des valeurs d origine dans les "slots" orig... de la structure
		spr->firstUpdate = 1;
		spr->origPos.x = spr->pos.x;
		spr->origPos.y = spr->pos.y;
		spr->origPosInc.x = spr->posInc.x;
		spr->origPosInc.y = spr->posInc.y;
		spr->origZoom.x = spr->zoom.x;
		spr->origZoom.y = spr->zoom.y;
		spr->origZoomInc.x = spr->zoomInc.x;
		spr->origZoomInc.y = spr->zoomInc.y;
	}
	if (spr->vblSkipTranslation == 0 || _vbl_count % spr->vblSkipTranslation == 0){
		if (spr->posInc.x != 0) spr->pos.x += spr->posInc.x;
		if (spr->posInc.y != 0) spr->pos.y += spr->posInc.y;
		change_sprite_pos(spr->idSpr, spr->pos.x, spr->pos.y, spr->size.y / 16);
	}
	if (spr->vblSkipZoom == 0 || _vbl_count % spr->vblSkipZoom == 0){
		spr->zoom.x += spr->zoomInc.x;
		spr->zoom.y += spr->zoomInc.y;
		change_sprite_zoom(spr->idSpr, spr->zoom.x, spr->zoom.y, spr->nb);
		//change_sprite_zoomCenter(&spr, spr->zoom.x, spr->zoom.y);
	}

}

/* TRANSFORM NEOGEO */
void sprZoomEffectPingPong(spr *spr, WORD maxTresh, WORD minTresh){
	if (_vbl_count % spr->vblSkipZoom == 0){
		if (spr->zoom.x >= maxTresh){
			if (spr->origZoomInc.x > 0){ spr->zoomInc.x = spr->origZoomInc.x * -1; }
			if (spr->origZoomInc.x < 0){ spr->zoomInc.x = spr->origZoomInc.x; }
		}

		if (spr->zoom.x <= minTresh){
			if (spr->origZoomInc.x > 0){ spr->zoomInc.x = spr->origZoomInc.x; }
			if (spr->origZoomInc.x < 0){ spr->zoomInc.x = spr->origZoomInc.x * -1; }
		}
	}
}
