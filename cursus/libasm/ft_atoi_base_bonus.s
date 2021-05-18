section			.text
global			_ft_atoi_base
extern			_ft_strlen

_ft_atoi_base:
				sub		rsp, 16
				mov		r9, rdi
				jmp		check_init
check_init:
				mov		qword [rsp], rdi
				cmp		rdi, 0
				je		handle_error
				cmp		rsi, 0
				je		handle_error
				mov		rdi, rsi
				call	_ft_strlen
				cmp		rax, 2
				jl		handle_error
				mov		rdi, rsi
				mov		rcx, rax
				mov		r8, rax
				jmp		check_base
_is_ban:
				mov		rax, 0
				mov		dl, BYTE [rdi + rsi - 1]
				cmp		dl, 32
				je		_ret_true
				cmp		dl, 43
				je		_ret_true
				cmp		dl, 45
				je		_ret_true
				cmp		dl, 33
				jl		_ret_true
				cmp		dl, 127
				jg		_ret_true
				ret
_is_duplex:
				mov		rax, 0
				cmp		rcx, 0
				je		_ret
				mov		dl, BYTE [rdi + rcx - 1]
				cmp		BYTE [rdi + rsi - 1], dl
				je		_ret_true
				loop	_is_duplex
				ret
check_base:
				mov		rsi, rcx
				call	_is_ban
				cmp		rax, 1
				je		handle_error
				mov		qword [rsp + 8], rcx
				sub		rcx, 1
				call	_is_duplex
				mov		rcx, qword [rsp + 8]
				cmp		rax, 1
				je		handle_error
				loop	check_base
_pre_white:
				mov		rsi, rdi
				mov		rdi, qword [rsp]
		  		mov		rcx, 0
				jmp		skip_white
skip_white:
				mov		dl, BYTE [rdi + rcx]
				cmp		dl, 0
				je		_pre_sign
				inc		rcx
				cmp		dl, 32
				je		skip_white
				dec		rcx
				cmp		dl, 13
				jg		_pre_sign
				cmp		dl, 9
				jl		_pre_sign
				inc		rcx
				jmp		skip_white
_pre_sign:
				mov		r10, 1
				jmp		skip_sign
_set_sign:
				imul	r10, -1
				jmp		skip_sign
skip_sign:
				mov		dl, BYTE [rdi + rcx]
				cmp		dl, 0
				je		_pre_atoi
				inc		rcx
				cmp		dl, 43
				je		skip_sign
				cmp		dl, 45
				je		_set_sign
				dec		rcx
				jmp		_pre_atoi
_pre_atoi:
				mov		r11, 0
				jmp		atoi
_get_base_idx:
				mov		r9b, BYTE [rsi + rcx]
				cmp		r9b, 0
				je		_ret
				mov		rax, rcx
				cmp		dl, r9b
				je		_ret
				mov		rax, -1
				inc		rcx
				jmp		_get_base_idx
_mul_base:
				imul	r11, r8
				add		r11, rdx
				inc		rcx
				jmp		atoi
atoi:
				mov		dl, BYTE [rdi + rcx]
				cmp		dl, 0
				je		end
				mov		rax, -1
				mov		qword [rsp + 8], rcx
				mov		rcx, 0
				call	_get_base_idx
				mov		rcx, qword [rsp + 8]
				cmp		rax, -1
				je		end
				mov		rdx, rax
				jmp		_mul_base
end:
				add		rsp, 16
				mov		rax, r11
				imul	rax, r10
				ret
handle_error:
				mov		rdi, qword [rsp]
				add		rsp, 16
				mov		rax, 0
				ret
_ret:
				ret
_ret_true:
	 			mov		rax, 1
				ret
