assume cs:codesg, ss:stacksg, ds:datasg

stacksg segment 
	dw 0,0,0,0,0,0,0,0
stacksg ends

datasg segment
	db '1. display      '
	db '2. brows        '
	db '3. replace      '
	db '4. modify       '
datasg ends

codesg segment
	start:	mov ax, stacksg
			mov ss, ax
			mov sp, 16
			mov ax, datasg
			mov ds, ax
			mov bx, 0

			mov cx, 4	;外循环
		s0:	push cx
			mov si, 3	;从第三个单元开始
			mov cx, 4	;内循环，控制4个字母

		s:	mov al, [bx + si]
			and al, 11011111b	;转换为大写字母
			mov [bx + si], al
			inc si
			loop s

			add bx, 16	;换行
			pop cx
			loop s0

			mov bx, 0
			mov cx, 4
		s1:	push cx
			mov si, 0
			mov cx, 16
			
		s2:	mov dl, [bx + si]
			mov ah, 02h
			int 21h
			inc si
			loop s2
			
			;输出换行
			mov ah, 02h
			mov dl, 0dh
			int 21h

			mov ah, 02h
			mov dl, 0ah
			int 21h
			
			add bx, 16
			pop cx
			loop s1
		

			nop
			nop
		
			mov ax, 4c00h
			int 21h

codesg ends
end start
			

