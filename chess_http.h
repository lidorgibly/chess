#ifndef _HTTP_H
#define _HTTP_H

#include "chess.h"
 
 
#define WEB_URL "http://127.0.0.1:3000/chess?move="
 
 
void http_send_move(_coordinates origin, _coordinates destination);

void http_send_board(_piece_type board[8][8]);
	

#endif