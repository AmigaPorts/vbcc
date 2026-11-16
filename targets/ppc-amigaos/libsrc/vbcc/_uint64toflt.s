	.file	"_uint64toflt.s"
	.text
	.align	3
	.global	__uint64toflt64
	.type	__uint64toflt64,@function
__uint64toflt64:
	.global	__uint64toflt32
	.type	__uint64toflt32,@function
__uint64toflt32:
	stwu	r1,-16(r1)
	lis	r0,17200
	stw	r3,12(r1)
	stw	r0,8(r1)
	lfd	f13,8(r1)
	stw	r4,12(r1)
	lfd	f12,8(r1)
	lis	r11,.Ldata8@ha
	lfd	f0,.Ldata8@l(r11)
	fsub	f13,f13,f0
	fsub	f12,f12,f0
	lis	r11,.Ldata0@ha
	lfd	f0,.Ldata0@l(r11)
	fmadd	f12,f13,f0,f12
	addi	r1,r1,16
	blr
	.size	__uint64toflt64,64
	.size	__uint64toflt32,64
	.data
	.align	3
.Ldata0:
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
