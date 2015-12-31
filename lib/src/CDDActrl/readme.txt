   	.globl	playcdda

playcdda:
	clr.w   d0
	move.w  #0x0502,d0
	jsr     0xC0056A

	
* move.w  #0x0002,d0 // loop
		
* $00: Read track and loop
* $02: Pause ?
* $04: Read track and loop (confirmed)
* $05: Read track (loop ?)
* $06: Stop ? sent with track number = 0 (puzzled)
* $07: ? sent with track number = 0 (mutnat)
* Set $13A to $0000 if not using the Z80 RAM. Set to $FFFF if using the default $FEF8 value.