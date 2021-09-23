#ifndef _HTTP_H
#define _HTTP_H


#include "chess.h"
 
void http_send_move(char move[]);

void http_send_board(_piece_type board[8][8]);
	
char piece_type_to_char(_piece_type pieceType);
char piece_type_to_color(_piece_type pieceType);
	
#endif