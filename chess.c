#include "chess.h"
#include "chess_http.h"
#include <stdbool.h>
#include <stdio.h>

#include "chess_LEDs.h"



_piece_type board[8][8];



_piece firstUp;
_piece secondUp;




void show_bishop_movement_LEDs(_coordinates originLocation);
void show_rook_movement_LEDs(_coordinates originLocation);
void show_queen_movement_LEDs(_coordinates originLocation);
void show_king_movement_LEDs(_coordinates originLocation);
void show_knight_movement_LEDs(_coordinates originLocation);
void show_top_pawn_movement_LEDs(_coordinates originLocation);
void show_bottom_pawn_movement_LEDs(_coordinates originLocation);
void show_permitted_locations(_coordinates coo);





void init_board(){
	
	board[0][0] = Bottom_Rook;
	board[1][0] = Bottom_Knight;
	board[2][0] = Bottom_Bishop;
	board[3][0] = Bottom_Queen;
	board[4][0] = Bottom_King;
	board[5][0] = Bottom_Bishop;
	board[6][0] = Bottom_Knight;
	board[7][0] = Bottom_Rook;
	for (int x=0;x<8;x++)
		board[x][1]= Bottom_Pawn;
	
	
	
	
	board[0][7] = Top_Rook;
	board[1][7] = Top_Knight;
	board[2][7] = Top_Bishop;
	board[3][7] = Top_Queen;
	board[4][7] = Top_King;
	board[5][7] = Top_Bishop;
	board[6][7] = Top_Knight;
	board[7][7] = Top_Rook;
	for (int x=0;x<8;x++)
		board[x][6]= Top_Pawn; 




	firstUp.pieceType = None;
	secondUp.pieceType = None;

}


bool is_init_state(){

	for (int x=0;x<8;x++)
		if (board[x][0]==None) 
			return false;
	for (int x=0;x<8;x++)
		if (board[x][1]==None) 
			return false;
	for (int x=0;x<8;x++)
		if (board[x][6]==None) 
			return false;
	for (int x=0;x<8;x++)
		if (board[x][7]==None) 
			return false;
		
		
	return true;
}




void piece_up(_coordinates coo){
	
	LED_on_off(coo, OFF);

	show_permitted_locations(coo);
	print_board(board);
	
	if (firstUp.pieceType==None){
		
		firstUp.pieceType = board[coo.x][coo.y];
		firstUp.originLocation = coo;		
		
	}else if(secondUp.pieceType==None){
		
		
		secondUp.pieceType = board[coo.x][coo.y];
		secondUp.originLocation = coo;

	}
		
	

	
	
	
}

void piece_down(_coordinates coo){
	
	LED_on_off(coo, ON);


	if (secondUp.pieceType==None){			
		
		printf("secondUp None\n");
		make_move(firstUp.originLocation, coo);
		firstUp.pieceType = None;
		LED_off_all();
	
	}else {		//maybe piece eated another piece
			//printf("thirdUp None\n");

		if (is_same_location(coo, secondUp.originLocation)){		
			
														//first eat second
			make_move(firstUp.originLocation, coo);		
		
		}else if (is_same_location(coo, firstUp.originLocation)){		
			make_move(secondUp.originLocation, coo);		// second eat first
			

		}
		
		firstUp.pieceType = None;
		secondUp.pieceType = None;
		LED_off_all();

	}
	
	
}

bool is_same_location(_coordinates c1, _coordinates c2){
	

	if ((c1.x==c2.x)&&(c1.y==c2.y))
		return true;
	return false;
	
}		




bool is_in_board(int cooX, int cooY){
	
	if ((cooX >= 0)&&(cooX <=7)&&(cooY >= 0)&&(cooY <=7))
		return true;
	return false;
	
}

void show_bishop_movement_LEDs(_coordinates originLocation){
	
	_coordinates nextCoo;
	
	LED_on_off(originLocation, ON);
	//up right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y + 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.x =  nextCoo.x + 1;
		nextCoo.y =  nextCoo.y + 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//up left movement
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y + 1;


	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.x =  nextCoo.x - 1 ;
		nextCoo.y =  nextCoo.y + 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//down right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y - 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.x =  nextCoo.x + 1;
		nextCoo.y =  nextCoo.y - 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//down left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y - 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.x =  nextCoo.x - 1 ;
		nextCoo.y =  nextCoo.y - 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	
}





void show_rook_movement_LEDs(_coordinates originLocation){
	
	_coordinates nextCoo;
	LED_on_off(originLocation, ON);
	//up movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y + 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.y =  nextCoo.y + 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//right movement
	nextCoo.x =  originLocation.x + 1 ;
	nextCoo.y =  originLocation.y;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.x =  nextCoo.x + 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//down movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y - 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.y =  nextCoo.y - 1;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, ON);
		nextCoo.x =  nextCoo.x - 1 ;
	}
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
}
void show_queen_movement_LEDs(_coordinates originLocation){
	show_rook_movement_LEDs(originLocation);
	show_bishop_movement_LEDs(originLocation);
	
}
void show_king_movement_LEDs(_coordinates originLocation){
	
	_coordinates nextCoo;
	

	LED_on_off(originLocation, ON);

	//up movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//right movement
	nextCoo.x =  originLocation.x + 1 ;
	nextCoo.y =  originLocation.y;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	//down movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	//left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);


	//up right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	//up left movement
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	//down right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	//down left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	
	
}

void show_knight_movement_LEDs(_coordinates originLocation){
	_coordinates nextCoo;
	LED_on_off(originLocation, ON);

	nextCoo.x =  originLocation.x + 2;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	nextCoo.x =  originLocation.x + 2;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y - 2;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y + 2;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	nextCoo.x =  originLocation.x - 2;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	nextCoo.x =  originLocation.x - 2;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	
	nextCoo.x =  originLocation.x - 1;
	nextCoo.y =  originLocation.y + 2;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
	nextCoo.x =  originLocation.x - 1;
	nextCoo.y =  originLocation.y - 2;
	
	if (is_in_board(nextCoo.x, nextCoo.y))
		LED_on_off(nextCoo, ON);
}

void show_top_pawn_movement_LEDs(_coordinates originLocation){
	
	_coordinates nextCoo;
	LED_on_off(originLocation, ON);

	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, ON);
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y - 1;
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]!=None))
		LED_on_off(nextCoo, ON);
	nextCoo.x =  originLocation.x - 1;
	nextCoo.y =  originLocation.y - 1;
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]!=None))
		LED_on_off(nextCoo, ON);
}
void show_bottom_pawn_movement_LEDs(_coordinates originLocation){
	_coordinates nextCoo;
	LED_on_off(originLocation, ON);
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y + 1;
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, ON);
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y + 1;
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]!=None))
		LED_on_off(nextCoo, ON);
	nextCoo.x =  originLocation.x - 1;
	nextCoo.y =  originLocation.y + 1;
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]!=None))
		LED_on_off(nextCoo, ON);
}



void show_permitted_locations(_coordinates coo){
	
	_piece_type pieceType = board[coo.x][coo.y];
	
	if ((pieceType == Bottom_Rook) || (pieceType == Top_Rook))
		show_rook_movement_LEDs(coo);
	if ((pieceType == Bottom_Knight) || (pieceType == Top_Knight))
		show_knight_movement_LEDs(coo);
	if ((pieceType == Bottom_Bishop) || (pieceType == Top_Bishop))
		show_bishop_movement_LEDs(coo);
	if ((pieceType == Bottom_Queen) || (pieceType == Top_Queen))
		show_queen_movement_LEDs(coo);
	if ((pieceType == Bottom_King) || (pieceType == Top_King))
		show_king_movement_LEDs(coo);
	
	if (pieceType == Bottom_Pawn)
		show_bottom_pawn_movement_LEDs(coo);
	if (pieceType == Top_Pawn)
		show_top_pawn_movement_LEDs(coo);

}






void make_move(_coordinates origin, _coordinates destination){
	
	
	
	board[destination.x][destination.y] = board[origin.x][origin.y];
	if ((origin.x != destination.x) || (origin.y != destination.y))
		board[origin.x][origin.y] = None;

	
	
	
	//http_send_move(origin, destination);
	
	
	print_board(board);
}


//x = 0 to 7
char chess_x_coordinate_to_letter(int x){
	return (char)(x + 97);
	
	
}
//y = 0 to 7
char chess_y_coordinate_to_char(int y){
	return (char)(y + 49);
	
	
}


int chess_letter_to_x_coordinate(char letter){
	return (int)letter-97;

	
}

int chess_char_to_y_coordinate(char yChar){
	return (int)yChar-49;
}



char piece_type_to_char(_piece_type pieceType){
	if (pieceType == -1)
		return 'L';
	
	
	if (pieceType == Top_King)
		return 'k';
	if (pieceType == Top_Queen)
		return 'q';
	if (pieceType == Top_Bishop)
		return 'b';
	if (pieceType == Top_Rook)
		return 'r';
	if (pieceType == Top_Knight)
		return 'n';
	if (pieceType == Top_Pawn)
		return 'p';
	
	if (pieceType == Bottom_King)
		return 'k';
	if (pieceType == Bottom_Queen)
		return 'q';
	if (pieceType == Bottom_Bishop)
		return 'b';
	if (pieceType == Bottom_Rook)
		return 'r';
	if (pieceType == Bottom_Knight)
		return 'n';
	if (pieceType == Bottom_Pawn)
		return 'p';
	if (pieceType == None)
		return ' ';
}

char piece_type_to_color(_piece_type pieceType){
	
	if (pieceType == -1)
		return ' ';
	
	
	if (pieceType == Top_King)
		return 'b';
	if (pieceType == Top_Queen)
		return 'b';
	if (pieceType == Top_Bishop)
		return 'b';
	if (pieceType == Top_Rook)
		return 'b';
	if (pieceType == Top_Knight)
		return 'b';
	if (pieceType == Top_Pawn)
		return 'b';
	
	if (pieceType == Bottom_King)
		return 'w';
	if (pieceType == Bottom_Queen)
		return 'w';
	if (pieceType == Bottom_Bishop)
		return 'w';
	if (pieceType == Bottom_Rook)
		return 'w';
	if (pieceType == Bottom_Knight)
		return 'w';
	if (pieceType == Bottom_Pawn)
		return 'w';


	if (pieceType == None)
		return ' ';


	

}

void print_board(_piece_type board[8][8]){
	printf("\n      a       b       c       d       e       f       g       h\n\n");
	
	for (int y=7;y>=0;y--){
		for (int x=0;x<8;x++){
			
			if (x==0)
				printf("%d  | %c-%c | ", y+1, piece_type_to_char(board[x][y]), piece_type_to_color(board[x][y]));
			else if (x==7)
				printf("| %c-%c |  %d", piece_type_to_char(board[x][y]), piece_type_to_color(board[x][y]), y+1);
			else
				printf("| %c-%c | ", piece_type_to_char(board[x][y]), piece_type_to_color(board[x][y]));
			
			
		}
		printf("\n\n");
	}
	
	printf("      a       b       c       d       e       f       g       h\n\n");
	
}






