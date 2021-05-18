section		.text
global		_ft_list_remove_if
extern		_free

%macro	REGISTER_SAVE 0
		mov		qword [rsp], rdi
		mov		qword [rsp + 8h], rsi
		mov		qword [rsp + 10h], rdx
		mov		qword [rsp + 18h], rcx
		mov		qword [rsp + 20h], r8
		mov		qword [rsp + 28h], r9
		mov		qword [rsp + 30h], r10
		mov		qword [rsp + 38h], r11
%endmacro

%macro	REGISTER_LOAD 0
		mov		rdi, qword [rsp]
		mov		rsi, qword [rsp + 8h]
		mov		rdx, qword [rsp + 10h]
		mov		rcx, qword [rsp + 18h]
		mov		r8, qword [rsp + 20h]
		mov		r9, qword [rsp + 28h]
		mov		r10, qword [rsp + 30h]
		mov		r11, qword [rsp + 38h]
%endmacro


_ft_list_remove_if:
						sub		rsp, 64
						mov		r8, rdi
						mov		r9, rsi
						mov		r10, rdx
						mov		r11, rcx
						cmp		r8, 0
						je		end
						mov		rdx, [r8]
						cmp		rdx, 0
						je		end
						cmp		r9, 0
						je		end
						cmp		r10, 0
						je		end
						cmp		r11, 0
						je		end
						xor		rcx, rcx
						jmp		compare
set_begin:
						mov		[r8], rsi
						mov		r8, rsi
						mov		rcx, 1
						jmp		check_end
handle_diff:
						cmp		rcx, 0
						je		set_begin
						mov		r8, rsi
						jmp		check_end
compare:
						mov		rdi, r9
						mov		rsi, QWORD [rdx]
						REGISTER_SAVE
						call	r10
						REGISTER_LOAD
						mov		rdi, rsi
						mov		rsi, rdx
						mov		rdx, [rdx + 8]
						cmp		rax, 0
						jne		handle_diff
						jmp		check_connect
check_connect:
						cmp		rcx, 0
						jne		connect
						jmp		remove
connect:
						mov		[r8 + 8], rdx
						jmp		remove
remove:
						REGISTER_SAVE
						call	r11
						REGISTER_LOAD
						REGISTER_SAVE
						mov		rdi, rsi
						call	_free
						REGISTER_LOAD
						jmp		check_end
check_end:
						cmp		rdx, 0
						je		check_null
						jmp		compare
set_null:
						mov		QWORD [r8], 0
						jmp		end
check_null:
						cmp		rcx, 0
						je		set_null
						jmp		end
end:
						add		rsp, 64
						ret
_ret:
						ret
