#ifndef _PCF8575_H
#define _PCF8575_H

//#include <stdbool.h>

#define I2C_DEVICE0_ADDRESS 0x20
#define I2C_DEVICE1_ADDRESS 0x21
#define I2C_DEVICE2_ADDRESS 0x22
#define I2C_DEVICE3_ADDRESS 0x23
#define I2C_DEVICE4_ADDRESS 0x24
#define I2C_DEVICE5_ADDRESS 0x25
#define I2C_DEVICE6_ADDRESS 0x26
#define I2C_DEVICE7_ADDRESS 0x27

typedef enum {ZERO, ONE} _bit;

typedef enum {PORT0, PORT1} _port;
typedef enum {PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7} _pin;
typedef char _port_data;
typedef struct IOsDevice{
	int address;	
} _IOsDevice;


typedef struct IO_position{
	_IOsDevice device;
	_port port;
	_pin pin;	
} _IO_position;

_bit read_bit(char index, char* byte);
void set_bit(char value, char index, char* byte);
_bit read_IO(_IO_position io);	//input mode
void write_all_IOs(_port_data port0Data, _port_data port1Data, _IOsDevice* device);	//output mode
void write_IO(_port port, _pin pin, _bit value, _IOsDevice* device);	//output mode
void read_all_IOs(char*, char*, _IOsDevice*);

#endif
