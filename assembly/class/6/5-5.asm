assume cs:code
a segment 
	db 1,2,3,4,5,6,7,8

a ends

b segment
	db 1,2,3,4,5,6,7,8
b ends

c segment 
	db 0,0,0,0,0,0,0,0
c ends

code segment
start:	mov ax, c
		mov ds, ax

		mov ax, a
		mov es, ax

		mov dl, 0
		mov bx, 0
		mov cx, 8
	s:  mov dl,  es:[bx]	
		mov ds:[bx], dl
		inc bx
		loop s

		mov ax, b
		mov es, ax

		mov dl, 0
		mov bx, 0
		mov cx, 8
	s0: mov dl, es:[bx]
		add ds:[bx], dl
		inc bx
		loop s0

		mov ah, 4ch
		int 21h

code ends
end start

