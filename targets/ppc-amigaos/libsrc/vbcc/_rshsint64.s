	.file	"_rshsint64.s"
	.text
	.align	3
	.global	__rshsint64
	.type	__rshsint64,@function
__rshsint64:
	subfic	r11,r5,32
	cmpwi	r11,0
	bge+ .L1c
	neg	r11,r11
	sraw	r4,r3,r11
	srawi	r3,r3,31
	blr
.L1c:
	slw	r0,r3,r11
	srw	r4,r4,r5
	sraw	r3,r3,r5
	or	r4,r4,r0
	blr
	.size	__rshsint64,48
