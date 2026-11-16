	.file	"strlen.s"
	.text
	.align	3
	.global	strlen
	.type	strlen,@function
strlen:
	addi	r4,r3,-1
.L4:
	lbzu	r0,1(r4)
	cmpwi	r0,0
	bne .L4
	subf	r3,r3,r4
	blr
	.size	strlen,24
