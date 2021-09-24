#ifndef _CHESS_H
#define _CHESS_H

#include <stdbool.h>

typedef enum {None, Top_King, Top_Queen, Top_Bishop, Top_Rook, Top_Knight, Top_Pawn, Bottom_King, Bottom_Queen, Bottom_Bishop, Bottom_Rook, Bottom_Knight, Bottom_Pawn} _piece_type;


typedef struct coordinates{
    int x;
	int y;

} _coordinates;


typedef struct piece{
    _coordinates originLocation;
	_piece_type pieceType;

} _piece;

void coordinates_to_chess_move(_coordinates origin, _coordinates destination, char move[]);

void print_board(_piece_type board[8][8]);

//x = 0 to 7
char chess_x_coordinate_to_letter(int x);
//y = 0 to 7
char chess_y_coordinate_to_char(int y);
//letter = 'a' to  'h'
int chess_letter_to_x_coordinate(char letter);
//yChar = 1 to 8
int chess_char_to_y_coordinate(char yChar);
char piece_type_to_char(_piece_type pieceType);
char piece_type_to_color(_piece_type pieceType);
	


void make_move(_coordinates origin, _coordinates destination);

bool is_same_location(_coordinates c1, _coordinates c2);
bool is_init_state();

void init_board();


//void check_board_state();

void piece_down(_coordinates coo);
void piece_up(_coordinates coo);



#endif