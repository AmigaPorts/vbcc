	.file	"memmove.s"
	.text
	.align	3
	.global	memmove
	.type	memmove,@function
memmove:
	cmpwi	r5,0
	beqlr
	cmplw	r3,r4
	blt .L78
	add	r6,r3,r5
	add	r4,r4,r5
	cmplwi	r5,16
	blt .L64
	clrlwi	r7,r6,30
	clrlwi.	r8,r4,30
	cmpw	cr1,r7,r8
	bne cr1,.L48
	beq .L48
	subf	r5,r7,r5
	mtctr	r7
.L3c:
	lbzu	r0,-1(r4)
	stbu	r0,-1(r6)
	bdnz .L3c
.L48:
	srwi	r7,r5,2
	mtctr	r7
.L50:
	lwzu	r0,-4(r4)
	stwu	r0,-4(r6)
	bdnz .L50
	andi.	r5,r5,3
	beqlr
.L64:
	mtctr	r5
.L68:
	lbzu	r0,-1(r4)
	stbu	r0,-1(r6)
	bdnz .L68
	blr
.L78:
	b memcpy
	.size	memmove,124
