	.file	"volatility.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	_80spaces
	.type	_80spaces, @function
_80spaces:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r25,lo8(80)
	ldi r24,lo8(32)
/* #APP */
 ;  9 "volatility.c" 1
	1:
	sbis 11, 5
	rjmp 1b
	out 12, r24
	ldi r24, 1
	/* result: r24
	   ucsra: 11
	   udre: 5
	   udr: 12
	   space: r24 */
 ;  0 "" 2
/* #NOAPP */
.L2:
	subi r25,lo8(-(-1))
	brne .L2
/* epilogue start */
	ret
	.size	_80spaces, .-_80spaces
	.ident	"GCC: (GNU) 5.3.0"
