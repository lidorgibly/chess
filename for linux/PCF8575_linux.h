#ifndef _PCF8575_H
#define _PCF8575_H

//#include <stdbool.h>

#define I2C_DEVICE0_ADDRESS 0x20

#define I2C_DEVICE1_ADDRESS

#define I2C_DEVICE2_ADDRESS

#define I2C_DEVICE3_ADDRESS

typedef enum {SET, RESET} _bit;

typedef enum {PORT0, PORT1} _port;
typedef enum {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7} _pin;
typedef char _port_data;

typedef struct IOsDevice{
	int address;
	
	char IOsMirrorPort0;
	char IOsMirrorPort1;
	
	
} _IOsDevice;



void read_IO(char *IO, _port PORT, _pin PIN, char deviceAddress);	//input mode
void write_all_IOs(_port_data port0Data, _port_data port1Data, _IOsDevice device);	//output mode
void write_IO(_port port, _pin pin, _bit value, char deviceAddress);	//output mode


#endif