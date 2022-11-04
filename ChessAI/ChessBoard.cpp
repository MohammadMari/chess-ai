#include "ChessBoard.h"


// okay maybe I should have put this in chess piece and fed it the pos that we already have c:
// its a later problem c:
string NodeLabel(Pos pos) {
	string posX; posX += ('a' + pos.x);
	string posY; posY += ('1' + pos.y);
	return posX + posY;
}

ChessBoard::ChessBoard()
{
	for (int i = 0; i < 8; i++) {
		piecePos[i] = new ChessPiece*[8];
	}

	piecePos[0][0] = new Rook(BLACK, Pos(0, 0), NodeLabel(Pos(0,0)));
	piecePos[1][0] = new Knight(BLACK, Pos(1, 0), NodeLabel(Pos(1, 0)));
	piecePos[2][0] = new Bishop(BLACK, Pos(2, 0), NodeLabel(Pos(2, 0)));
	piecePos[3][0] = new Queen(BLACK, Pos(3, 0), NodeLabel(Pos(3, 0)));
	piecePos[4][0] = new King(BLACK, Pos(4, 0), NodeLabel(Pos(4, 0)));
	piecePos[5][0] = new Bishop(BLACK, Pos(5, 0), NodeLabel(Pos(5, 0)));
	piecePos[6][0] = new Knight(BLACK, Pos(6, 0), NodeLabel(Pos(6, 0)));
	piecePos[7][0] = new Rook(BLACK, Pos(7, 0), NodeLabel(Pos(7, 0)));

	for (int i = 0; i < 8; i++) {
		piecePos[i][1] = new Pawn(BLACK, Pos(i, 1), NodeLabel(Pos(i, 1)));
		piecePos[i][6] = new Pawn(WHITE, Pos(i, 6), NodeLabel(Pos(i, 6)));
	}
	
	piecePos[0][7] = new Rook(WHITE, Pos(0, 7), NodeLabel(Pos(0, 7)));
	piecePos[1][7] = new Knight(WHITE, Pos(1, 7), NodeLabel(Pos(1, 7)));
	piecePos[2][7] = new Bishop(WHITE, Pos(2, 7), NodeLabel(Pos(2, 7)));
	piecePos[3][7] = new Queen(WHITE, Pos(3, 7), NodeLabel(Pos(3, 7)));
	piecePos[4][7] = new King(WHITE, Pos(4, 7), NodeLabel(Pos(4, 7)));
	piecePos[5][7] = new Bishop(WHITE, Pos(5, 7), NodeLabel(Pos(5, 7)));
	piecePos[6][7] = new Knight(WHITE, Pos(6, 7), NodeLabel(Pos(6, 7)));
	piecePos[7][7] = new Rook(WHITE, Pos(7, 7), NodeLabel(Pos(7, 7)));

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (piecePos[i][j] == nullptr) {
				piecePos[i][j] = new Empty(Pos(i,j), NodeLabel(Pos(i, j)));
			}
		}
	}
}


SIDE ChessBoard::GetcurTurn()
{
	return curTurn;
}

SIDE ChessBoard::SwapCurTurn()
{
	printf("switch\n");
	if (curTurn == NONE) {
		return WHITE;
	}
	else if (curTurn == WHITE) {
		return BLACK;
		
	} 
	else if (curTurn == BLACK) {
		return WHITE;
	}
}

void ChessBoard::DisplayBoard(RenderWindow &window)
{
	RectangleShape boardSquare;
	Color squareColor;

	// draw board and pieces
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {		
			squareColor = (i + j) % 2 == 0 ? Color(238,238,213) : Color(125,148,93);

			// set rectangle properties
			boardSquare.setSize(Vector2f(75, 75));
			boardSquare.setPosition(Vector2f(i * 75, j * 75));
			boardSquare.setFillColor(squareColor);

			// add rectangle to draw list
			window.draw(boardSquare);



			//draw chess pieces
			if (piecePos[i][j]->GetSide() != NONE) {
				Sprite piecePic;
				Texture pieceText = piecePos[i][j]->GetTexture();
				piecePic.setTexture(pieceText);
				piecePic.setScale(Vector2f(1,1));
				piecePic.setPosition(Vector2f((i * 75) + 15, (j * 75) + 10));
				window.draw(piecePic);
			}
		}
	}
	
	if (selectedPiece) {
		CircleShape pieceOutline;

		for (Pos move : selectedPiece->PossibleMoves(piecePos)) {
			pieceOutline.setFillColor(Color(0,0,0,20));
			pieceOutline.setRadius(37.5);
			pieceOutline.setPosition(Vector2f(move.x * 75, move.y * 75));
			window.draw(pieceOutline);
		}
		
	}
}

void ChessBoard::ProcessClickEvent(int x, int y)
{
	x /= 75;
	y /= 75;

	printf("Curturn: %d\n", curTurn);

	// if we have a piece selected
	if (selectedPiece) {
		// find all of its possible moves
		vector<Pos> Moves = selectedPiece->PossibleMoves(piecePos);
		
		// check the spot we just clicked to see if its in the possible move
		for (Pos pos : Moves) {

			// if it is in the possible move, move your piece over to that spot.
			if (pos.x == x && pos.y == y) {
				free(piecePos[x][y]); 
				piecePos[x][y] = piecePos[selectedPiece->GetX()][selectedPiece->GetY()];
				piecePos[selectedPiece->GetX()][selectedPiece->GetY()] = new Empty(Pos(selectedPiece->GetX(), selectedPiece->GetY()), NodeLabel(Pos(selectedPiece->GetX(), selectedPiece->GetY())));
				
				// update the cords in the piece itself
				selectedPiece->SetX(x); // set flag to moved in pawn
				selectedPiece->SetY(y);
				selectedPiece = nullptr;
				curTurn = SwapCurTurn();
				return;
			}
		}
	}

	if (piecePos[x][y]->GetSide() == curTurn) {
		selectedPiece = piecePos[x][y];
	} 
	else {
		selectedPiece = nullptr;
	}
}
