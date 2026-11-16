	.file	"_divsint64.s"
	.text
	.align	3
	.global	__divsint64
	.type	__divsint64,@function
__divsint64:
	mflr	r0
	stw	r0,4(r1)
	stwu	r1,-16(r1)
	stw	r31,8(r1)
	srawi.	r31,r5,31
	beq .L20
	subfic	r6,r6,0
	subfze	r5,r5
.L20:
	srawi.	r11,r3,31
	beq .L34
	subfic	r4,r4,0
	subfze	r3,r3
	xor	r31,r31,r11
.L34:
	bl __divuint64
	cmpwi	r31,0
	beq .L48
	subfic	r4,r4,0
	subfze	r3,r3
.L48:
	lwz	r31,8(r1)
	addi	r1,r1,16
	lwz	r0,4(r1)
	mtlr	r0
	blr
	.size	__divsint64,92
