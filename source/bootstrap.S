.global init
.extern kmain

init:	
;@ Move the stack pointer.
	mov sp, #0x80000

;@ Invoke our main C++ entrypoint.
	bl main

;@ Loop forever
	b hang$

hang$:
	b hang$
