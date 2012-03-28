.model tiny
.data
x  DW  0
y  DW  0
z  DW  0
.code
.startup
call readin 
MOV [x] , AX
MOV AX ,x
PUSH AX
MOV AX ,5
POP BX
ADD AX,BX
MOV [x], AX
MOV AX ,0
MOV [y], AX
label0:
MOV AX , x
MOV BX , y
CMP AX,BX
JLE label1
MOV AX , x
MOV BX , y
CMP AX,BX
JLE label2
MOV AX , x
MOV BX , y
CMP AX,BX
JLE label3
MOV AX , [x]
call printout 
label3:
label2:
MOV AX ,x
PUSH AX
MOV AX ,1
PUSH AX
POP BX
POP AX
SUB AX,BX
MOV [x], AX
JMP label0
label1:
call readin 
MOV [z] , AX
.exit

readin proc near
	push bx
	push cx
	push dx
	mov cx,10
	mov bx,0

read:
	mov ah,1
	int 21h
	cmp al,'0'
	jl endread
	cmp al,'9'
	jg endread
	sub al,'0'
	mov ah,0
	push ax
	mov ax,bx
	mul cx
	pop dx
	add ax,dx
	mov bx,ax
	jmp read

endread:
	push ax
	mov dl,10
	mov ah,6
	int 21h
	mov dl,13
	mov ah,6
	int 21h
	pop ax
	mov ax,bx
	pop dx
	pop cx
	pop bx
	ret
readin endp

printout proc near
	push bx
	push cx
	push dx
	mov bx,10
	mov cx,0
	cmp ax,0
	jl makepos

print1:	
	mov dx,0
	div bx
	push dx
	inc cx
	cmp ax,0
	jnz print1

print2:
	pop dx
	add dl,'0'
	mov ah,6
	int 21h
	loop print2
	push ax
	mov dl,10
	mov ah,6
	int 21h
	mov dl,13
	mov ah,6
	int 21h
	pop ax
	pop dx
	pop cx
	pop bx
	ret

makepos:
	push ax
	mov dl,'-'
	mov ah,6
	int 21h
	pop ax
	not ax
	add ax,1
	jmp print1
printout endp	

end
