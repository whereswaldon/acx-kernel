/**
 * acx.c
 * System configuration for a basic cooperative executive
 * Kernel.
 * @author Christopher Waldon
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "acx.h"

/***********************************************|
 * Define data structures **********************|
 */

/**
 * stacks holds the base pointers and head pointers
 * of each stack for each thread.
 */
Stack stacks[NUM_THREADS];

StackDelay stackDelays[NUM_THREADS];

/**
 * These three bytes encode the current delay, disable,
 * and suspend statuses for each thread. Bit 0 in each
 * byte refers to thread 0; so forth and so on...
 */
byte delays;
byte disables;
byte suspends;

/**
 * ticks counts the total number of system ticks since
 * the system came online.
 */
uint32_t ticks;

/*
 * Defines the id of the currently executing thread.
 */
byte x_thread_id;

/*
 * TODO: document this
 */
byte x_thread_mask;


/***********************************************|
 * Define functions ****************************|
 */

/*
 * Initializes kernel data structures, sets stack pointer
 * to Thread0 stack area returns to caller. The calling
 * function becomes Thread0.
 */
void x_init() {
	//initialize stacks
	stacks[0].pHead = (byte *)TH0_START;
	stacks[0].pBase = (byte *)TH0_START;
	stacks[1].pHead = (byte *)TH1_START;
	stacks[1].pBase = (byte *)TH1_START;
	stacks[2].pHead = (byte *)TH2_START;
	stacks[2].pBase = (byte *)TH2_START;
	stacks[3].pHead = (byte *)TH3_START;
	stacks[3].pBase = (byte *)TH3_START;
	stacks[4].pHead = (byte *)TH4_START;
	stacks[4].pBase = (byte *)TH4_START;
	stacks[5].pHead = (byte *)TH5_START;
	stacks[5].pBase = (byte *)TH5_START;
	stacks[6].pHead = (byte *)TH6_START;
	stacks[6].pBase = (byte *)TH6_START;
	stacks[7].pHead = (byte *)TH7_START;
	stacks[7].pBase = (byte *)TH7_START;

	//initialize canaries
	byte * curr_canary = (byte *)TH0_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH1_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH2_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH3_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH4_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH5_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH6_CANARY;
	*curr_canary = CANARY_VALUE;
	curr_canary = (byte *)TH7_CANARY;
	*curr_canary = CANARY_VALUE;

	//initialize counter
	ticks = 0;

	//Initialize Delays
	stackDelays[0] = 0;
	stackDelays[1] = 0;
	stackDelays[2] = 0;
	stackDelays[3] = 0;
	stackDelays[4] = 0;
	stackDelays[5] = 0;
	stackDelays[6] = 0;
	stackDelays[7] = 0;

	//Disable all but thread 0
	disables = 0xFE;

	//Set initial statuses
	delays = 0;
	suspends = 0;

	//Configure this to return as thread 0
	x_thread_id = 0;
	x_thread_mask = 0x01;

	//Change the stack location to Thread 0's space
	int i = 0;
	byte * newStack = TH0_START;
	//iterate across the old stack and copy all values
	for (; STACK_START-i >= SP; i++) {
		*(newStack-i) = *((byte *)STACK_START-i);
	}
	
	//disable interrupts
	cli();
	//Set new stack pointer. +1 compensates for final
	//increment of i.
	SP = (int)TH0_START-i+1;
	//set global interrupt enable
	sei();
	return;
}

/*
 * Assigns a function pointer (pthread) to a thread ID
 * and sets its initial enable status. If the thread ID
 * is the same as the calling thread, then the calling
 * thread is replaced and rescheduling takes place.
 *
 * Note: This function MAY NOT be called from an
 * interrupt handler.
 */
void x_new(byte tid, PTHREAD pthread, byte isEnabled) {

}

/*
 * Invokes kernel scheduler to give other threads a
 * chance to run. Does not change state of current
 * thread. If no other threads are READY, then
 * current thread (the calling thread) is restored
 * to execution.
 *
 * Note: This function MAY NOT be called from an
 * interrupt handler.
 */
void X_yield() {

}

/*
 * Delays the calling task by the specified number
 * of system “ticks”. Actually delay depends on
 * tick frequency, set at system initialization.
 *
 * Note: This function MAY NOT be called from an
 * interrupt handler.
 */
void x_delay(int ticks) {

}

/*
 *
 * Suspends the specified thread by setting its
 * suspend status bit.
 *
 * Note 1: This function MAY be called from an interrupt handler.
 *
 * Note 2: A future version of this function might be
 * implemented with a counting semaphore to allow
 * multiple levels of suspend. 
 */
void x_suspend(int tid) {

}

/*
 * Resumes specified thread by clearing its suspend status bit. 
 *
 * Note 1: This function MAY be called from an interrupt handler.
 *
 * Note 2: A future version of this function might be implemented 
 * with a counting semaphore to allow multiple levels of suspend. 
 */
void x_resume(int tid) {

}

/*
 *
 * Disables specified thread by setting its disable status bit.
 * This makes the puts the thread into a BLOCKED state.
 * For now this bit behaves just like the suspend status,
 * only providing another level of “suspend”. 
 * 
 * Note 1: This function MAY be called from an interrupt handler.
 *
 * Note 2: A future This function could be implemented with other 
 * capabilities. For example:
 * This function could reset the thread to its starting state
 * so that if enabled it will restart as if it had just been
 * created. (This could be implemented by invoking x_new with
 * the thread disabled. Thread starting address must be saved
 * on the stack when first created.
 */
void x_disable(int tid) {

}

/*
 * Enables specified thread by clearing its disable status bit.
 *
 * Note 1: This function MAY be called from an interrupt handler.
 *
 * Note 2: A future version of this function might clear ALL
 * status bits that block the thread. 
 */
void x_enable(int tid) {

}

/*
 * Returns the 32-bit time as recorded on the absolute tick
 * counter.
 */
long gtime() {

}

