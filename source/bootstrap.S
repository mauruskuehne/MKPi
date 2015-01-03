.global init
.extern kmain
.globl _start
_start:
init:	
;@ Move the stack pointer.
	mov sp, #0x80000

/*
;@light up ACT
ldr r0,=0x20200000
mov r1,#1
lsl r1,#18
str r1,[r0,#4]
mov r1,#1
lsl r1,#16
str r1,[r0,#40]
*/

;@ Invoke our main C++ entrypoint.
	bl main

;@ Loop forever
	b hang$

hang$:
	b hang$
