	.file	"minstart.s"
	.text
	.align	2
	.global	_start
	.type	_start,@function
_start:
	b .Lc
	rlwinm.	r2,r18,8,13,1
	subfic	r1,r16,11833
.Lc:
	mflr	r0
	stwu	r1,-160(r1)
	stw	r0,164(r1)
	stmw	r13,8(r1)
	mr.	r31,r3
	beq .L30
	li	r0,0
	addi	r4,r4,-1
	stbx	r0,r3,r4
.L30:
	lis	r13,_LinkerDB@ha
	addi	r13,r13,_LinkerDB@l
	stw	r1,.Lsdata8@sdarel(r13)
	stw	r5,.Lsdata0@sdarel(r13)
	lwz	r3,632(r5)
	stw	r3,.Lsdata4@sdarel(r13)
	lwz	r0,60(r3)
	mtctr	r0
	bctrl
	mr	r3,r31
	bl main
	.global	exit
	.type	exit,@function
exit:
	lis	r11,.Lsdata8@ha
	lwz	r1,.Lsdata8@l(r11)
	mr	r31,r3
	lis	r11,.Lsdata4@ha
	lwz	r3,.Lsdata4@l(r11)
	lwz	r0,64(r3)
	mtctr	r0
	bctrl
	lwz	r0,164(r1)
	mr	r3,r31
	mtlr	r0
	lmw	r13,8(r1)
	addi	r1,r1,160
	blr
	.size	exit,56
	.size	_start,92
	.section	.rodata
	.align	3
	.global	__vbcc_startup
	.size	__vbcc_startup,14
__vbcc_startup:
	.byte	109
	.byte	105
	.byte	110
	.byte	115
	.byte	116
	.byte	97
	.byte	114
	.byte	116
	.byte	32
	.byte	86
	.byte	49
	.byte	46
	.byte	50
	.byte	0
	.byte	0
	.byte	0
	.section	.sdata
.Lsdata0:
	.global	SysBase
	.type	SysBase,@object
	.size	SysBase,4
SysBase:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Lsdata4:
	.global	IExec
	.type	IExec,@object
	.size	IExec,4
IExec:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.Lsdata8:
	.global	__stackPtr
	.type	__stackPtr,@object
	.size	__stackPtr,4
__stackPtr:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
