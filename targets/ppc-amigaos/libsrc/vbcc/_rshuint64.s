	.file	"_rshuint64.s"
	.text
	.align	3
	.global	__rshuint64
	.type	__rshuint64,@function
__rshuint64:
	subfic	r11,r5,32
	cmpwi	r11,0
	bge+ .L1c
	neg	r11,r11
	srw	r4,r3,r11
	li	r3,0
	blr
.L1c:
	slw	r0,r3,r11
	srw	r4,r4,r5
	srw	r3,r3,r5
	or	r4,r4,r0
	blr
	.size	__rshuint64,48
