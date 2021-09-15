#include "chess.h"
#include <stdbool.h>




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
	board[3][0] = Bottom_King;
	board[4][0] = Bottom_Queen;
	board[5][0] = Bottom_Bishop;
	board[6][0] = Bottom_Knight;
	board[7][0] = Bottom_Rook;
	for (int x=0;x<8;x++)
		board[x][1]= Bottom_Pawn;
	
			
	board[0][7] = Top_Rook;
	board[1][7] = Top_Knight;
	board[2][7] = Top_Bishop;
	board[3][7] = Top_King;
	board[4][7] = Top_Queen;
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
		if (board[x][0]!=None) 
			return false;
	for (int x=0;x<8;x++)
		if (board[x][1]!=None) 
			return false;
	for (int x=0;x<8;x++)
		if (board[x][6]!=None) 
			return false;
	for (int x=0;x<8;x++)
		if (board[x][7]!=None) 
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
		
	
	
	
	board[coo.x][coo.y] = None;

	
	
	
	
	
	
}

void piece_down(_coordinates coo){
	
	
	if (firstUp.pieceType==None){	//maybe the players got up 2 pieces and got them down
		
		board[coo.x][coo.y] = lastEat.pieceType;
		board[lastEaten.originLocation.x][lastEaten.originLocation.y] = lastEaten.pieceType;
		
		
		
	}else if (secondUp.pieceType==None){			
		
		board[coo.x][coo.y] = firstUp.pieceType;
		firstUp.pieceType = None;
		
		
	
	}else if (thirdUp.pieceType==None){		//maybe piece eated another piece
		if (is_same_location(coo, secondUp.originLocation)){		
			board[coo.x][coo.y] = firstUp.pieceType;
			lastEaten = secondUp;
			lastEat = firstUp;
		}else if (is_same_location(coo, firstUp.originLocation)){		
			board[coo.x][coo.y] = secondUp.pieceType;
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

void bishop_movement(_piece_type** board, bool** LEDs, _piece piece){
	
	int nextCooX;
	int nextCooY;

	//up right movement
	nextCooX =  piece.originLocation.x + 1;
	nextCooY =  piece.originLocation.y + 1;
	
	while ((is_in_board(nextCooX, nextCooY)) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooX =  piece.originLocation.x + 1;
		nextCooY =  piece.originLocation.y + 1;
	}
	//up left movement
	nextCooX =  piece.originLocation.x - 1 ;
	nextCooY =  piece.originLocation.y + 1;


	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooX =  piece.originLocation.x - 1 ;
		nextCooY =  piece.originLocation.y + 1;
	}
	
	//down right movement
	nextCooX =  piece.originLocation.x + 1;
	nextCooY =  piece.originLocation.y - 1;
	
	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooX =  piece.originLocation.x + 1;
		nextCooY =  piece.originLocation.y - 1;
	}
	
	//down left movement
	
	nextCooX =  piece.originLocation.x - 1 ;
	nextCooY =  piece.originLocation.y - 1;
	
	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooX =  piece.originLocation.x - 1 ;
		nextCooY =  piece.originLocation.y - 1;
	}
	
	
	
}





void rook_movement(_piece_type** board, bool** LEDs, _piece piece){
	
	int nextCooX;
	int nextCooY;

	//up movement
	nextCooX =  piece.originLocation.x;
	nextCooY =  piece.originLocation.y + 1;
	
	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooY =  piece.originLocation.y + 1;
	}
	//right movement
	nextCooX =  piece.originLocation.x + 1 ;
	nextCooY =  piece.originLocation.y;
	
	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooX =  piece.originLocation.x + 1;
	}
	
	//down movement
	nextCooX =  piece.originLocation.x;
	nextCooY =  piece.originLocation.y - 1;
	
	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooY =  piece.originLocation.y - 1;
	}
	
	//left movement
	
	nextCooX =  piece.originLocation.x - 1 ;
	nextCooY =  piece.originLocation.y;
	
	while (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None)){
		LEDs[nextCooX][nextCooY] = 1;
		nextCooX =  piece.originLocation.x - 1 ;
	}
	
}
void queen_movement(_piece_type** board, bool** LEDs, _piece piece){
	rook_movement(board, LEDs, piece);
	bishop_movement(board, LEDs, piece);
	
}
void king_movement(_piece_type** board, bool** LEDs, _piece piece){
	
	
	int nextCooX;
	int nextCooY;


	//up movement
	nextCooX =  piece.originLocation.x;
	nextCooY =  piece.originLocation.y + 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	//right movement
	nextCooX =  piece.originLocation.x + 1 ;
	nextCooY =  piece.originLocation.y;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	
	//down movement
	nextCooX =  piece.originLocation.x;
	nextCooY =  piece.originLocation.y - 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	
	//left movement
	
	nextCooX =  piece.originLocation.x - 1 ;
	nextCooY =  piece.originLocation.y;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;


	//up right movement
	nextCooX =  piece.originLocation.x + 1;
	nextCooY =  piece.originLocation.y + 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	//up left movement
	nextCooX =  piece.originLocation.x - 1 ;
	nextCooY =  piece.originLocation.y + 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	
	//down right movement
	nextCooX =  piece.originLocation.x + 1;
	nextCooY =  piece.originLocation.y - 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	
	//down left movement
	
	nextCooX =  piece.originLocation.x - 1 ;
	nextCooY =  piece.originLocation.y - 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	
	
	
}

void top_pawn_movement(_piece_type** board, bool** LEDs, _piece piece){
	int nextCooX =  piece.originLocation.x;
	int nextCooY =  piece.originLocation.y - 1;
	
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;

	
	
}
void bottom_pawn_movement(_piece_type** board, bool** LEDs, _piece piece){
	
	int nextCooX =  piece.originLocation.x;
	int nextCooY =  piece.originLocation.y + 1;
	if (is_in_board(nextCooX, nextCooY) && (board[nextCooX][nextCooY]==None))
		LEDs[nextCooX][nextCooY] = 1;
	
}