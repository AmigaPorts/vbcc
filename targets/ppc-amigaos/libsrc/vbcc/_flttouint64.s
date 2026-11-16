	.file	"_flttouint64.s"
	.text
	.align	3
	.global	__flt64touint64
	.type	__flt64touint64,@function
__flt64touint64:
	.global	__flt32touint64
	.type	__flt32touint64,@function
__flt32touint64:
	mflr	r0
	stw	r0,4(r1)
	stwu	r1,-32(r1)
	stfd	f31,24(r1)
	stw	r31,16(r1)
	fmr	f31,f12
	lis	r11,.Ldata0@ha
	lfd	f0,.Ldata0@l(r11)
	fcmpu	cr1,f31,f0
	blt cr1,.L3c
	lis	r11,.Ldata8@ha
	lfd	f0,.Ldata8@l(r11)
	fcmpu	cr1,f31,f0
	cror	4*cr1+so,4*cr1+eq,4*cr1+gt
	bns cr1,.L48
.L3c:
	li	r4,-1
	li	r3,-1
	b .L148
.L48:
	lis	r11,.Ldata10@ha
	lfd	f0,.Ldata10@l(r11)
	fsub	f0,f31,f0
	lis	r11,_dconst41f@ha
	lfd	f13,_dconst41f@l(r11)
	fdiv	f0,f0,f13
	lis	r11,.Ldata18@ha
	lfd	f13,.Ldata18@l(r11)
	fcmpu	cr1,f0,f13
	cror	4*cr1+so,4*cr1+eq,4*cr1+gt
	bso cr1,.L84
	fctiwz	f0,f0
	stfd	f0,8(r1)
	lwz	r31,12(r1)
	b .L98
.L84:
	fsub	f0,f0,f13
	fctiwz	f0,f0
	stfd	f0,8(r1)
	lwz	r31,12(r1)
	xoris	r31,r31,32768
.L98:
	cmplwi	cr1,r31,0
	blt cr1,.Lb4
	mr	r3,r31
	li	r4,0
	crclr	4*cr1+eq
	bl __sint64toflt64
	b .Ld8
.Lb4:
	li	r3,0
	li	r4,0
	slwi	r12,r31,31
	srwi	r11,r31,1
	or	r3,r3,r11
	or	r4,r4,r12
	crclr	4*cr1+eq
	bl __sint64toflt64
	fadd	f12,f12,f12
.Ld8:
	fsub	f31,f31,f12
	lis	r11,.Ldata0@ha
	lfd	f0,.Ldata0@l(r11)
	fcmpu	cr1,f31,f0
	lis	r11,.Ldata20@ha
	lfd	f12,.Ldata20@l(r11)
	bge cr1,.Lfc
	addi	r31,r31,-1
	fadd	f31,f31,f12
.Lfc:
	fcmpu	cr1,f31,f12
	ble cr1,.L10c
	addi	r31,r31,1
	fsub	f31,f31,f12
.L10c:
	lis	r11,.Ldata18@ha
	lfd	f13,.Ldata18@l(r11)
	fcmpu	cr1,f31,f13
	cror	4*cr1+so,4*cr1+eq,4*cr1+gt
	bso cr1,.L130
	fctiwz	f0,f31
	stfd	f0,8(r1)
	lwz	r4,12(r1)
	b .L144
.L130:
	fsub	f0,f31,f13
	fctiwz	f0,f0
	stfd	f0,8(r1)
	lwz	r4,12(r1)
	xoris	r4,r4,32768
.L144:
	mr	r3,r31
.L148:
	lwz	r31,16(r1)
	lfd	f31,24(r1)
	addi	r1,r1,32
	lwz	r0,4(r1)
	mtlr	r0
	blr
	.size	__flt64touint64,352
	.size	__flt32touint64,352
	.data
	.align	3
.Ldata0:
	.global	_dconst0
	.type	_dconst0,@object
	.size	_dconst0,8
_dconst0:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Ldata8:
	.global	_dconst2e19
	.type	_dconst2e19,@object
	.size	_dconst2e19,8
_dconst2e19:
	.byte	67
	.byte	240
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Ldata10:
	.byte	64
	.byte	32
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Ldata18:
	.byte	65
	.byte	224
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Ldata20:
	.byte	65
	.byte	239
	.byte	255
	.byte	255
	.byte	255
	.byte	224
	.byte	0
	.byte	0
