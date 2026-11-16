	.file	"longjmp.s"
	.text
	.align	3
	.global	longjmp
	.type	longjmp,@function
longjmp:
	lmw	r9,0(r3)
	lfd	f14,96(r3)
	lfd	f15,104(r3)
	lfd	f16,112(r3)
	lfd	f17,120(r3)
	lfd	f18,128(r3)
	lfd	f19,136(r3)
	lfd	f20,144(r3)
	lfd	f21,152(r3)
	lfd	f22,160(r3)
	lfd	f23,168(r3)
	lfd	f24,176(r3)
	lfd	f25,184(r3)
	lfd	f26,192(r3)
	lfd	f27,200(r3)
	lfd	f28,208(r3)
	lfd	f29,216(r3)
	lfd	f30,224(r3)
	lfd	f31,232(r3)
	mr	r2,r9
	mr	r1,r10
	mtlr	r11
	mtcr	r12
	mr.	r3,r4
	bnelr
	li	r3,1
	blr
	.size	longjmp,108
