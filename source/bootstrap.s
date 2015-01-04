.global init
.extern main


;@ This is the actual entr point to the application.
;@ I need to look into how to do this another way, but it seems like
;@ this is the most reliable method for copying the interrupt handlers
;@ into the IVT.
interrupt:

	;@ Basically each line represents the value to a branch command.
	;@ Since this is the first thing, we know that our _relative_
	;@ interrupt vector table will always be at the start of our
	;@ kernel ( location: 0x8000 ).

	;@ Reset Interrupt
	ldr pc, reset_handler
	
	;@ Undefined Instruction
	ldr pc, basic_handler
	
	;@ Software Interrupt
	ldr pc, basic_handler
	
	;@ Prefetch Abort
	ldr pc, basic_handler
	
	;@ Data Abort
	ldr pc, basic_handler
	
	;@ ?? Looks like the ARM ARM specifys that
	;@ there is just a casual hole here, so I guess we
	;@ are filling it with another handler. Though I don't
	;@ really know what calls this.
	ldr pc, basic_handler
	
	;@ IRQ
	ldr pc, basic_handler
	
	;@ FIQ
	ldr pc, basic_handler



;@ Next up is a trick to basically force the compiler
;@ to store the branch command as a value
;@ into the respective register.
reset_handler:
	.word reset

basic_handler:
	.word arm_interrupt_handler

;@ Then this is our "reset" function
;@ which is what will actually get automatically
;@ called since the program is going to flow down
;@ into this method.
reset:

	;@ So now we setup everything to copy the values over.
	mov r0, #0x8000
	mov r1, #0x0000

	;@ And then we do the actual data copy.
	ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
	stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
	ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
	stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
	
	;@ And then call the bootstrapper init function.
	;@ NOTE: I delegated these two assembly files because I don't
	;@ want to marry my kernel to the ivt setup code.
	b init
	bx lr


.globl _start
_start:
init:	
;@ Move the stack pointer.
	mov sp, #0x80000

;@ Invoke our main C++ entrypoint.
	bl main

;@ Loop forever
	b hang$

hang$:
	b hang$

.global PUT32
PUT32:
    str r1,[r0]
    bx lr

.global GET32
GET32:
    ldr r0,[r0]
    bx lr

.global dummy
dummy:
    bx lr

hang:
	b hang
	
.extern irq_handler
;@ And here is the actual interrupt handler code.
arm_interrupt_handler:
  push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
  ;@ the SWI / SVC instruction contains a user defined number, we'll extract it and pass it as param to the c handler
  LDR R0, [lr,#-4]
  BIC R0, R0, #0xFF000000
  bl irq_handler
  pop  {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
  movs pc,r14

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   This code is probably needed for HW Interrupts!
	;@ Store the return link.
	sub r14, r14, #4
	stmfd sp!, {r0,r1,r2,r3,r4,r14}
	
	;@ Invoke our C++ irq handler.
	bl irq_handler
	
	;@ Restore to the original caller.
	ldmfd sp!, {r0,r1,r2,r3,r4,pc}^
	bx lr*/
