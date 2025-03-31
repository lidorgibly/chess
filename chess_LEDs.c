#include <stdio.h>
#include "chess.h"
#include "chess_LEDs.h"
#ifdef LINUX
#include "PCF8575_linux.h"
#else
#include "PCF8575.h"
#endif



_LED_state LED_Board[8][8];

extern _piece_type board[8][8];


_IOsDevice device0;
_IOsDevice device1;
_IOsDevice device2;
_IOsDevice device3;

void init_LEDs(){
	device0.address = I2C_DEVICE0_ADDRESS;
	device1.address = I2C_DEVICE1_ADDRESS;
	device2.address = I2C_DEVICE2_ADDRESS;
	device3.address = I2C_DEVICE3_ADDRESS;
	LED_off_all();


	
}

//typedef struct LED{
//    _LED_state state;
//} _LED;


void LED_on_off(_coordinates coo, _LED_state on_off){
	
	_IOsDevice* device;
	
	//////////////////////////
	//board[coo.x][coo.y] = -1;
	////////////////////////////
	
	
	
	_port port;
	_bit bit;
	
	
	if (on_off==ON){
		//TODO
		printf("LED on\n");
		bit = 0;
			
	}else{
		//TODO
		printf("LED off\n");
		bit = 1;
	}
	
	if (coo.y==0){	//device0 port0
		device = &device0;
		port = PORT0;		
	}
	if (coo.y==1){	//device0 port1
		device = &device0;
		port = PORT1;		
		
	}
	if (coo.y==2){	//device1 port0
		device = &device1;
		port = PORT0;		
		
	}
	if (coo.y==3){	//device1 port1
		device = &device1;
		port = PORT1;		

	}
	if (coo.y==4){	//device2 port0
		device = &device2;
		port = PORT0;		

	}
	if (coo.y==5){	//device2 port1
		device = &device2;
		port = PORT1;		

	}
	if (coo.y==6){	//device3 port0
		device = &device3;
		port = PORT0;		

	}
	if (coo.y==7){	//device3 port1
		device = &device3;
		port = PORT1;		

	}
	

	write_IO(port, coo.x, bit, device);	//output mode


	
}



void LED_on_all(){


	write_all_IOs( 0x00,  0x00, &device0);
	write_all_IOs( 0x00,  0x00, &device1);
	write_all_IOs( 0x00,  0x00, &device2);
	write_all_IOs( 0x00,  0x00, &device3);

	



}


void LED_off_all(){
	
	
	/*
	for (int y=7;y>=0;y--){
		for (int x=0;x<8;x++){
			
			if (board[x][y] == -1)
				board[x][y] = None;
		}
		
	}
	
	*/
	
	write_all_IOs( 0xff,  0xff, &device0);
	
	write_all_IOs( 0xff,  0xff, &device1);
	
	write_all_IOs( 0xff,  0xff, &device2);

	write_all_IOs( 0xff,  0xff, &device3);
	
}




	
	

