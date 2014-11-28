assume cs:codesg

codesg segment

	start:	
			mov dl, 10h

			;控制外循环
			mov cx, 15
		s0:	mov si, cx		;si保存外循环

			;控制内循环
			mov cx, 16
		s:	;输出字符	
			mov ah, 02h
			mov dl, dl
			int 21h	

			push dx

			;输出空格
			mov ah, 02h
			mov dl, 0
			int 21h

			pop dx
			inc dl
			loop s

			push dx
			;输出换行
			mov ah, 02h
			mov dl, 0dh
			int 21h

			mov ah, 02h
			mov dl, 0ah
			int 21h

			pop dx
			mov cx, si
			loop s0

			nop
			nop

			mov ax, 4c00h
			int 21h
codesg ends

end
