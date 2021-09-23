#include <stdbool.h>
#include "PCF8575_linux.h"
#include "i2c_linux.h"











//P00-P07 // P10-P17
//IO 0 to 15


//PORT 0 or 1
//PIN 0 to 7
void read_IO(char *IO, _port PORT, _pin PIN, _IOsDevice device){		//input mode
	
		
	
	
	
	char data[2];
	
	set_i2c_slave_address((int)device.address);
	
	i2c_read(data, 2);
	
	
	
	
	
	
	
	device.IOsMirrorPort0 = data[0];
	device.IOsMirrorPort1 = data[1];
	
}


//port0 - pins 7 to 0
//port1 - pins 7 to 0

void write_all_IOs(_port_data port0Data, _port_data port1Data, _IOsDevice device){	//output mode
	
	char data[2];
	data[0] = port0Data;
	data[1] = port1Data;
	
	set_i2c_slave_address((int)device.address);

	//write 2 bytes I2C_ADDRESS_WRITE
	i2c_write(data, 2);
	
	device.IOsMirrorPort0 = port0Data;
	device.IOsMirrorPort1 = port1Data;

	
}



//value 0 or 1
void write_IO(_port port, _pin pin, _bit value, _IOsDevice device){	//output mode
	
	char data[2];
	data[0] = device.IOsMirrorPort0;
	data[1] = device.IOsMirrorPort1;
	
	
	if (port == Port0){
		set_bit(value, (char)pin, &data[0])
		device.IOsMirrorPort0 = data[0];
	}
	
	if (port == Port1){
		set_bit(value, (char)pin, &data[1])
		device.IOsMirrorPort1 = data[1];
	}
	
	
	write_all_IOs(data[0], data[1], device);

	
	
	
	
}






// index 7-0
//value 0 or 1
void set_bit(char value, char index, char* byte){
	
	*byte = ((~(1 << index)) & *byte) | (value << index);
	
}








