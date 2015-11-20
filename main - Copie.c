
#include <stdlib.h>
#include <video.h>


extern  PALETTE	 palettes;
//extern  TILEMAP	 playership[];
extern	TILEMAP	megaman[];
extern  TILEMAP backgrounda;
extern  TILEMAP background;



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
	// Var must be declared before setPalette
	int x = 0;
	int y = 0;
    int xBack = 2;
    int yBack = 1;
	int xInc = 1;
	int yInc = 1;
	int xz = 1;
	int yz = 1;
	int xzInc = 1;
	int yzInc = 1;

	int i = 0;
	//
	setpalette(0, 1, (const PPALETTE)&palettes);
	setpalette(0, 2, (const PPALETTE)&palettes);
    setpalette(0, 3, (const PPALETTE)&palettes);
    setpalette(0, 4, (const PPALETTE)&palettes);


    playCDDA();

	while(1){
		wait_vbl();
		//textoutf(x, 10, 0, 0, " Vbl Counter:%d ", _vbl_count);
		set_current_sprite(3);
        write_sprite_data(8 + xBack , 0 + yBack, 255, 255, 32, 19, (const PTILEMAP)&background);
        write_sprite_data(8, 0, xz, yz, 32, 19, (const PTILEMAP)&backgrounda); //grid

        write_sprite_data(30 + x, y - 100, 255, 255, 10, 10, (const PTILEMAP)&megaman[0]);
        write_sprite_data(40, 100, xz, yz, 10, 10, (const PTILEMAP)&megaman[0]);
        
		i = 0;

        
        if (xz >= 255 - xzInc){ xzInc = -1; }
        if (xz <= 0   - xzInc){ xzInc =  1; }
        if (yz >= 255 - yzInc){ yzInc = -2; }
        if (yz <= 0   - yzInc){ yzInc =  2; }

		if (y > 200){ yInc = -1; }
		if (y < 50)	{ yInc = 1;  }
		y += yInc;
        
        
        if(_vbl_count > 190){
            yBack = 0;
            xBack = 0;
        }
        
        if(_vbl_count % 2 == 0 && _vbl_count < 190){
            yBack = !yBack;
        }
        if(_vbl_count % 4 == 0){
            if(xBack == 2 ) { xBack = -2; }else{
                if(xBack == -2) xBack =  2;
            }
        }

        if(_vbl_count % 5 == 0){
            xz += xzInc;
            yz += yzInc;
        }

		if(_vbl_count % 2 == 0){
			x += xInc;				
			if (x > 100){ xInc = -1; }
			if (x < 5){ xInc = 1; }
		}
	}
}