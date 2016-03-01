/*
 * serial.h
 *
 * Created: 2/29/2016 7:06:58 PM
 *  Author: Chris
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

/*
 * Define the same constants for serial configuration
 * that Arduino uses.
 */
#define SERIAL_5N1 0
#define SERIAL_6N1
#define SERIAL_7N1
#define SERIAL_8N1
#define SERIAL_5N2
#define SERIAL_6N2
#define SERIAL_7N2
#define SERIAL_8N2
#define SERIAL_5E1
#define SERIAL_6E1
#define SERIAL_7E1
#define SERIAL_8E1
#define SERIAL_5E2
#define SERIAL_6E2
#define SERIAL_7E2
#define SERIAL_8E2
#define SERIAL_5O1
#define SERIAL_6O1
#define SERIAL_7O1
#define SERIAL_8O1
#define SERIAL_5O2
#define SERIAL_6O2
#define SERIAL_7O2
#define SERIAL_8O2

void serial_open(long speed, int config);
char serial_read(void);
void serial_write(char data);
#endif /* SERIAL_H_ */