/**
 * acx.c
 * System configuration for a basic cooperative executive
 * Kernel.
 * @author Christopher Waldon
 */

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


/***********************************************|
 * Define functions ****************************|
 */

/*
 * Initializes kernel data structures, sets stack pointer
 * to Thread0 stack area returns to caller. The calling
 * function becomes Thread0.
 */
void x_init() {

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

