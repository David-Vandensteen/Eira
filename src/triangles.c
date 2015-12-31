#include <stdlib.h>
#include <video.h>
#include <math.h>
#include "triangles.h"
#include "neo_core.h"

void triangle01Umove(WORD id, WORD *x, WORD *yz, WORD *zoomPol){
	if (*zoomPol == 0) *yz = (*yz - (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (*zoomPol == 1) *yz = (*yz + (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (_vbl_count % TRIANGLE01D_VBLSKIPMOVE == 0) *x += TRIANGLES_XINC;
	change_sprite_pos(id, *x, 0, tileSizeClipping(16));
	change_sprite_zoom(id, 15, *yz, tileSizeNB(512));
	if (*yz <= 0x00 + TRIANGLES_ZOOMINC) *zoomPol = 1;
	if (*yz >= 0xFF - TRIANGLES_ZOOMINC) *zoomPol = 0;
}
void triangle02Umove(WORD id, WORD *x, WORD *yz, WORD *zoomPol){
	if (*zoomPol == 0) *yz = (*yz - (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (*zoomPol == 1) *yz = (*yz + (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (_vbl_count % TRIANGLE01D_VBLSKIPMOVE == 0) *x += TRIANGLES_XINC;
	change_sprite_pos(id, *x, 0, tileSizeClipping(48));
	change_sprite_zoom(id, 15, *yz, tileSizeNB(512));
	if (*yz <= 0x00 + TRIANGLES_ZOOMINC) *zoomPol = 1;
	if (*yz >= 0xFF - TRIANGLES_ZOOMINC) *zoomPol = 0;
}
void triangle03Umove(WORD id, WORD *x, WORD *yz, WORD *zoomPol){
	if (*zoomPol == 0) *yz = (*yz - (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (*zoomPol == 1) *yz = (*yz + (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (_vbl_count % TRIANGLE01D_VBLSKIPMOVE == 0) *x += TRIANGLES_XINC;
	change_sprite_pos(id, *x, 0, tileSizeClipping(48));
	change_sprite_zoom(id, 15, *yz, tileSizeNB(512));
	if (*yz <= 0x00 + TRIANGLES_ZOOMINC) *zoomPol = 1;
	if (*yz >= 0xFF - TRIANGLES_ZOOMINC) *zoomPol = 0;
}
void triangle01Dmove(WORD id, WORD *x, FIXED *y, WORD *yz, WORD *zoomPol){
	if (*zoomPol == 0) {
		*y = fadd(*y, 4096 * TRIANGLES_ZOOMINC);
	}
	else{
		*y = fadd(*y, -4096 * TRIANGLES_ZOOMINC);
	}
	if (*zoomPol == 0) *yz = (*yz - (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (*zoomPol == 1) *yz = (*yz + (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (_vbl_count % TRIANGLE01D_VBLSKIPMOVE == 0) *x += TRIANGLES_XINC;
	change_sprite_pos(id, *x, fixtoi(*y), tileSizeClipping(16));
	change_sprite_zoom(id, 15, *yz, tileSizeNB(512));
	if (*yz <= 0x00 + TRIANGLES_ZOOMINC) *zoomPol = 1;
	if (*yz >= 0xFF - TRIANGLES_ZOOMINC) *zoomPol = 0;
}
void triangle02Dmove(WORD id, WORD *x, FIXED *y, WORD *yz, WORD *zoomPol){
	if (*zoomPol == 0) {
		*y = fadd(*y, 8192 * TRIANGLES_ZOOMINC);
	}
	else{
		*y = fadd(*y, -8192 * TRIANGLES_ZOOMINC);
	}
	if (*zoomPol == 0) *yz = (*yz - (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (*zoomPol == 1) *yz = (*yz + (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (_vbl_count % TRIANGLE02D_VBLSKIPMOVE == 0) *x += TRIANGLES_XINC;
	change_sprite_pos(id, *x, fixtoi(*y), tileSizeClipping(48));
	change_sprite_zoom(id, 15, *yz, tileSizeNB(512));
	if (*yz <= 0x00 + TRIANGLES_ZOOMINC) *zoomPol = 1;
	if (*yz >= 0xFF - TRIANGLES_ZOOMINC) *zoomPol = 0;
}
void triangle03Dmove(WORD id, WORD *x, FIXED *y, WORD *yz, WORD *zoomPol){
	if (*zoomPol == 0) {
		*y = fadd(*y, 12288 * TRIANGLES_ZOOMINC);
	}
	else{
		*y = fadd(*y, -12288 * TRIANGLES_ZOOMINC);
	}
	if (*zoomPol == 0) *yz = (*yz - (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (*zoomPol == 1) *yz = (*yz + (1 * TRIANGLES_ZOOMINC)) & 0xFF;
	if (_vbl_count % TRIANGLE03D_VBLSKIPMOVE == 0) *x += TRIANGLES_XINC;
	change_sprite_pos(id, *x, fixtoi(*y), tileSizeClipping(48));
	change_sprite_zoom(id, 15, *yz, tileSizeNB(512));
	if (*yz <= 0x00 + TRIANGLES_ZOOMINC) *zoomPol = 1;
	if (*yz >= 0xFF - TRIANGLES_ZOOMINC) *zoomPol = 0;
}
