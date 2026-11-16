	.file	"_chkabort.s"
	.text
	.align	4
	.global	_chkabort
	.type	_chkabort,@function
_chkabort:
	stwu	r1,-16(r1)
	mflr	r0
	stw	r0,20(r1)
	lis	r11,IExec@ha
	lwz	r3,IExec@l(r11)
	lwz	r0,288(r3)
	li	r4,0
	li	r5,4096
	mtlr	r0
	blrl
	andi.	r3,r3,4096
	beq+ .L38
	li	r3,20
	bl exit
.L38:
	lwz	r0,20(r1)
	addi	r1,r1,16
	mtlr	r0
	blr
	.size	_chkabort,72
