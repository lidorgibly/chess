#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "i2c_linux.h"
#include <string.h>
#include <errno.h>
	int i2cFile;
	int adapterNum = 1; 	
	char fileName[20];
	
	//addr = 0x20
	


	
	
void init_i2c(){
	snprintf(fileName, 19, "/dev/i2c-%d", adapterNum);
	i2cFile = open(fileName, O_RDWR);
	if (i2cFile < 0) {
	/* ERROR HANDLING; you can check errno to see what went wrong */
		printf("init_i2c: %s\n", strerror(errno));
		exit(1);
	}
	
}
	
	
	
int i2c_read(char* buf, int size){
	if (read(i2cFile, buf, size) != size){
		printf("i2c_read: %s\n", strerror(errno));
		return 0;

		/* ERROR HANDLING: i2c transaction failed */
	}else{
		return 1;

		//printf("%d %d", buf[0], buf[1]);

	}
	
	
}

int i2c_write(char* buf, int size){
	
	if (write(i2cFile, buf, size) != size) {
		printf("i2c_write: %s\n", strerror(errno));
		return 0;
		/* ERROR HANDLING: i2c transaction failed */
	}
	return 1;
	
}
	
void set_i2c_slave_address(int addr){
	if (ioctl(i2cFile, I2C_SLAVE, addr) < 0) {
		printf("set_i2c_address %d: %s\n", addr, strerror(errno));
	
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	
}
