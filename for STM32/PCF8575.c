#include <stdbool.h>
#include "PCF8575.h"












//P00-P07 // P10-P17
//IO 0 to 15


//PORT 0 or 1
//PIN 0 to 7
void read_IO(char *IO, _port PORT, _pin PIN, _IOsDevice device){		//input mode
	
		
	
	
	
	char data[2];
	
	
	
	//TODO: 
	
	
	
	
	
	
	
	
	device.IOsMirrorPort0 = data[0];
	device.IOsMirrorPort1 = data[1];
	
}


//port0 - pins 7 to 0
//port1 - pins 7 to 0

void write_all_IOs(char port0Data, char port1Data, _IOsDevice device){	//output mode
	
	char data[2];
	data[0] = port0Data;
	data[1] = port1Data;
	
	//write 2 bytes I2C_ADDRESS_WRITE
	
	
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
	
	
	write_IOs(data[0], data[1], device);

	
	
	
	
}






// index 7-0
//value 0 or 1
void set_bit(char value, char index, char* byte){
	
	*byte = ((~(1 << index)) & *byte) | (value << index);
	
}








