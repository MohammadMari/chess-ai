#include "ChessBoard.h"


// okay maybe I should have put this in chess piece and fed it the pos that we already have c:
// its a later problem c:
string NodeLabel(Pos pos) {
	string posX; posX += ('a' + pos.x);
	string posY; posY += ('1' + pos.y);
	return posX + posY;
}

bool ChessBoard::getCheckFlagWhite() {
	return this->checkFlagWhite;
}
bool ChessBoard::getCheckFlagBlack() {
	return this->checkFlagBlack;
}

void ChessBoard::setCheckFlagWhite(bool valueToSet) {
	this->checkFlagWhite = valueToSet;
	return;
}
void ChessBoard::setCheckFlagBlack(bool valueToSet) {
	this->checkFlagBlack = valueToSet;
	return;
}

ChessBoard::ChessBoard()
{
	for (int i = 0; i < 8; i++) {
		piecePos[i] = new ChessPiece*[8];
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			piecePos[i][j] = new Empty(Pos(i, j), NodeLabel(Pos(i, j)));
		}
	}

	free(piecePos[0][0]);
	free(piecePos[1][0]);
	free(piecePos[2][0]);
	free(piecePos[3][0]);
	free(piecePos[4][0]);
	free(piecePos[5][0]);
	free(piecePos[6][0]);
	free(piecePos[7][0]);

	piecePos[0][0] = new Rook(BLACK, Pos(0, 0), NodeLabel(Pos(0,0)));
	piecePos[1][0] = new Knight(BLACK, Pos(1, 0), NodeLabel(Pos(1, 0)));
	piecePos[2][0] = new Bishop(BLACK, Pos(2, 0), NodeLabel(Pos(2, 0)));
	piecePos[3][0] = new Queen(BLACK, Pos(3, 0), NodeLabel(Pos(3, 0)));
	piecePos[4][0] = new King(BLACK, Pos(4, 0), NodeLabel(Pos(4, 0)));
	piecePos[5][0] = new Bishop(BLACK, Pos(5, 0), NodeLabel(Pos(5, 0)));
	piecePos[6][0] = new Knight(BLACK, Pos(6, 0), NodeLabel(Pos(6, 0)));
	piecePos[7][0] = new Rook(BLACK, Pos(7, 0), NodeLabel(Pos(7, 0)));

	for (int i = 0; i < 8; i++) {
		free(piecePos[i][1]);
		free(piecePos[i][6]);
		piecePos[i][1] = new Pawn(BLACK, Pos(i, 1), NodeLabel(Pos(i, 1)));
		piecePos[i][6] = new Pawn(WHITE, Pos(i, 6), NodeLabel(Pos(i, 6)));
	}


	free(piecePos[0][7]);
	free(piecePos[1][7]);
	free(piecePos[2][7]);
	free(piecePos[3][7]);
	free(piecePos[4][7]);
	free(piecePos[5][7]);
	free(piecePos[6][7]);
	free(piecePos[7][7]);

	piecePos[0][7] = new Rook(WHITE, Pos(0, 7), NodeLabel(Pos(0, 7)));
	piecePos[1][7] = new Knight(WHITE, Pos(1, 7), NodeLabel(Pos(1, 7)));
	piecePos[2][7] = new Bishop(WHITE, Pos(2, 7), NodeLabel(Pos(2, 7)));
	piecePos[3][7] = new Queen(WHITE, Pos(3, 7), NodeLabel(Pos(3, 7)));
	piecePos[4][7] = new King(WHITE, Pos(4, 7), NodeLabel(Pos(4, 7)));
	piecePos[5][7] = new Bishop(WHITE, Pos(5, 7), NodeLabel(Pos(5, 7)));
	piecePos[6][7] = new Knight(WHITE, Pos(6, 7), NodeLabel(Pos(6, 7)));
	piecePos[7][7] = new Rook(WHITE, Pos(7, 7), NodeLabel(Pos(7, 7)));
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

	//updates the current status of check for white or black after each move is made. 
	determineIfAnyCheck();


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

	//load the output SFML font, if not possible, output error.
	Font font;
	if (!font.loadFromFile("fonts/ShortBaby-Mg2w.ttf")) {
		printf("Error, could not load font\n");
		exit(0);
	}

	//if black is in check, display text output to SFML Window.
	if (getCheckFlagBlack()) {
		Text blackCheck;	
		blackCheck.setFont(font);
		blackCheck.setFillColor(Color::Red);
		blackCheck.setString("Black is in check!");
		blackCheck.setCharacterSize(40);
		blackCheck.setPosition(Vector2f(150, 550));
		window.draw(blackCheck);
	}

	//if white is in check, display text output to SFML Window.
	if (getCheckFlagWhite()) {
		Text whiteCheck;
		whiteCheck.setFont(font);
		whiteCheck.setFillColor(Color::Red);
		whiteCheck.setString("White is in check!");
		whiteCheck.setCharacterSize(40);
		whiteCheck.setPosition(Vector2f(150, 550));
		window.draw(whiteCheck);
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
				selectedPiece->isMoved = true;


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


void ChessBoard::determineIfAnyCheck() {

	//check if any moves from any chess pieces result in check, if so, update respective check status for piece.
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			if (piecePos[i][j]->getPieceType() != INVALID) {
				piecePos[i][j]->PossibleMoves(piecePos);
			}
		}
	}

	//clear old results.
	whitePiecesChecking.clear();
	blackPiecesChecking.clear();

	//finds all pieces participating in a check (white or black pieces)
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			//if the current piece found is doing a check on their respective enemy king.
			if (piecePos[i][j]->getCheckStatusForPiece()) {
				//if the current piece involved in a check is white, black king is in check.
				if (piecePos[i][j]->GetSide() == WHITE) {
					whitePiecesChecking.push_back(piecePos[i][j]);
				}
				//if the current piece involved in a check is black, white king is in check instead.
				if (piecePos[i][j]->GetSide() == BLACK) {
					blackPiecesChecking.push_back(piecePos[i][j]);
				}

			}
		}
	}

	//if black king is in check, set check flag for black. This is true when there are chess pieces in the whitePiecesChecking container.
	if (whitePiecesChecking.size()) {
		setCheckFlagBlack(true);
	}
	//else, no check on black king so set check flag to false if not already.
	else {
		setCheckFlagBlack(false);
	}

	//if white king is in check, set check flag for white. This is true when there are chess pieces in the blackPiecesChecking container.
	if (blackPiecesChecking.size()) {
		setCheckFlagWhite(true);
	}
	//otherwise, no check on white king so set check flag to false if not already.
	else {
		setCheckFlagWhite(false);
	}

	//reset individual check flags for all pieces (will be re-evaluated at the start of this function again).
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			if (piecePos[i][j]->getPieceType() != INVALID) {
				piecePos[i][j]->setCheckStatusForPiece(false);
			}
		}
	}


	return;
}
