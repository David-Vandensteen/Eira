	.globl	playcdda

playcdda:
	clr.w   d0
	move.w  #0x0002,d0
	jsr     0xC0056A
	