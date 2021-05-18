section		.text
global		_ft_list_size

_ft_list_size:
				xor		rax, rax
				jmp		cnt
cnt:
				cmp		rdi, 0
				je		end
				mov		rdi, [rdi + 8]
				inc		rax
				jmp		cnt
end:
				ret
