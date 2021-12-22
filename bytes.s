	.section .data
msg:	.int 0x6c6c6548,0x57202c6f,0x646c726f,0xa21
	.section .text
	.globl bytes
bytes:	leaq	msg,%rdi
	call	func
	xorl	%edi,%edi
	movl	$0x3c,%eax
	syscall
func:	pushq	%rbp
	movq	%rsp,%rbp
	addq	$-0x10,%rsp
	movq	%rdi,-0x10(%rbp)
	xorl	%eax,%eax
	movl	%eax,-0x4(%rbp)
	movq	-0x10(%rbp),%rsi
t:	cmpb	$0,(%rsi)
	je	e
	xorb	$0x42,(%rsi)
	movb	(%rsi),%al
	inc	%rsi
	addl	%eax,-0x4(%rbp)
	jmp	t
e:	movl	-0x4(%rbp),%eax
	addq	$0x10,%rsp
	popq	%rbp
	ret
