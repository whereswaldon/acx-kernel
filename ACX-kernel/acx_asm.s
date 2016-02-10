
/*
 * acx_asm.s
 *
 * Created: 
 * Author: efb
 */ 
 #define __SFR_OFFSET 0
 #include <avr/io.h>
 #include "acx.h"


		.section .text
		.global x_yield
x_yield:
//------------------------------------------------------------------
// Save "callee-save" registers
//------------------------------------------------------------------
		push	r28
		push	r29
		push	r2
		push	r3
		push	r4
		push	r5
		push	r6
		push	r7
		push	r8
		push	r9
		push	r10
		push	r11
		push	r12
		push	r13
		push	r14
		push	r15
		push	r16
		push	r17


//------------------------------------------------------------------
//   Get thread ID and mask
//------------------------------------------------------------------

		lds	r20,	x_thread_id
		lds	r21,	x_thread_mask

//------------------------------------------------------------------
// Store SP into current thread's stack-save area
//------------------------------------------------------------------
		;compute index into stacks array
		mov	r22,	r20	;make a copy of the thread id
		lsl	r22	  	;left shift two to multiply by 2
		lsl	r22	  	;left shift two to multiply by 2
		ldi	r30,	lo8(stacks)	;load the address of the array
		ldi r31,	hi8(stacks)	;load the other byte
		add	r30,	r22	;increment the address by index
		adc r31,	0	;pull in the carry from previous, if any
		
		;write the SP into the stack save area
		lds	r16,	(0x5d);Load SP low byte
		st	Z,	r16	;save SP low byte
		lds r16,		(0x5e);Load SP high byte
		std	Z+1	,r16	;save SP high byte


;------------------------------------------------------------------------
; Schedule next thread -- must use caller-save registers below here
;                         because we can reach this without saving regs
;                         if entered from x_new() function
;-------------------------------------------------------------------------
		.global	x_schedule
x_schedule:
	// determine READY status of each thread




;------------------------------------------------
;   Loop through all threads to test for READY
;------------------------------------------------




;----------------------------------------------------------
;  SLEEP HERE:  Here's where we sleep (no threads are READY)
;  but for now we'll jump back to schedule loop again
;----------------------------------------------------------
		; add sleep instructions here...
		;TODO: uncomment & implement
		;rjmp	x_schedule			

;---------------------------------------------------
; Restore context of next READY thread
;---------------------------------------------------
restore:
		//	restore SP from thread's sp
		
		
		
				
		// update hardware SP




		// Restore registers
		pop	r17
		pop	r16
		pop	r15
		pop	r14
		pop	r13
		pop	r12
		pop	r11
		pop	r10
		pop	r9
		pop	r8
		pop	r7
		pop	r6
		pop	r5
		pop	r4
		pop	r3
		pop	r2
		pop	r29
		pop	r28

		// Return to next thread
		ret
