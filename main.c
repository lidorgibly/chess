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

extern _IOsDevice device4;
extern _IOsDevice device5;
extern _IOsDevice device6;
extern _IOsDevice device7;

char data[4];
_coordinates coo, coor;
_IOsDevice* device;
_port port;

int main(){
	init_i2c();
	init_LEDs();	
	init_contact_sensors();


	
	//LED_on_all();

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
		read_all_IOs(&data[0], &data[1], &device5);
		printf("y0 is %d\n", data[0]);	
		printf("y1 is %d\n", data[1]);	
		
		read_all_IOs(&data[2], &data[3], &device5);
		printf("y2 is %d\n", data[2]);	
		printf("y3 is %d\n", data[3]);	
		read_all_IOs(&data[2], &data[3], &device6);
		printf("y2 is %d\n", data[2]);	
		printf("y3 is %d\n", data[3]);	
		read_all_IOs(&data[2], &data[3], &device7);
		printf("y2 is %d\n", data[2]);	
		printf("y3 is %d\n", data[3]);	
		*/
		for (int k=0;k<8;k++){
			coo.y = k;

			for (int n=0;n<8;n++){
				coo.x = n;
				//LED_on_off(coo, ON);
				//fgets(data, 2,stdin);	

				if (coo.y==0){	//device0 port0
					device = &device4;
					port = PORT0;		
				}
				if (coo.y==1){	//device0 port1
					device = &device4;
					port = PORT1;		
					
				}
				if (coo.y==2){	//device1 port0
					device = &device5;
					port = PORT0;		
					
				}
				if (coo.y==3){	//device1 port1
					device = &device5;
					port = PORT1;		

				}
				if (coo.y==4){	//device2 port0
					device = &device6;
					port = PORT0;		

				}
				if (coo.y==5){	//device2 port1

					device = &device6;
					port = PORT1;		

				}
				if (coo.y==6){	//device3 port0
					device = &device7;
					port = PORT0;		

				}
				if (coo.y==7){	//device3 port1
					device = &device7;
					port = PORT1;		

				}
				//read_all_IOs(data, data, device);
				if (read_IO( port, (_pin)coo.x, device) == ZERO){
					printf("%d, %d\n", coo.x, coo.y);
					
					LED_on_off(coo, ON);
				}else{

					
					LED_on_off(coo, OFF);
					
				}
				
				//usleep(10);

			} 
		}

		//usleep(1500);

	}

	
	
	while (true)
	{
		



		usleep(HTTP_UPDATE_TIME_US);



	}
	
}



	
	
	

	


	
	
