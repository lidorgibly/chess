#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>


	int i2cFile;
	int adapterNum = 1; 	
	char fileName[20];
	
	//addr = 0x20
	


	
	
void init_i2c(){
	snprintf(fileName, 19, "/dev/i2c-%d", adapterNum);
	i2cFile = open(fileName, O_RDWR);
	if (i2cFile < 0) {
	/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	
}
	
	
	
void i2c_read(char* buf, int size){
	if (read(i2cFile, buf, size) != size){
	/* ERROR HANDLING: i2c transaction failed */
	}else{
		printf("%d %d", buf[0], buf[1]);

	}
	
	
}

void i2c_write(char* buf, int size){
	
	if (write(i2cFile, buf, size) != size) {
	/* ERROR HANDLING: i2c transaction failed */
	}
	
}
	
void set_i2c_slave_address(int addr){
	if (ioctl(i2cFile, I2C_SLAVE, addr) < 0) {
	/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	
}
