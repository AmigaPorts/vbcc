	.file	"fabs.s"
	.text
	.align	3
	.global	fabs
	.type	fabs,@function
fabs:
	fabs	f1,f1
	blr
	.size	fabs,8
