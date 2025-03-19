#include "chess.h"
#include "chess_error.h"
#include "chess_LEDs.h"
#include "chess_http.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "contact_sensor.h"

#ifdef LINUX
#include "i2c_linux.h"
#include "PCF8575_linux.h"
#endif

#define HTTP_UPDATE_TIME_US 1000	//1sec



extern bool LED_Board[8][8];

extern _piece_type board[8][8];

extern _IOsDevice device0;
extern _IOsDevice device1;
extern _IOsDevice device2;
extern _IOsDevice device3;





int main(){
	init_i2c();
	init_LEDs();	
	

	char data[4];



	LED_on_all();
	//LED_on_off(coo, ON);

/*
	device0.address = I2C_DEVICE0_ADDRESS;
	device1.address = I2C_DEVICE1_ADDRESS;
	device2.address = I2C_DEVICE2_ADDRESS;
	device3.address = I2C_DEVICE3_ADDRESS;
	device4.address = I2C_DEVICE4_ADDRESS;

 	write_all_IOs(0x00, 0x00, &device0);	//output mode
	write_all_IOs(0x00, 0x00, &device1);	//output mode
	write_all_IOs(0x00, 0x00, &device2);	//output mode
	write_all_IOs(0x00, 0x00, &device3);	//output mode
	write_all_IOs(0x00, 0x00, &device4);	//output mode
	fgets(data, 2,stdin);	
	write_all_IOs(0xFF, 0xFF, &device0);	//output mode
	write_all_IOs(0xFF, 0xFF, &device1);	//output mode
	write_all_IOs(0xFF, 0xFF, &device2);	//output mode
	write_all_IOs(0xFF, 0xFF, &device3);	//output mode
	write_all_IOs(0xFF, 0xFF, &device4);	//output mode
	*/
	//fgets(data, 1,stdin);	

	//while(true);


	while(true){
		/*	
		read_all_IOs(&data[0], &data[1], &device4);
		printf("y0 is %d\n", data[0]);	
		printf("y1 is %d\n", data[1]);	
			
		read_all_IOs(&data[2], &data[3], &device5);
		printf("y2 is %d\n", data[2]);	
		printf("y3 is %d\n", data[3]);	
		

		*/
	

		usleep(1500);

	}

	
	
	while (true)
	{
		



		usleep(HTTP_UPDATE_TIME_US);



	}
	
}



	
	
	

	


	
	
