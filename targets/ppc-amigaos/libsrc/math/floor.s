	.file	"floor.s"
	.text
	.align	3
	.global	floor
	.type	floor,@function
floor:
	stwu	r1,-16(r1)
	mffs	f2
	mtfsfi	7,3
	fctiw	f0,f1
	stfd	f0,8(r1)
	mtfsf	1,f2
	lwz	r11,12(r1)
	lis	r12,17200
	stw	r12,8(r1)
	xoris	r12,r11,32768
	stw	r12,12(r1)
	lfd	f1,8(r1)
	lis	r11,__int2flt@ha
	lfd	f0,__int2flt@l(r11)
	fsub	f1,f1,f0
	addi	r1,r1,16
	blr
	.size	floor,68
