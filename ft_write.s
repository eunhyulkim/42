section		.text
global		_ft_write
extern		___error

_ft_write:
			sub rsp, 8
			mov	r8, rdx
			mov rax, 0x2000004
			syscall
			jc error
			jmp end
	error:
			mov qword [rsp], rax
			call ___error
			mov rcx, qword [rsp]
			mov [rax], rcx
			mov rax, -1
			jmp exit
	 end:
	 		mov rax, r8
			jmp exit
	exit:
			add rsp, 8
			ret

