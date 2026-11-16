	.file	"_sint64toflt.s"
	.text
	.align	3
	.global	__sint64toflt64
	.type	__sint64toflt64,@function
__sint64toflt64:
	.global	__sint64toflt32
	.type	__sint64toflt32,@function
__sint64toflt32:
	stwu	r1,-16(r1)
	cmpwi	cr1,r3,0
	bge cr1,.L14
	subfic	r4,r4,0
	subfze	r3,r3
.L14:
	stw	r3,12(r1)
	lis	r0,17200
	stw	r0,8(r1)
	lfd	f12,8(r1)
	stw	r4,12(r1)
	lfd	f13,8(r1)
	lis	r11,.Ldata8@ha
	lfd	f0,.Ldata8@l(r11)
	fsub	f12,f12,f0
	fsub	f13,f13,f0
	lis	r11,.Ldata0@ha
	lfd	f0,.Ldata0@l(r11)
	fmadd	f12,f12,f0,f13
	addi	r1,r1,16
	bgelr	cr1
	fneg	f12,f12
	blr
	.size	__sint64toflt64,88
	.size	__sint64toflt32,88
	.data
	.align	3
.Ldata0:
	.global	_dconst41f
	.type	_dconst41f,@object
	.size	_dconst41f,8
_dconst41f:
	.byte	65
	.byte	240
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Ldata8:
	.byte	67
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
