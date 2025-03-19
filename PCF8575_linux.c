#include <stdbool.h>
#include "PCF8575_linux.h"
#include "i2c_linux.h"
#include <stdio.h>
#include <unistd.h>









//P00-P07 // P10-P17
//IO 0 to 15


//PORT 0 or 1
//PIN 0 to 7
_bit read_IO(_port port, _pin pin, _IOsDevice* device){		//input mode
	
	char data[2];
	
	set_i2c_slave_address(device->address);
	
	i2c_read(data, 2);
	
	if (port == PORT0){
		return read_bit((char)pin, &data[0]);
		//printf("read %d from port %d\n", data[0], port);
	}
	
	if (port == PORT1){
		return read_bit((char)pin, &data[1]);
		//printf("read %d from port %d\n", data[1], port);
	}	
	
	

	
	
}

void read_all_IOs(char* IOsPort0, char* IOsPort1, _IOsDevice* device){		//input mode
	
		
	
	char data[2];
	
	set_i2c_slave_address(device->address);
	
	i2c_read(data, 2);
	
	printf("read all IOs %d %d\n", data[0], data[1]);

	
	
	*IOsPort0 = data[0];
	*IOsPort1 = data[1];
	
	
	
}


//port0 - pins 7 to 0
//port1 - pins 7 to 0

void write_all_IOs(_port_data port0Data, _port_data port1Data, _IOsDevice* device){	//output mode
	
	char data[2];
	data[0] = port0Data;
	data[1] = port1Data;

	//printf("%d", device.address);
	set_i2c_slave_address(device->address);
	//write 2 bytes I2C_ADDRESS_WRITE
	if (i2c_write(data, 2) == false) {
		printf("I2C error address: %d\n", device->address);

	}

	
	usleep(100000);

}



//value 0 or 1
void write_IO(_port port, _pin pin, _bit value, _IOsDevice* device){	//output mode
	
	char data[2];
	read_all_IOs(&data[0], &data[1], device);
	if (port == PORT0){
		set_bit(value, (char)pin, &data[0]);
		printf("write %d to port %d\n", data[0], port);
	}
	
	if (port == PORT1){
		set_bit(value, (char)pin, &data[1]);
		printf("write %d to port %d\n", data[1], port);
	}
	
	write_all_IOs(data[0], data[1], device);

	
	
	
	
}






// index 7-0
//value 0 or 1
void set_bit(char value, char index, char* byte){
	
	*byte = ((~(1 << index)) & *byte) | (value << index);
	
}

_bit read_bit(char index, char* byte){
	
	return (_bit)((*byte >> index) & 0x1);

	
}






