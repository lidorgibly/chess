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
#define HTTP_UPDATE_TIME_US 1000000	//1sec



extern bool LED_Board[8][8];

extern _piece_type board[8][8];
extern _IOsDevice device4;







int main(){
	init_i2c();
	init_board();
	init_LEDs();	
	init_contact_sensors();
	//if (!is_init_state())
	//	raise_error(NotStartingPositionAtStartup);
	print_board(board);
	char move[10];

	char data[2];

//printf("move empty: %c %c %c %c", move[0], move[1], move[2], move[3]);

	




	while (true)
	{
		//if (is_init_state())
			//init_board();

		//fputs("enter a move: (example: b1-c3)");
		fputs("enter a command: (example: upb2, downf5)", stdout);

		fgets(move, 10,stdin);	

		read_all_IOs(&data[0], &data[1], &device4);
		printf("read contact_sensors %d %d\n", data[0], data[1]);
		
		if (strstr(move, "up")){
			_coordinates coo;
			
			coo.x = chess_letter_to_x_coordinate(move[2]);
			coo.y = chess_char_to_y_coordinate(move[3]);
			piece_up(coo);
			
		}
		if (strstr(move, "down")){
			_coordinates coo;
			
			coo.x = chess_letter_to_x_coordinate(move[4]);
			coo.y = chess_char_to_y_coordinate(move[5]);
			piece_down(coo);
			
		}
		
		

		usleep(HTTP_UPDATE_TIME_US);



	}
	
}



