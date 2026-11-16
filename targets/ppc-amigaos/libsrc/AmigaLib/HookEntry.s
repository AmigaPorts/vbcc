	.file	"HookEntry.s"
	.text
	.align	3
.Ltext0:
	addi	r12,r1,-16
	clrrwi	r12,r12,4
	stw	r1,0(r12)
	mr	r1,r12
	stw	r11,12(r1)
	lwz	r12,12(r3)
	mtctr	r12
	bctrl
	lwz	r11,12(r1)
	mtlr	r11
	lwz	r1,0(r1)
	blrl
	.long	.Ldata13	# UNHANDLED R_PPC_ADDR32 .Ldata13
	.long	0x0002013c
	.byte	3
	.byte	0
	.byte	4
	.data
	.global	HookEntry
	.type	HookEntry,@function
	.size	HookEntry,19
HookEntry:
	.byte	78
	.byte	248
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.long	.Ltext0
	.byte	4
	.byte	1
	.byte	60
	.byte	3
	.byte	32
	.byte	4
	.byte	40
	.byte	5
	.byte	36
.Ldata13:
	.byte	78
	.byte	117
