.file   "a.cc"
.text
.globl  main
.type   main, @function
main:
.LFB0:
.cfi_startproc
pushq   %rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq    %rsp, %rbp
	.cfi_def_cfa_register 6
	movb    $48, -1(%rbp)
	movb    $1, -2(%rbp)
	movzbl  -2(%rbp), %edx
	movzbl  -1(%rbp), %eax
	addl    %edx, %eax
	movb    %al, -3(%rbp)
	movl    $0, %eax
	popq    %rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
	.LFE0:
	.size   main, .-main
	.ident  "GCC: (GNU) 4.8.2"
	.section        .note.GNU-stack,"",@progbits
