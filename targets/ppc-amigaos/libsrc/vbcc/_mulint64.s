	.file	"_mulint64.s"
	.text
	.align	3
	.global	__mulint64
	.type	__mulint64,@function
__mulint64:
	mr	r11,r3
	mr	r12,r4
	mulhwu	r3,r12,r6
	mullw	r4,r12,r6
	mullw	r11,r11,r6
	add	r3,r3,r11
	mullw	r12,r12,r5
	add	r3,r3,r12
	blr
	.size	__mulint64,36
