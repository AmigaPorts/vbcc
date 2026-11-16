	.file	"_flttosint64.s"
	.text
	.align	3
	.global	__flt64tosint64
	.type	__flt64tosint64,@function
__flt64tosint64:
	.global	__flt32tosint64
	.type	__flt32tosint64,@function
__flt32tosint64:
	mflr	r0
	stw	r0,4(r1)
	stwu	r1,-16(r1)
	lis	r11,_dconst0@ha
	lfd	f0,_dconst0@l(r11)
	fcmpu	cr1,f12,f0
	bge cr1,.L54
	lis	r11,.Ldata0@ha
	lfd	f0,.Ldata0@l(r11)
	fcmpu	cr1,f12,f0
	cror	4*cr1+so,4*cr1+eq,4*cr1+lt
	bns cr1,.L3c
	li	r4,0
	lis	r3,-32768
	b .L80
.L3c:
	fneg	f12,f12
	crset	4*cr1+eq
	bl __flt64touint64
	subfic	r4,r4,0
	subfze	r3,r3
	b .L80
.L54:
	lis	r11,_dconst2e19@ha
	lfd	f0,_dconst2e19@l(r11)
	fcmpu	cr1,f12,f0
	cror	4*cr1+so,4*cr1+eq,4*cr1+gt
	bso cr1,.L74
	crset	4*cr1+eq
	bl __flt64touint64
	b .L80
.L74:
	li	r4,-1
	lis	r0,32767
	ori	r3,r0,65535
.L80:
	addi	r1,r1,16
	lwz	r0,4(r1)
	mtlr	r0
	blr
	.size	__flt64tosint64,144
	.size	__flt32tosint64,144
	.data
	.align	3
.Ldata0:
	.byte	195
	.byte	224
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
