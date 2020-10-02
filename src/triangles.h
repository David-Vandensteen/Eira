#ifndef TRIANGLES_H
#define TRIANGLES_H

#define	TRIANGLE01U_VBLSKIPMOVE		5
#define	TRIANGLE02U_VBLSKIPMOVE		10
#define	TRIANGLE03U_VBLSKIPMOVE		15
#define	TRIANGLE01D_VBLSKIPMOVE		5
#define	TRIANGLE02D_VBLSKIPMOVE		10
#define	TRIANGLE03D_VBLSKIPMOVE		15

#define TRIANGLES_ZOOMINC			2
#define TRIANGLES_XINC				-1


#define TRIANGLE01U_INIT 	WORD		triangle01U_id; \
							WORD		triangle01U_x = 0; \
							WORD		triangle01U_yz = 0xFF; \
							WORD		triangle01U_zoomPol = 0; \

#define TRIANGLE02U_INIT	WORD		triangle02U_id; \
							WORD		triangle02U_x = 0; \
							WORD		triangle02U_yz = 0xFF; \
							WORD		triangle02U_zoomPol = 0; \

#define TRIANGLE03U_INIT	WORD		triangle03U_id; \
							WORD		triangle03U_x = 0; \
							WORD		triangle03U_yz = 0xFF; \
							WORD		triangle03U_zoomPol = 0; \

#define	TRIANGLE01D_INIT	WORD		triangle01D_id; \
							WORD		triangle01D_x = 0; \
							FIXED		triangle01D_y = 208 * FIXEDCOEF; \
							WORD		triangle01D_yz = 0xFF; \
							WORD		triangle01D_zoomPol = 0; \

#define	TRIANGLE02D_INIT	WORD		triangle02D_id; \
							WORD		triangle02D_x = 0; \
							FIXED		triangle02D_y = 192 * FIXEDCOEF; \
							WORD		triangle02D_yz = 0xFF; \
							WORD		triangle02D_zoomPol = 0; \

#define	TRIANGLE03D_INIT	WORD		triangle03D_id; \
							WORD		triangle03D_x = 0; \
							FIXED		triangle03D_y = 176 * FIXEDCOEF; \
							WORD		triangle03D_yz = 0xFF; \
							WORD		triangle03D_zoomPol = 0; \

void triangle01Dmove(WORD id, WORD *x, FIXED *y, WORD *yz, WORD *zoomPol);
void triangle02Dmove(WORD id, WORD *x, FIXED *y, WORD *yz, WORD *zoomPol);
void triangle03Dmove(WORD id, WORD *x, FIXED *y, WORD *yz, WORD *zoomPol);

void triangle01Umove(WORD id, WORD *x, WORD *yz, WORD *zoomPol);
void triangle02Umove(WORD id, WORD *x, WORD *yz, WORD *zoomPol);
void triangle03Umove(WORD id, WORD *x, WORD *yz, WORD *zoomPol);

#endif
