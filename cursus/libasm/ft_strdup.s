section		.text
global		_ft_strdup
extern		_ft_strlen
extern		_malloc
extern		_ft_strcpy

_ft_strdup:
			sub		rsp, 8
			cmp		rdi, 0
			je		error
			call	_ft_strlen
			add		rax, 1
			mov		qword [rsp], rdi
			mov		rdi, rax
			call	_malloc
			cmp		rax, 0
			je		error
			mov		rdi, rax
			mov		rsi, qword [rsp]
			call	_ft_strcpy
			jmp		end
	error:
			mov		rax, 0
			add		rsp, 8
			ret
	  end:
	  		add		rsp, 8
			ret
