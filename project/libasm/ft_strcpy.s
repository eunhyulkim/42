section		.text
global		_ft_strcpy

_ft_strcpy:
			xor rax, rax
	  loop:
			mov dl, BYTE [rsi+rax]
			mov BYTE [rdi+rax], dl
	  		cmp	BYTE [rsi+rax], 0
			je	end
			inc rax
			jmp loop
		end:
			mov rax, rdi
			ret
