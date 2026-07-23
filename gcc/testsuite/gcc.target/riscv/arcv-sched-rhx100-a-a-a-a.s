	.file	"arcv-sched-rhx100-a-a-a-a.c"
	.option nopic
	.attribute arch, ""
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	f_a_a_a_a
	.type	f_a_a_a_a, @function
f_a_a_a_a:
	xori	t0,a5,3
	xori	t1,a4,4
	xori	t2,a3,5
	xori	a0,a2,6
	ret
	.size	f_a_a_a_a, .-f_a_a_a_a
	.ident	"GCC: (g853d1dfcf69-dirty) 17.0.0 20260716 (experimental)"
	.section	.note.GNU-stack,"",@progbits
