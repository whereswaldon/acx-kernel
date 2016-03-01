/*
 * serial.c
 *
 * Created: 2/29/2016 7:07:12 PM
 *  Author: Chris
 */ 
#include "serial.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

/************************************************************************/
/* Serial Communication Functions                                       */
/************************************************************************/

/*
 * Set the serial port to listen at a given speed with a given configuration
 * (use the ones defined in serial.h).
 */
void serial_open(long speed, int config) {
	//disable interrupts during config
	cli();
	//set the baud rate
	UBRR0 = speed;
	
	
	//enable interrupts after config
	sei();
}

/*
 * Waits for an available character in the serial receive buffer, then
 * reads and returns the character.
 */
char serial_read(void) {
	if (/*mode is 9 bit*/1) {
		unsigned char status, resh, resl;
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) )
		;
		/* Get status and 9th bit, then data */
		/* from buffer */
		status = UCSR0A;
		resh = UCSR0B;
		resl = UDR0;
		
		/* If error, return -1 */
		if ( status & (1<<FE0)|(1<<DOR0)|(1<<UPE0) ) {
			return -1;
		}
		
		/* Filter the 9th bit, then return */
		resh = (resh >> 1) & 0x01;
		return ((resh << 8) | resl);
	} else {
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) )
		;
		/* Get and return received data from buffer */
		return UDR0;
	}
	
}

/*
 * Waits for the write buffer to be available, then writes a byte value
 * to the buffer.
 */
void serial_write(char data) {
	if (/*mode is 9-bit*/1) {
		while( !(UCSR0A & (1<<UDRE0)) ) {
			;//wait for buffer to be empty
		}
		/* Copy 9th bit to TXB8 */
		UCSR0B &= ~(1<<TXB);
		if ( data & 0x0100 )
		UCSR0B |= (1<<TXB);
		/* Put data into buffer, sends the data */
		UDR0 = data;
	} else {
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE0)) )
		;
		/* Put data into buffer, sends the data */
		UDR0 = data;
	}
}