/*
 * ACX-kernel.c
 *
 * Created: 1/28/2016 2:56:40 PM
 * Author : waldonck
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "acx.h"


void forever() {
	DDRB=0x80;
	while(1) {
		PORTB ^= 0x80;
		x_delay(100);
	}
}

int main(void)
{
	x_init();
	x_new(1, forever, 1);
	x_disable(0);
	x_enable(0);
	x_suspend(0);
	x_resume(0);
	byte thread_id = x_getID();
	x_disable(thread_id);
	x_delay(1000);
	
	return 0;
}
