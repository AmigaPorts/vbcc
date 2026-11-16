	.file	"setjmp.s"
	.text
	.align	3
	.global	setjmp
	.type	setjmp,@function
setjmp:
	mflr	r11
	mfcr	r12
	mr	r10,r1
	mr	r9,r2
	stmw	r9,0(r3)
	addi	r3,r3,88
	stfdu	f14,8(r3)
	stfdu	f15,8(r3)
	stfdu	f16,8(r3)
	stfdu	f17,8(r3)
	stfdu	f18,8(r3)
	stfdu	f19,8(r3)
	stfdu	f20,8(r3)
	stfdu	f21,8(r3)
	stfdu	f22,8(r3)
	stfdu	f23,8(r3)
	stfdu	f24,8(r3)
	stfdu	f25,8(r3)
	stfdu	f26,8(r3)
	stfdu	f27,8(r3)
	stfdu	f28,8(r3)
	stfdu	f29,8(r3)
	stfdu	f30,8(r3)
	stfdu	f31,8(r3)
	li	r3,0
	blr
	.size	setjmp,104
