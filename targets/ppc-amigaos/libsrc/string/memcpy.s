	.file	"memcpy.s"
	.text
	.align	3
	.global	memcpy
	.type	memcpy,@function
memcpy:
	cmpwi	r5,0
	beqlr
	mr	r6,r3
	cmplwi	r5,16
	blt .L70
	clrlwi	r7,r6,30
	clrlwi.	r8,r4,30
	cmpw	cr1,r7,r8
	bne cr1,.L44
	beq .L44
	li	r7,4
	subf	r7,r8,r7
	lwz	r0,0(r4)
	subf	r5,r7,r5
	add	r4,r4,r7
	stw	r0,0(r6)
	add	r6,r6,r7
.L44:
	srwi	r7,r5,2
	mtctr	r7
	addi	r4,r4,-4
	addi	r6,r6,-4
.L54:
	lwzu	r0,4(r4)
	stwu	r0,4(r6)
	bdnz .L54
	andi.	r5,r5,3
	beqlr
	addi	r4,r4,4
	addi	r6,r6,4
.L70:
	mtctr	r5
	addi	r6,r6,-1
	addi	r4,r4,-1
.L7c:
	lbzu	r0,1(r4)
	stbu	r0,1(r6)
	bdnz .L7c
	blr
	.size	memcpy,140
