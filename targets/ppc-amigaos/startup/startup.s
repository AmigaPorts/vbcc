	.file	"startup.s"
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
	stwu	r1,-192(r1)
	li	r11,0
	stmw	r13,36(r1)
	stw	r0,196(r1)
	stw	r11,8(r1)
	stw	r11,24(r1)
	stw	r11,28(r1)
	lis	r13,_LinkerDB@ha
	addi	r13,r13,_LinkerDB@l
	stw	r5,SysBase@sdarel(r13)
	lwz	r28,632(r5)
	stw	r28,IExec@sdarel(r13)
	lwz	r0,60(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	li	r4,0
	lwz	r0,260(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	mr	r26,r3
	lis	r4,.Lrodatad@ha
	addi	r4,r4,.Lrodatad@l
	li	r5,50
	lwz	r0,424(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	mr.	r4,r3
	beq .L3c4
	stw	r4,DOSBase@sdarel(r13)
	stw	r4,32(r1)
	lis	r5,.Lrodata19@ha
	addi	r5,r5,.Lrodata19@l
	li	r6,1
	li	r7,0
	lwz	r0,448(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	mr.	r27,r3
	beq .L3c4
	stw	r27,IDOS@sdarel(r13)
	lwz	r0,420(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	mr.	r24,r3
	beq .L2bc
	lwz	r0,456(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	mr	r20,r3
	addi	r3,r3,-1
	li	r14,3
	b .L104
.Lf8:
	cmpwi	r11,32
	bne+ .L104
	addi	r14,r14,1
.L104:
	lbzu	r11,1(r3)
	mr.	r11,r11
	bne .Lf8
	subf	r0,r20,r3
	mtctr	r0
.L118:
	lbzu	r11,-1(r3)
	cmplwi	r11,32
	bdnzf gt,.L118
	addi	r3,r3,1
	subf	r21,r20,r3
	lwz	r3,16(r24)
	slwi	r3,r3,2
	lbz	r16,0(r3)
	slwi	r15,r14,2
	add	r4,r15,r16
	add	r4,r4,r21
	addi	r4,r4,11
	lis	r5,1
	ori	r5,r5,0
	lwz	r0,112(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	mr.	r25,r3
	beq .L3a8
	stw	r25,8(r1)
	addi	r14,r14,-1
	stw	r14,4(r25)
	addi	r22,r25,8
	add	r23,r22,r15
	stw	r23,0(r25)
	mr	r4,r23
	addi	r5,r16,1
	stw	r23,0(r22)
	add	r23,r23,r5
	lwz	r0,484(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	li	r0,0
	li	r15,1
	addi	r20,r20,-1
	addi	r23,r23,-1
	mr.	r21,r21
	bne+ .L1c8
	b .L25c
.L1bc:
	stbu	r0,1(r23)
.L1c0:
	addic.	r21,r21,-1
	beq .L25c
.L1c8:
	lbzu	r11,1(r20)
	cmpwi	r11,32
	ble- .L1c0
	cmpw	r15,r14
	beq .L25c
	addi	r12,r23,1
	stwu	r12,4(r22)
	addi	r15,r15,1
	cmpwi	r11,34
	beq .L210
.L1f0:
	stbu	r11,1(r23)
	addic.	r21,r21,-1
	beq .L25c
	lbzu	r11,1(r20)
	cmpwi	r11,32
	bgt .L1f0
	b .L1bc
.L20c:
	stbu	r11,1(r23)
.L210:
	addic.	r21,r21,-1
	beq .L25c
	lbzu	r11,1(r20)
	cmpwi	r11,34
	beq- .L1bc
	cmpwi	r11,42
	bne .L20c
	addic.	r21,r21,-1
	beq .L25c
	lbzu	r11,1(r20)
	andi.	r12,r11,223
	cmpwi	r12,78
	bne .L24c
	li	r11,10
	b .L20c
.L24c:
	cmpwi	r12,69
	bne .L20c
	li	r11,27
	b .L20c
.L25c:
	stbu	r0,1(r23)
	stwu	r0,4(r22)
	lwz	r0,92(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	bl .L550
	stw	r3,_stdin@sdarel(r13)
	lwz	r0,96(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	bl .L550
	stw	r3,_stdout@sdarel(r13)
	lwz	r0,876(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	mr.	r3,r3
	bne .L2b0
	lwz	r3,_stdout@sdarel(r13)
.L2b0:
	stw	r3,_stderr@sdarel(r13)
	addi	r16,r25,8
	b .L3cc
.L2bc:
	bl .L5a0
	mr	r16,r3
	stw	r16,.Lsdata0@sdarel(r13)
	lwz	r4,32(r16)
	mr.	r4,r4
	bne .L2dc
	lis	r4,.Lrodata1e@ha
	addi	r4,r4,.Lrodata1e@l
.L2dc:
	li	r5,1006
	lwz	r0,76(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	mr.	r14,r3
	beq .L3a8
	stw	r14,.Lsbss0@sdarel(r13)
	stw	r14,_stdin@sdarel(r13)
	stw	r14,_stdout@sdarel(r13)
	stw	r14,_stderr@sdarel(r13)
	slwi	r3,r14,2
	lwz	r4,8(r3)
	mr.	r4,r4
	beq .L32c
	lwz	r0,444(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	stw	r3,24(r1)
.L32c:
	mr	r4,r14
	lwz	r0,280(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	stw	r3,12(r1)
	mr	r4,r14
	lwz	r0,284(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	stw	r3,16(r1)
	mr	r4,r14
	lwz	r0,880(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	stw	r3,20(r1)
	lwz	r3,36(r16)
	mr.	r3,r3
	beq .L3a0
	lwz	r4,0(r3)
	mr.	r4,r4
	beq .L3a0
	lwz	r0,140(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	stw	r3,28(r1)
.L3a0:
	li	r15,0
	b .L3cc
.L3a8:
	mr.	r24,r24
	bne .L3c4
	lwz	r12,.Lsdata0@sdarel(r13)
	mr.	r12,r12
	bne .L3c4
	bl .L5a0
	stw	r3,.Lsdata0@sdarel(r13)
.L3c4:
	li	r3,20
	b .L404
.L3cc:
	stmw	r13,112(r1)
	lwz	r0,58(r26)
	stw	r1,__stackPtr@sdarel(r13)
	stw	r0,__stackLower@sdarel(r13)
	li	r3,1
	bl __so_init
	mr	r3,r15
	mr	r4,r16
	bl __main
	li	r3,0
	b .L404
	.global	__exit
	.type	__exit,@function
__exit:
	lis	r11,__stackPtr@ha
	lwz	r1,__stackPtr@l(r11)
	lmw	r13,112(r1)
.L404:
	mr	r31,r3
	li	r3,0
	bl __so_init
	mr.	r27,r27
	beq .L528
	lwz	r25,.Lsbss0@sdarel(r13)
	mr.	r24,r24
	bne .L49c
	mr.	r25,r25
	beq .L49c
	lwz	r4,28(r1)
	mr.	r4,r4
	beq .L448
	lwz	r0,140(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
.L448:
	lwz	r4,12(r1)
	lwz	r0,280(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	lwz	r4,16(r1)
	lwz	r0,284(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	lwz	r4,20(r1)
	lwz	r0,880(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	lwz	r4,24(r1)
	mr.	r4,r4
	lwz	r0,444(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
.L49c:
	mr.	r4,r25
	beq .L4b4
	lwz	r0,80(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
.L4b4:
	lwz	r4,8(r1)
	mr.	r4,r4
	beq .L4d0
	lwz	r0,172(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
.L4d0:
	mr	r4,r27
	lwz	r0,456(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	lwz	r4,32(r1)
	lwz	r0,428(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	lwz	r14,.Lsdata0@sdarel(r13)
	mr.	r14,r14
	beq .L528
	lwz	r0,156(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	mr	r4,r14
	lwz	r0,336(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
.L528:
	lwz	r0,64(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	lwz	r0,196(r1)
	mr	r3,r31
	mtlr	r0
	lmw	r13,36(r1)
	addi	r1,r1,192
	blr
.L550:
	mr.	r3,r3
	bnelr
	lwz	r3,.Lsbss0@sdarel(r13)
	mr.	r3,r3
	bnelr
	mflr	r0
	stwu	r1,-16(r1)
	stw	r0,20(r1)
	lis	r4,.Lrodata1e@ha
	addi	r4,r4,.Lrodata1e@l
	li	r5,1006
	lwz	r0,76(r27)
	mr	r3,r27
	mtctr	r0
	bctrl
	stw	r3,.Lsbss0@sdarel(r13)
	lwz	r0,20(r1)
	addi	r1,r1,16
	mtlr	r0
	blr
.L5a0:
	mflr	r0
	stwu	r1,-16(r1)
	stw	r0,20(r1)
	addi	r4,r26,92
	lwz	r0,340(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	addi	r4,r26,92
	lwz	r0,324(r28)
	mr	r3,r28
	mtctr	r0
	bctrl
	lwz	r0,20(r1)
	addi	r1,r1,16
	mtlr	r0
	blr
	.size	__exit,12
	.size	_start,1016
	.section	.rodata
	.align	3
	.global	__vbcc_startup
	.size	__vbcc_startup,13
__vbcc_startup:
	.byte	115
	.byte	116
	.byte	97
	.byte	114
	.byte	116
	.byte	117
	.byte	112
	.byte	32
	.byte	86
	.byte	50
	.byte	46
	.byte	50
	.byte	0
.Lrodatad:
	.byte	100
	.byte	111
	.byte	115
	.byte	46
	.byte	108
	.byte	105
	.byte	98
	.byte	114
	.byte	97
	.byte	114
	.byte	121
	.byte	0
.Lrodata19:
	.byte	109
	.byte	97
	.byte	105
	.byte	110
	.byte	0
.Lrodata1e:
	.byte	78
	.byte	73
	.byte	76
	.byte	58
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section	.sdata
	.align	2
.Lsdata0:
	.global	__WBenchMsg
	.type	__WBenchMsg,@object
	.size	__WBenchMsg,4
__WBenchMsg:
	.global	WBenchMsg
	.type	WBenchMsg,@object
	.size	WBenchMsg,4
WBenchMsg:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section	.sbss
	.align	2
.Lsbss0:
	.space	4
	.comm	__stack_usage,4,4
	.comm	__stackLower,4,4
	.comm	__stackPtr,4,4
	.comm	_stderr,4,4
	.comm	_stdout,4,4
	.comm	_stdin,4,4
	.comm	IDOS,4,4
	.comm	DOSBase,4,4
	.comm	IExec,4,4
	.comm	SysBase,4,4
