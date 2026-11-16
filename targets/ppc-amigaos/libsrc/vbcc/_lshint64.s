	.file	"_lshint64.s"
	.text
	.align	3
	.global	__lshint64
	.type	__lshint64,@function
__lshint64:
	subfic	r11,r5,32
	slw	r3,r3,r5
	srw	r0,r4,r11
	or	r3,r3,r0
	addi	r11,r5,-32
	slw	r0,r4,r11
	or	r3,r3,r0
	slw	r4,r4,r5
	blr
	.size	__lshint64,36
