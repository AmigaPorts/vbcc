	.file	"toupper.s"
	.text
	.align	3
	.global	toupper
	.type	toupper,@function
toupper:
	lis	r4,__ctype@ha
	addi	r4,r4,__ctype@l
	addi	r4,r4,1
	lbzx	r5,r4,r3
	andi.	r5,r5,2
	beqlr
	addi	r3,r3,-32
	blr
	.size	toupper,32
