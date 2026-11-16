	.file	"_modsint64.s"
	.text
	.align	3
	.global	__modsint64
	.type	__modsint64,@function
__modsint64:
	mflr	r0
	stw	r0,4(r1)
	stwu	r1,-16(r1)
	stw	r31,8(r1)
	srawi.	r11,r5,31
	beq .L20
	subfic	r6,r6,0
	subfze	r5,r5
.L20:
	srawi.	r31,r3,31
	beq .L30
	subfic	r4,r4,0
	subfze	r3,r3
.L30:
	bl __moduint64
	mr.	r0,r31
	beq .L44
	subfic	r4,r4,0
	subfze	r3,r3
.L44:
	lwz	r31,8(r1)
	addi	r1,r1,16
	lwz	r0,4(r1)
	mtlr	r0
	blr
	.size	__modsint64,88
