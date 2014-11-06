assume cs:codesg

codesg segment

	start:	
			mov dl, 10h
			mov cx, 15

		s0:	mov si, cx	
			mov cx, 16
		
		s:	
			mov ah, 02h
			mov dl, dl
			int 21h	

			push dx

			mov ah, 02h
			mov dl, 0
			int 21h

			pop dx
			inc dl
			loop s

			push dx
			mov ah, 02h
			mov dl, 0dh
			int 21h

			mov ah, 02h
			mov dl, 0ah
			int 21h

			pop dx
			mov cx, si
			loop s0

			mov ax, 4c00h
			int 21h
codesg ends

end
