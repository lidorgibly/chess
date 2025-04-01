#include "chess.h"
#include "chess_error.h"
#include "chess_LEDs.h"
#include "chess_http.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "sensors.h"
#include <pthread.h>

#ifdef LINUX
#include "i2c_linux.h"
#include "PCF8575_linux.h"
#endif

#define HTTP_UPDATE_TIME_US 1000	//1sec


_IO_position coordinate_to_sensor_IO(_coordinates coo);
_IO_position coordinate_to_LED_IO(_coordinates coo);
void* board_state_thread(void* arg);
void* game_init_thread(void* arg);

_sensor_state Sensors_Board[8][8];
_LED_state LED_Board[8][8];

extern _piece_type board[8][8];
extern _IOsDevice device0;
extern _IOsDevice device1;
extern _IOsDevice device2;
extern _IOsDevice device3;
extern _IOsDevice device4;
extern _IOsDevice device5;
extern _IOsDevice device6;
extern _IOsDevice device7;

int gameInit = 1;
pthread_t boardStateThread, gameInitThread;
pthread_mutex_t i2cMutex, gameInitMutex;

int main(){
	char data[4];
	init_i2c();
	init_LEDs();	
	init_contact_sensors();

	init_board();

	

	pthread_mutex_init(&i2cMutex, NULL);
	pthread_mutex_init(&gameInitMutex, NULL);

	pthread_create(&gameInitThread, NULL, game_init_thread, NULL);

	fgets(data, 2,stdin);
	pthread_mutex_lock(&gameInitMutex);
	gameInit = 0;
	pthread_mutex_unlock(&gameInitMutex);
	pthread_join(gameInitThread, NULL);
	LED_off_all();

	pthread_create(&boardStateThread, NULL, board_state_thread, NULL);




	pthread_join(boardStateThread, NULL);
	pthread_mutex_destroy(&gameInitMutex);
    pthread_mutex_destroy(&i2cMutex);




}



	
	




_IO_position coordinate_to_LEDS_IO(_coordinates coo)
{
	_IO_position pos;
	pos.pin = (_pin)coo.x;
	if (coo.y==0)
	{	//device0 port0
		pos.device = device0;
		pos.port = PORT0;		
	}
	if (coo.y==1){	//device0 port1
		pos.device = device0;
		pos.port = PORT1;		
		
	}
	if (coo.y==2){	//device1 port0
		pos.device = device1;
		pos.port = PORT0;		
		
	}
	if (coo.y==3){	//device1 port1
		pos.device = device1;
		pos.port = PORT1;		

	}
	if (coo.y==4){	//device2 port0
		pos.device = device2;
		pos.port = PORT0;		

	}
	if (coo.y==5){	//device2 port1

		pos.device = device2;
		pos.port = PORT1;		

	}
	if (coo.y==6){	//device3 port0
		pos.device = device3;
		pos.port = PORT0;		

	}
	if (coo.y==7){	//device3 port1
		pos.device = device3;
		pos.port = PORT1;		

	}
	return pos;


}

_IO_position coordinate_to_sensor_IO(_coordinates coo)
{	
	_IO_position pos;
	pos.pin = (_pin)coo.x;
	if (coo.y==0)
	{	//device0 port0
		pos.device = device4;
		pos.port = PORT0;		
	}
	if (coo.y==1){	//device0 port1
		pos.device = device4;
		pos.port = PORT1;		
		
	}
	if (coo.y==2){	//device1 port0
		pos.device = device5;
		pos.port = PORT0;		
		
	}
	if (coo.y==3){	//device1 port1
		pos.device = device5;
		pos.port = PORT1;		

	}
	if (coo.y==4){	//device2 port0
		pos.device = device6;
		pos.port = PORT0;		

	}
	if (coo.y==5){	//device2 port1

		pos.device = device6;
		pos.port = PORT1;		

	}
	if (coo.y==6){	//device3 port0
		pos.device = device7;
		pos.port = PORT0;		

	}
	if (coo.y==7){	//device3 port1
		pos.device = device7;
		pos.port = PORT1;		

	}
	return pos;
}

void* board_state_thread(void* arg){
	_coordinates coo;
	while(true)
	{
			
		for (int k=0;k<8;k++)
		{
			coo.y = k;
			for (int n=0;n<8;n++)
			{
				coo.x = n;
				//LED_on_off(coo, ON);
				//fgets(data, 2,stdin);	


				if (read_IO(coordinate_to_sensor_IO(coo)) == ZERO){
					if (Sensors_Board[coo.x][coo.y] == OPEN)	//changed to close
					{
						Sensors_Board[coo.x][coo.y] = CLOSE;
						piece_down(coo);

					}
						
					//LED_on_off(coo, ON);
					//printf("%d, %d\n", coo.x, coo.y);
					//if (is_sensor_changed(ON, _coordinates coo))
						//piece_down(coo);
				}else{
					if (Sensors_Board[coo.x][coo.y] == CLOSE)	//changed to close
					{
						Sensors_Board[coo.x][coo.y] = OPEN;
						piece_up(coo);

					}
					//LED_on_off(coo, OFF);

					//if (is_sensor_changed(ON, _coordinates coo))						
					//	piece_up(coo);
					
				}
				pthread_mutex_unlock(&i2cMutex);

			} 
		}
		//usleep(1500);
	}
}

void* game_init_thread(void* arg)
{	
	_coordinates coo;
	while(gameInit)
	{
		pthread_mutex_unlock(&gameInitMutex);

		for (int k=0;k<8;k++)
		{
			coo.y = k;
			for (int n=0;n<8;n++)
			{
				coo.x = n;
				//LED_on_off(coo, ON);
				//fgets(data, 2,stdin);	


				pthread_mutex_lock(&i2cMutex);
				//read_all_IOs(data, data, device);
				if (read_IO(coordinate_to_sensor_IO(coo)) == ZERO)
				{				
					Sensors_Board[coo.x][coo.y] = CLOSE;		
					LED_on_off(coo, ON);
					//printf("%d, %d\n", coo.x, coo.y);
					//if (is_sensor_changed(ON, _coordinates coo))
						//piece_down(coo);
				}else{	
					Sensors_Board[coo.x][coo.y] = OPEN;		
					LED_on_off(coo, OFF);			
				}
				pthread_mutex_unlock(&i2cMutex);

			} 
		}
		pthread_mutex_lock(&gameInitMutex);
	}



}
	


	


	
	
