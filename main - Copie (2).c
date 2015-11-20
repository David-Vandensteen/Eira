
#include <stdlib.h>
#include <video.h>

extern  PALETTE	 palettes;
//extern  TILEMAP logo_shadow;
extern	TILEMAP	background;


void playCDDA(){
	/*
        clr.w   d0
        move.w  #$0502,d0           ; starts playing CDDA track 2 with no looping
        jsr     BIOSF_CDDACMD
	*/
	asm("clr.w		%d0 \t");
	asm("move.w     #1282,%d0 \t");
	asm("jsr		12584298 \t");
}

int main(void){
	// Var must be declared before function call
	int zoom = 1;
	//
	setpalette(0, 1, (const PPALETTE)&palettes);
	setpalette(0, 2, (const PPALETTE)&palettes);
 //   setpalette(0, 3, (const PPALETTE)&palettes);
 //   setpalette(0, 4, (const PPALETTE)&palettes);


    playCDDA();

	while(1){
		wait_vbl();
		textoutf(10, 10, 0, 0, " Vbl Counter:%d ", _vbl_count);
		set_current_sprite(3);
        //write_sprite_data(8 , 0, 255, 255, 32, 19, (const PTILEMAP)&logo_shadow);
		write_sprite_data(0, -8, 15, 255, 32, 19, (const PTILEMAP)&background);

        //write_sprite_data(30 + x, y - 100, 255, 255, 10, 10, (const PTILEMAP)&megaman[0]);
        //write_sprite_data(40, 100, xz, yz, 10, 10, (const PTILEMAP)&megaman[0]);
		zoom++;
		//if(_vbl_count % 2 == 0){
		//}
	}
}
