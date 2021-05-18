section		.text
extern		_malloc
global		_ft_list_push_front

_ft_list_push_front:
			sub		rsp, 16
			mov		qword [rsp], rdi
			mov		qword [rsp + 8], rsi
			mov		rdi, 16
			call	_malloc
			mov		rdi, qword [rsp]
			mov		rsi, qword [rsp + 8]
			cmp		rax, 0
			je		end
			mov		[rax], rsi
			mov		rcx, [rdi]
			mov		[rax + 8], rcx
			mov		[rdi], rax
end:
			add		rsp, 16
			ret
