#include "chess.h"
#include "chess_error.h"

#include "chess_http.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
//#include <synchapi.h>



#define HTTP_UPDATE_TIME_US 1000000	//1sec





extern bool LED_Board[8][8];

extern _piece_type board[8][8];




int main(){
	
	
	//if (!is_init_state())
	//	raise_error(NotStartingPositionAtStartup);


	while (true)
	{
		if (is_init_state())
			init_board();

		//Sleep(1000);
		usleep(HTTP_UPDATE_TIME_US);


		printf("send_http\n");
		http_send_board(board);
		printf("sent_http\n\n");

	}
	
}