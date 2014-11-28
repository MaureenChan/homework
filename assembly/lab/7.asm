assume cs:codes, ds:data, es:table
data segment
	db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
	db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
	db '1993', '1994', '1995'

	dd 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514
	dd 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000, 5937000

	dw 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793, 4037, 5635, 8226
	dw 11542, 14430, 15257, 17800

data ends

table segment
	db 21 dup ('year summ ne ?? ')
table ends

codes segment

start:
	mov ax, data
	mov ds, ax
	mov ax, table
	mov es, ax

	mov bp, 0
	mov si, 0
	mov bx, 0
	mov cx, 21

;写入年份
s:  mov ax, ds:[si]
	mov es:[bx], ax

	mov ax, ds:[si + 2]
	mov es:[bx + 2], ax
	add si, 4
	add bx, 16
	loop s

	mov bx, 0
	mov cx, 21
;写入收入
s0: mov ax, ds:[si]
	mov es:[bx + 5], ax
	
	mov ax, ds:[si + 2]
	mov es:[bx + 7], ax
	add si, 4
	add bx, 16
	loop s0

	mov bx, 0
	mov cx, 21
;写入雇员数
s1: mov ax, ds:[si]
	mov es:[bx + 10], ax

	add si, 2
	add bx, 16
	
	loop s1

	mov bx, 0
	mov cx, 21
	
;写入人均收入
s2: mov ax, es:[bx + 5]
	mov dx, es:[bx + 7]
	div word ptr es:[bx + 10] 
	mov es:[bx + 13], ax
	add bx, 16
	loop s2
	nop
	nop
	mov ax, 4c00h
	int 21h



codes ends
end start

