section		.text
global		_ft_read
extern		___error

_ft_read:
			sub rsp, 8
			mov rax, 0x2000003
			syscall
			jc ERROR
			jmp end
	ERROR:
			mov qword [rsp], rax
			call ___error
			mov rcx, qword [rsp]
			mov [rax], rcx
			mov rax, -1
	  end:
			add rsp, 8
			ret
