	.file	"frexp.s"
	.text
	.align	3
	.global	frexp
	.type	frexp,@function
frexp:
	stwu	r1,-16(r1)
	stfd	f1,8(r1)
	lwz	r4,8(r1)
	li	r0,1022
	clrlwi	r6,r4,1
	mr	r5,r4
	cmpwi	r6,0
	beq .L30
	rlwimi	r4,r0,20,1,11
	stw	r4,8(r1)
	rlwinm	r5,r5,12,21,31
	addi	r5,r5,-1022
.L30:
	stw	r5,0(r3)
	lfd	f1,8(r1)
	addi	r1,r1,16
	blr
	.size	frexp,64
