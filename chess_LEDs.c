#include "chess.h"
#include "chess_LEDs.h"
#ifdef LINUX
#include "PCF8575_linux.h"
#else
#include "PCF8575.h"
#endif


typedef enum {ON, OFF} _LED_state;

_LED_state LED_Board[8][8];

extern _piece_type board[8][8];


_IOsDevice device0;
_IOsDevice device1;
_IOsDevice device2;
_IOsDevice device3;


void init_LEDs(){
	device0.address = I2C_DEVICE0_ADDRESS;
	write_all_IOs(0, 0, device0);
	device1.address = I2C_DEVICE1_ADDRESS;
	write_all_IOs(0, 0, device1);
	device2.address = I2C_DEVICE2_ADDRESS;
	write_all_IOs(0, 0, device2);
	device3.address = I2C_DEVICE3_ADDRESS;
	write_all_IOs(0, 0, device3);

	
}

//typedef struct LED{
//    _LED_state state;
//} _LED;


void LED_on_off(_coordinates coo, bool on_off){
	
	_IOsDevice device;
	
	
	_port port;
	_pin pin;
	_bit bit;
	
	
	if (on_off==1){
		//TODO
		//bit = ;
			
	}else{
		//TODO
		//bit = ;
	}
	
	if (coo.y==0){	//device0 port0
		device = device0;
		port = PORT0;		
	}
	if (coo.y==1){	//device0 port1
		device = device0;
		port = PORT1;		
		
	}
	if (coo.y==2){	//device1 port0
		device = device1;
		port = PORT0;		
		
	}
	if (coo.y==3){	//device1 port1
		device = device1;
		port = PORT1;		

	}
	if (coo.y==4){	//device2 port0
		device = device2;
		port = PORT0;		

	}
	if (coo.y==5){	//device2 port1
		device = device2;
		port = PORT1;		

	}
	if (coo.y==6){	//device3 port0
		device = device3;
		port = PORT0;		

	}
	if (coo.y==7){	//device3 port1
		device = device3;
		port = PORT1;		

	}
	

	write_IO(port, coo.x, bit, device);	//output mode


	
}



void LED_off_all(){
	
	
	//TODO
	//write_all_IOs( 0xff or 0x00,  0xff or 0x00, device0);
	//TODO
	//write_all_IOs( 0xff or 0x00,  0xff or 0x00, device1);
	//TODO
	//write_all_IOs( 0xff or 0x00,  0xff or 0x00, device2);
	//TODO
	//write_all_IOs( 0xff or 0x00,  0xff or 0x00, device3);
	
}




	
	

