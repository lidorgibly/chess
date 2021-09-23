#include "chess.h"
#include "chess_http.h"
#include <stdbool.h>
#include <stdio.h>

#include "chess_LEDs.h"


_piece_type board[8][8];


_piece lastEaten;
_piece lastEat;



_piece firstUp;
_piece secondUp;
_piece thirdUp;

_coordinates coo;



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
	
	if (firstUp.pieceType==None){
		
		firstUp.pieceType = board[coo.x][coo.y];
		firstUp.originLocation = coo;
		
		
		
		//show_permitted_locations(_coordinates);
		
		
	}else if(secondUp.pieceType==None){
		
		
		secondUp.pieceType = board[coo.x][coo.y];
		secondUp.originLocation = coo;

	}else{
		
		thirdUp.pieceType = board[coo.x][coo.y];
		thirdUp.originLocation = coo;
		
	}
		
	
	
	
	//board[coo.x][coo.y] = None;

	
	
	
	
	
	
}

void piece_down(_coordinates coo){
	
	
	if (firstUp.pieceType==None){	//maybe the players got up 2 pieces and got them down
		
		board[coo.x][coo.y] = lastEat.pieceType;
		board[lastEaten.originLocation.x][lastEaten.originLocation.y] = lastEaten.pieceType;
		
		printf("firstUp None\n");

		
	}else if (secondUp.pieceType==None){			
		
		printf("secondUp None\n");
		make_move(firstUp.originLocation, coo);
		

		firstUp.pieceType = None;
		
	
	}else if (thirdUp.pieceType==None){		//maybe piece eated another piece
			printf("thirdUp None\n");

		if (is_same_location(coo, secondUp.originLocation)){		
			
														//first eat second
			make_move(firstUp.originLocation, coo);

			lastEaten = secondUp;
			lastEat = firstUp;
		}else if (is_same_location(coo, firstUp.originLocation)){		
			make_move(secondUp.originLocation, coo);		// second eat first
			lastEaten = firstUp;
			lastEat = secondUp;

		}
		
		firstUp.pieceType = None;
		secondUp.pieceType = None;
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
	

	//up right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y + 1;
	
	while ((is_in_board(nextCoo.x, nextCoo.y)) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.x =  originLocation.x + 1;
		nextCoo.y =  originLocation.y + 1;
	}
	//up left movement
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y + 1;


	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.x =  originLocation.x - 1 ;
		nextCoo.y =  originLocation.y + 1;
	}
	
	//down right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y - 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.x =  originLocation.x + 1;
		nextCoo.y =  originLocation.y - 1;
	}
	
	//down left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y - 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.x =  originLocation.x - 1 ;
		nextCoo.y =  originLocation.y - 1;
	}
	
	
	
}





void show_rook_movement_LEDs(_coordinates originLocation){
	
	int nextCoo.x;
	int nextCoo.y;

	//up movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y + 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.y =  originLocation.y + 1;
	}
	//right movement
	nextCoo.x =  originLocation.x + 1 ;
	nextCoo.y =  originLocation.y;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.x =  originLocation.x + 1;
	}
	
	//down movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y - 1;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.y =  originLocation.y - 1;
	}
	
	//left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y;
	
	while (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None)){
		LED_on_off(nextCoo, true);
		nextCoo.x =  originLocation.x - 1 ;
	}
	
}
void show_queen_movement_LEDs(_coordinates originLocation){
	show_rook_movement_LEDs(originLocation);
	show_bishop_movement_LEDs(originLocation);
	
}
void show_king_movement_LEDs(_coordinates originLocation){
	
	
	int nextCoo.x;
	int nextCoo.y;


	//up movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	//right movement
	nextCoo.x =  originLocation.x + 1 ;
	nextCoo.y =  originLocation.y;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	
	//down movement
	nextCoo.x =  originLocation.x;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	
	//left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);


	//up right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	//up left movement
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y + 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	
	//down right movement
	nextCoo.x =  originLocation.x + 1;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	
	//down left movement
	
	nextCoo.x =  originLocation.x - 1 ;
	nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	
	
	
}

void show_top_pawn_movement_LEDs(_coordinates originLocation){
	int nextCoo.x =  originLocation.x;
	int nextCoo.y =  originLocation.y - 1;
	
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);

	
	
}
void show_bottom_pawn_movement_LEDs(_coordinates originLocation){
	
	int nextCoo.x =  originLocation.x;
	int nextCoo.y =  originLocation.y + 1;
	if (is_in_board(nextCoo.x, nextCoo.y) && (board[nextCoo.x][nextCoo.y]==None))
		LED_on_off(nextCoo, true);
	
}



void show_permitted_locations(_coordinates coo){
	
	_piece_type pieceType = board[coo.x][coo.y];
	
	if (pieceType == Bottom_Rook || Top_Rook)
		show_rook_movement_LEDs(coo);
	if (pieceType == Bottom_Knight || Top_Knight)
		show_knight_movement_LEDs(coo);
	if (pieceType == Bottom_Bishop || Top_Bishop)
		show_bishop_movement_LEDs(coo);
	if (pieceType == Bottom_Queen || Top_Queen)
		show_queen_movement_LEDs(coo);
	if (pieceType == Bottom_King || Top_King)
		show_king_movement_LEDs(coo);
	
	if (pieceType == Bottom_Pawn)
		show_bottom_pawn_movement_LEDs(coo);
	if (pieceType == Top_Pawn)
		show_top_pawn_movement_LEDs(coo);

}






void make_move(_coordinates origin, _coordinates destination){
	
	board[destination.x][destination.y] = board[origin.x][origin.y];
	board[origin.x][origin.y] = None;

	
	char move[6];
	coordinates_to_chess_move(origin, destination, move);
	http_send_move(move);
	
	
	print_board(board);
}

void coordinates_to_chess_move(_coordinates origin, _coordinates destination, char move[]){
	
	sprintf(move,"%c%c-%c%c", chess_x_coordinate_to_letter(origin.x), chess_y_coordinate_to_char(origin.y), chess_x_coordinate_to_letter(destination.x), chess_y_coordinate_to_char(destination.y));

	
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




void print_board(_piece_type board[8][8]){
	
	for (int y=7;y>=0;y--){
		for (int x=0;x<8;x++){
			
			printf("| %c-%c | ", piece_type_to_char(board[x][y]), piece_type_to_color(board[x][y]));
			
			
		}
		printf("\n");
	}
}






