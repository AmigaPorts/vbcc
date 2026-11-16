	.file	"tolower.s"
	.text
	.align	3
	.global	tolower
	.type	tolower,@function
tolower:
	lis	r4,__ctype@ha
	addi	r4,r4,__ctype@l
	addi	r4,r4,1
	lbzx	r5,r4,r3
	andi.	r5,r5,1
	beqlr
	addi	r3,r3,32
	blr
	.size	tolower,32
