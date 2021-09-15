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





bool is_same_location(_coordinates c1, _coordinates c2);

bool is_init_state();
void init_board();


void check_board_state();




#endif