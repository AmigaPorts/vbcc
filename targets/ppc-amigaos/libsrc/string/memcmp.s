	.file	"memcmp.s"
	.text
	.align	3
	.global	memcmp
	.type	memcmp,@function
memcmp:
	mtctr	r5
	addi	r6,r3,-1
	addi	r4,r4,-1
	mr.	r3,r5
	beqlr
.L14:
	lbzu	r3,1(r6)
	lbzu	r5,1(r4)
	subf.	r3,r5,r3
	bnelr
	bdnz .L14
	blr
	.size	memcmp,44
