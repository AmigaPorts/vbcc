	.file	"_moduint64.s"
	.text
	.align	3
	.global	__moduint64
	.type	__moduint64,@function
__moduint64:
	stwu	r1,-16(r1)
	cmpwi	r3,0
	stw	r7,8(r1)
	cntlzw	r0,r3
	cntlzw	r11,r4
	stw	r8,12(r1)
	bne .L20
	addi	r0,r11,32
.L20:
	cmpwi	r5,0
	cntlzw	r11,r5
	cntlzw	r12,r6
	bne .L34
	addi	r11,r12,32
.L34:
	cmpw	r0,r11
	subfic	r12,r0,64
	bgt .Lf0
	addi	r11,r11,1
	subfic	r11,r11,64
	add	r0,r0,r11
	subf	r11,r11,r12
	mtctr	r11
	cmpwi	r11,32
	addi	r7,r11,-32
	blt .L6c
	srw	r8,r3,r7
	li	r7,0
	b .L80
.L6c:
	srw	r8,r4,r11
	subfic	r7,r11,32
	slw	r7,r3,r7
	or	r8,r8,r7
	srw	r7,r3,r11
.L80:
	cmpwi	r0,32
	addic	r11,r0,-32
	blt .L98
	slw	r3,r4,r11
	li	r4,0
	b .Lac
.L98:
	slw	r3,r3,r0
	subfic	r11,r0,32
	srw	r11,r4,r11
	or	r3,r3,r11
	slw	r4,r4,r0
.Lac:
	li	r12,-1
	addic	r7,r7,0
.Lb4:
	adde	r4,r4,r4
	adde	r3,r3,r3
	adde	r8,r8,r8
	adde	r7,r7,r7
	subfc	r0,r6,r8
	subfe.	r11,r5,r7
	blt .Ldc
	mr	r8,r0
	mr	r7,r11
	addic	r0,r12,1
.Ldc:
	bdnz .Lb4
	mr	r3,r7
	lwz	r7,8(r1)
	mr	r4,r8
	lwz	r8,12(r1)
.Lf0:
	addi	r1,r1,16
	blr
	.size	__moduint64,248
