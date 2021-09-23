#include <stdio.h>
#include "curl.h"
#include "chess.h"

void coordinates_to_chess_move(_coordinates origin, _coordinates destination, char move[]);
void board_to_string(_piece_type board[8][8], char* stringBoard);


char stringBoard[3000];

//stringBoard must be 65 chars- last one will be null
void board_to_string(_piece_type board[8][8], char* stringBoard){

	char str[50];
	char pieceTypeName;
	char pieceColor;
	_piece_type pieceType;
	stringBoard[0] = 0;
	strcat(stringBoard, "{\"board\":[");
	for (int y=7;y>=0;y--){
		strcat(stringBoard, "[");
		for (int x=0;x<8;x++){	
			pieceType = board[x][y];
			if (pieceType == None){
				sprintf(str,"null");
				strcat(stringBoard, str);
			}else{				
				pieceTypeName = piece_type_to_char(pieceType);
				pieceColor = piece_type_to_color(pieceType);
				sprintf(str,"{type: '%c', color: '%c'}", pieceTypeName, pieceColor);
				strcat(stringBoard, str);				
			}			
			if (x!=7)
				strcat(stringBoard, ",");
		}		
		if (y!=0)
			strcat(stringBoard, "],");
		else
			strcat(stringBoard, "]");
	}
	strcat(stringBoard, "]}");
}	
 
char piece_type_to_char(_piece_type pieceType){
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
		return 0;
}

char piece_type_to_color(_piece_type pieceType){
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
		return 0;


	

}


void http_get(char* url)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
}


void http_post(char* url, char * postfields){
	
	CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
	

    /* Check for errors */
    if(res != CURLE_OK){

		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
			  
	}
 
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
	
	
}



/*
void http_send_move(_coordinates origin, _coordinates destination){
	
	
	char move[6];
	
	

	sprintf(move,"%c%c-%c%c", chessXCoordinationToLetter(origin.x), chessYCoordinationToChar(origin.y), chessXCoordinationToLetter(destination.x), chessYCoordinationToChar(destination.y));
	
	char url[50] = "http://127.0.0.1:3000/chess?move=";
	strcat(url, move);
	printf("sending move: %s by http\n", move);
	
	http_get(url);
	
	
	
	
	
}*/




void http_send_move(char move[]){
	
	
	
	char url[50] = "http://127.0.0.1:3000/chess?move=";
	
	strcat(url, move);
	printf("sending move: %s by http\n", move);
	
	http_get(url);
	
	
	
	
	
}





void http_send_board(_piece_type board[8][8]){

	board_to_string(board, stringBoard);
	printf("sending string board : \n%s \n",stringBoard);
	printf("string board length: %d\n",strlen(stringBoard));

	http_post("http://127.0.0.1:3000/chess", stringBoard);
  

}