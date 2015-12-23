#ifndef BACKDROPCOLOR_H
#define BACKDROPCOLOR_H

#define BGCOLOR000	asm("move #0x1000,0x401FFE");
#define BGCOLOR001	asm("move #0x3000,0x401FFE");
#define BGCOLOR002	asm("move #0x0011,0x401FFE");
#define BGCOLOR003	asm("move #0x1011,0x401FFE");
#define BGCOLOR004	asm("move #0x0012,0x401FFE");
#define BGCOLOR005	asm("move #0x1022,0x401FFE");
#define BGCOLOR006	asm("move #0x5023,0x401FFE");
#define BGCOLOR007	asm("move #0x4034,0x401FFE");
#define BGCOLOR008	asm("move #0x4035,0x401FFE");
#define BGCOLOR009	asm("move #0x5045,0x401FFE");
#define BGCOLOR010	asm("move #0x0157,0x401FFE");
#define BGCOLOR011	asm("move #0x1157,0x401FFE"); //final color

void backdropColorNext(WORD *curColorTableIndex);

#endif
