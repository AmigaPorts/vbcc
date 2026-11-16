	.file	"__stack_check.s"
	.text
	.align	3
	.global	__stack_check
	.type	__stack_check,@function
__stack_check:
	stwu	r1,-16(r1)
	stw	r11,8(r1)
	stw	r12,12(r1)
	subf	r11,r12,r1
	lis	r12,__stackPtr@ha
	lwz	r12,__stackPtr@l(r12)
	subf	r12,r11,r12
	lis	r11,__stack_usage@ha
	lwz	r11,__stack_usage@l(r11)
	cmplw	r12,r11
	ble+ .L34
	lis	r11,__stack_usage@ha
	stw	r12,__stack_usage@l(r11)
.L34:
	lwz	r11,8(r1)
	lwz	r12,12(r1)
	addi	r1,r1,16
	blr
	.size	__stack_check,68
