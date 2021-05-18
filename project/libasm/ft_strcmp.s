section		.text
global		_ft_strcmp

_ft_strcmp:
			xor rcx, rcx
			jmp	comp
	  comp:
			mov	dl, BYTE [rdi + rcx]
			mov al, BYTE [rsi + rcx]
	  		cmp	dl, 0
			je	short_one
			cmp	al, 0
			je	short_two
			cmp dl, al
			jne end
  increment:
			inc	rcx
			jmp comp
  short_one:
			mov dl, al
	  		mov rax, 0
	  		cmp dl, 0
			je exit
			mov rax, -1
			jmp exit
  short_two:
			mov rax, 1
			jmp exit
		end:
			sub dl, al
			movsx rax, dl
	   exit:
			ret
