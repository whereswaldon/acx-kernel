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
	x_delay(1000);	
	return 0;
}
