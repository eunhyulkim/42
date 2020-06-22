section		.text
global		_ft_list_sort

_ft_list_sort:
				sub		rsp, 32
				mov		r8, rdi
				cmp		rdi, 0
				je		end
				mov		rdi, [rdi]
				cmp		rdi, 0
				je		end
				mov		rdx, [rdi + 8]
				cmp		rdx, 0
				je		end
				mov		r9, rsi
				mov		rsi, rdx
				jmp		iterable
swap:
				mov		EDX, DWORD [rdi]
				mov		ECX, DWORD [rsi]
				mov		DWORD [rdi], ECX
				mov		DWORD [rsi], EDX
				jmp		comp_loop
comp_loop:
				mov		[rsp + 24], rdi
				mov		[rsp + 32], rsi
				mov		rdi, QWORD [rdi]
				mov		rsi, QWORD [rsi]
				call	r9
				mov		rdi, [rsp + 24]
				mov		rsi, [rsp + 32]
				jg		swap
				mov		rsi, [rsi + 8]
				cmp		rsi, 0
				je		_ret
				jmp		comp_loop
iterable:
				mov		[rsp], rdi
				mov		[rsp + 8], rsi
				call	comp_loop
				mov		rdi, [rsp]
				mov		rsi, [rsp + 8]
				mov		rdi, rsi
				mov		rsi, [rdi + 8]
				cmp		rsi, 0
				je		end
				jmp		iterable
end:
				add		rsp, 32
				mov		rax, r8
				ret
_ret:
				ret
