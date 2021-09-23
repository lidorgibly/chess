#include "chess.h"
#include "chess_error.h"

#include "chess_http.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define HTTP_UPDATE_TIME_US 1000000	//1sec





extern bool LED_Board[8][8];

extern _piece_type board[8][8];









int main(){
	
	init_board();
	
	//if (!is_init_state())
	//	raise_error(NotStartingPositionAtStartup);

	char move[10];

//printf("move empty: %c %c %c %c", move[0], move[1], move[2], move[3]);

	




	while (true)
	{
		//if (is_init_state())
			//init_board();

		//fputs("enter a move: (example: b1-c3)");
		fputs("enter a command: (example: upb2, downf5)", stdout);

		fgets(move, 10,stdin);	



		
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
		
		
		//http_send_move(move);


		//is_init_state();
		usleep(HTTP_UPDATE_TIME_US);


		//printf("send_http\n");
		//http_send_board(board);
		//printf("sent_http\n\n");

	}
	
}