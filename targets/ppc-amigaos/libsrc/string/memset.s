	.file	"memset.s"
	.text
	.align	3
	.global	memset
	.type	memset,@function
memset:
	cmpwi	r5,0
	beqlr
	mr	r6,r3
	cmplwi	r5,16
	blt .L64
	rlwimi	r4,r4,8,16,23
	rlwimi	r4,r4,16,0,15
	clrlwi	r7,r6,30
	clrlwi.	r8,r4,30
	cmpw	cr1,r7,r8
	bne cr1,.L44
	beq .L44
	li	r7,4
	subf	r7,r8,r7
	subf	r5,r7,r5
	stw	r4,0(r6)
	add	r6,r6,r7
.L44:
	srwi	r7,r5,2
	mtctr	r7
	addi	r6,r6,-4
.L50:
	stwu	r4,4(r6)
	bdnz .L50
	andi.	r5,r5,3
	beqlr
	addi	r6,r6,4
.L64:
	mtctr	r5
	addi	r6,r6,-1
.L6c:
	stbu	r4,1(r6)
	bdnz .L6c
	blr
	.size	memset,120
