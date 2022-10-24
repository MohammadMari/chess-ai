#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	piecePos[0][0] = Rook(BLACK);
	piecePos[1][0] = Knight(BLACK);
	piecePos[2][0] = Bishop(BLACK);
	piecePos[3][0] = Queen(BLACK);
	piecePos[4][0] = King(BLACK);
	piecePos[5][0] = Bishop(BLACK);
	piecePos[6][0] = Knight(BLACK);
	piecePos[7][0] = Rook(BLACK);

	for (int i = 0; i < 8; i++) {
		piecePos[i][1] = Pawn(BLACK);
		piecePos[i][6] = Pawn(WHITE);
	}
	
	piecePos[0][7] = Rook(WHITE);
	piecePos[1][7] = Knight(WHITE);
	piecePos[2][7] = Bishop(WHITE);
	piecePos[3][7] = Queen(WHITE);
	piecePos[4][7] = King(WHITE);
	piecePos[5][7] = Bishop(WHITE);
	piecePos[6][7] = Knight(WHITE);
	piecePos[7][7] = Rook(WHITE);
}


SIDE ChessBoard::GetcurTurn()
{
	return curTurn;
}

void ChessBoard::SwapcurTurn()
{
	if (curTurn == NONE) {
		curTurn = WHITE;
	}
	else if (curTurn == WHITE) {
		curTurn == BLACK;
	} 
	else if (curTurn == BLACK) {
		curTurn = WHITE;
	}
}

void ChessBoard::DisplayBoard(RenderWindow &window)
{
	RectangleShape boardSquare;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {		
			Color squareColor = (i + j) % 2 == 0 ? Color(238,238,213) : Color(125,148,93);

			// set rectangle properties
			boardSquare.setSize(Vector2f(75, 75));
			boardSquare.setPosition(Vector2f(i * 75, j * 75));
			boardSquare.setFillColor(squareColor);

			// add rectangle to draw list
			window.draw(boardSquare);

			//draw chess pieces
			if (piecePos[i][j].GetSide() != NONE) {
				Sprite piecePic;
				Texture pieceText = piecePos[i][j].GetTexture();
				piecePic.setTexture(pieceText);
				piecePic.setScale(Vector2f(1,1));
				piecePic.setPosition(Vector2f((i * 75) + 15, (j * 75) + 10));
				window.draw(piecePic);
			}
		}
	}
}