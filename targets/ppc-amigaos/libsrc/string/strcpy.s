	.file	"strcpy.s"
	.text
	.align	3
	.global	strcpy
	.type	strcpy,@function
strcpy:
	addi	r5,r3,-1
	addi	r4,r4,-1
.L8:
	lbzu	r0,1(r4)
	stbu	r0,1(r5)
	cmpwi	r0,0
	bne .L8
	blr
	.size	strcpy,28
