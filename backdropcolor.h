#ifndef BACKDROPCOLOR_H
#define BACKDROPCOLOR_H

#define BGCOLOR000	asm("move #0x1000,0x401FFE");
#define BGCOLOR001	asm("move #0x1111,0x401FFE");
#define BGCOLOR002	asm("move #0x1111,0x401FFE");
#define BGCOLOR003	asm("move #0x1112,0x401FFE");
#define BGCOLOR004	asm("move #0x1112,0x401FFE");
#define BGCOLOR005	asm("move #0x1122,0x401FFE");
#define BGCOLOR006	asm("move #0x1123,0x401FFE");
#define BGCOLOR007	asm("move #0x1123,0x401FFE");
#define BGCOLOR008	asm("move #0x1124,0x401FFE");
#define BGCOLOR009	asm("move #0x1124,0x401FFE");
#define BGCOLOR010	asm("move #0x1124,0x401FFE");
#define BGCOLOR011	asm("move #0x1124,0x401FFE");
#define BGCOLOR012	asm("move #0x1134,0x401FFE");
#define BGCOLOR013	asm("move #0x1145,0x401FFE");
#define BGCOLOR014	asm("move #0x1156,0x401FFE");
#define BGCOLOR015	asm("move #0x1157,0x401FFE"); //final color

void backdropColorNext(WORD *curColorTableIndex);

#endif
