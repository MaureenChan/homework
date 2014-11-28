assume cs:codesg, ss:stack
data segment
	;0-83h
	db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
	db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
	db '1993', '1994', '1995'
	;84-0a7h
	dd 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514
	dd 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000, 5937000
	;0a8h
	dw 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793, 4037, 5635, 8226
	dw 11542, 14430, 15257, 17800
data ends

table segment
	db 21 dup('year summ ne ?? ')
table ends

stack segment
	dw 32 dup(0)
stack ends

;存放字符串
buffer segment
	db 32 dup(0)
buffer ends

codesg segment
start:
	mov ax, data
	mov ds, ax
	mov di, 0
	mov si, 4 * 21 + 4 * 21	;控制人数

	mov ax, table
	mov es, ax		;es为table段中数据
	mov bx, 0
	call finishing	;把data中的数据存入表中

	mov ax, stack
	mov ss, ax		;ss为栈中数据
	mov sp, 64

	;把table表内容转换成字符串输出
	mov ax, buffer
	mov ds, ax		;ds为buffer数据
	mov si, 0
	mov ax, table
	mov es, ax
	mov bx, 0
	mov dh, 4

	mov cx, 21

s:
	push cx

	;把年份输出
	mov ax, es:[bx]
	mov ds:[si], ax
	mov ax, es:[bx + 2]
	mov ds:[si + 2], ax
	mov byte ptr ds:[si + 4], 0		;字符串末尾\0
	mov dl, 20		;dl为排版间隔
	mov cl, 2		;显示属性
	call show_str

	;把收入转换为字符串
	push dx
	mov ax, es:[bx + 5]
	mov dx, es:[bx + 7]
	call dtoc
	pop dx
	mov dl, 30
	call show_str

	;把雇员数转换为字符串
	push dx
	mov ax, es:[bx + 0ah]
	mov dx, 0
	call dtoc
	pop dx
	mov dl, 40
	call show_str

	;把平均收入转换为字符串
	push dx
	mov ax, es:[bx + 0dh]
	mov dx, 0
	call dtoc
	pop dx
	mov dl, 50
	call show_str

	add dh, 1			;控制输出的行
	add bx, 10h			;控制table的行

	pop cx
	loop s

	mov ax, 4c00h
	int 21h

show_str:
	;保存现场
	push ax
	push bx
	push cx
	push dx
	push es
	push bp
	push si

	mov ax, 0b800h		;显示存储区
	mov es, ax

	mov al, 80 * 2		;一行有160字节
	mul dh				;al为起始位置
	mov dh, 0
	add ax, dx
	add ax, dx
	mov bp, ax			;bp控制列
	mov al, cl			;al为显示属性
	mov cx, 0
	mov cl, ds:[si]		;cl为输出字符
	inc si

	;把数据拷贝到显示区
show_str_s:
	mov es:[bp], cl		;字符放到低地址
	inc bp
	mov es:[bp], al		;属性放到高地址
	inc bp
	mov cl,ds:[si]
	inc si
	inc cx
	loop show_str_s		;字符串结尾是cl为0,跳出循环

	pop si
	pop bp
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret

dtoc:
	push ax
	push bx
	push cx
	push dx
	push bp
	push si
	
	mov bp, 0
dtoc_s0:
	mov cx, 10d	;除数
	call divdw
	push cx		;余数进栈	
	inc bp		;记录位数
	mov cx, ax	;商为0时跳出循环
	inc cx
	loop dtoc_s0

	mov cx, bp	;出栈次数

dtoc_s:
	pop bx					
	add bl, 30h				;转为字符串
	mov ds:[si], bl			;保存到buffer中
	inc si
	loop dtoc_s

	mov byte ptr ds:[si], 0	;字符串结尾\0

	pop si
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	ret

	;不会溢出的除法
divdw:
	push bx

	push ax
	mov ax, dx	;高8位
	mov dx, 0
	div cx		;除数
	mov bx, ax	;bx = int(H/N)	dx = rem(H/N)
	pop ax		;低8位
	div cx		;(rem(H / N) * 10000H + L ) / N
	mov cx, dx	;余数
	mov dx, bx	;dx = int(H/N)

	pop bx
	ret

finishing:
	push ax
	push bx
	push cx
	push di
	push si
	push bp

	mov cx, 21

;把data段中信息以正确形式写入es段中
finishing_s:
	;拷贝年份,每个数据占用4个字节
	mov ax, ds:[di]			;di为ds段中横向变量,增量为4
	mov es:[bx], ax			;bx为es段中纵向变量,增量为16
	mov ax, ds:[di + 2]
	mov es:[bx + 2], ax

	;拷贝收入,每个数据占用4个字节
	mov ax, ds:[di + 4 * 21]
	mov dx, ds:[di + 4 * 21 + 2]
	mov es:[bx + 5], ax
	mov es:[bx + 5 + 2], dx

	;拷贝雇员
	mov bp, ds:[si]			;si为雇员的数据段,增量为2
	mov es:[bx + 0ah], bp

	;计算并拷贝到人均收入
	div bp					;bp为当前的雇员数
	mov es:[bx + 0dh], ax

	add bx, 16
	add di, 4
	add si, 2
	loop finishing_s

	pop bp
	pop si
	pop di
	pop cx
	pop bx
	pop ax
	ret

codesg ends
end start

