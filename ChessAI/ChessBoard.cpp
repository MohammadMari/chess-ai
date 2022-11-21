#include "ChessBoard.h"
// transforms the board we have into a 3d array.


// we feed this into tensorflow.
vector<vector<vector<int>>> convert(ChessPiece*** board) {

	vector<vector<vector<int>>> arr;

	// im throwing hands with whoever said we should use C++ for this
	for (int i = 0; i < 14; i++) {
		vector<vector<int>> temp14;
		for (int j = 0; j < 8; j++) {
			vector<int> temp8;
			for (int k = 0; k < 8; k++) {
				temp8.push_back(0);
			}
			temp14.push_back(temp8);
		}
		arr.push_back(temp14);
	}


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int num = board[i][j]->getPieceType() + ((board[i][j]->GetSide() == BLACK ? 1 : 0) * 7); // piece type white += 0, black += 7
			arr[num][i][j] = 1; // piece is in this spot.

			vector<Pos> moves = board[i][j]->PossibleMoves(board, board[i][j]->GetSide()); //get all possible moves

			int possibleMovesForSide = board[i][j]->GetSide() == BLACK ? 12 : 13; //all possible moves will be contained in 12 and 13 index
			for (Pos move : moves) {
				arr[possibleMovesForSide][move.x][move.y] = 1;
			}
		}
	}

	return arr;
}


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


	delete piecePos[0][0];
	delete piecePos[1][0];
	delete piecePos[2][0];
	delete piecePos[3][0];
	delete piecePos[4][0];
	delete piecePos[5][0];
	delete piecePos[6][0];
	delete piecePos[7][0];

	piecePos[0][0] = new Rook(BLACK, Pos(0, 0), NodeLabel(Pos(0,0)));
	piecePos[1][0] = new Knight(BLACK, Pos(1, 0), NodeLabel(Pos(1, 0)));
	piecePos[2][0] = new Bishop(BLACK, Pos(2, 0), NodeLabel(Pos(2, 0)));
	piecePos[3][0] = new Queen(BLACK, Pos(3, 0), NodeLabel(Pos(3, 0)));
	piecePos[4][0] = new King(BLACK, Pos(4, 0), NodeLabel(Pos(4, 0)));
	piecePos[5][0] = new Bishop(BLACK, Pos(5, 0), NodeLabel(Pos(5, 0)));
	piecePos[6][0] = new Knight(BLACK, Pos(6, 0), NodeLabel(Pos(6, 0)));
	piecePos[7][0] = new Rook(BLACK, Pos(7, 0), NodeLabel(Pos(7, 0)));

	for (int i = 0; i < 8; i++) {
		delete piecePos[i][1];
		delete piecePos[i][6];
		piecePos[i][1] = new Pawn(BLACK, Pos(i, 1), NodeLabel(Pos(i, 1)));
		piecePos[i][6] = new Pawn(WHITE, Pos(i, 6), NodeLabel(Pos(i, 6)));
	}


	delete piecePos[0][7];
	delete piecePos[1][7];
	delete piecePos[2][7];
	delete piecePos[3][7];
	delete piecePos[4][7];
	delete piecePos[5][7];
	delete piecePos[6][7];
	delete piecePos[7][7];

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

	//check and checkmate status affects what pieces can be selected.


	//load the output SFML font, if not possible, output error.
	Font font;
	if (!font.loadFromFile("fonts/ShortBaby-Mg2w.ttf")) {
		printf("Error, could not load font\n");
		exit(0);
	}




	//if it is neither a check for black or white.
	if (!getCheckFlagBlack() && !getCheckFlagWhite()) {
		if (selectedPiece) {
			CircleShape pieceOutline;

			for (Pos move : selectedPiece->PossibleMoves(piecePos)) {
				pieceOutline.setFillColor(Color(0, 0, 0, 20));
				pieceOutline.setRadius(37.5);
				pieceOutline.setPosition(Vector2f(move.x * 75, move.y * 75));
				window.draw(pieceOutline);
			}

		}

	}

	//if black is in check, could either be check or checkmate(White Wins).
	if (getCheckFlagBlack()) {

		if (GetcurTurn() != BLACK) {
			this->isCheckMateOnBlack = true;
		}

		//updates container of valid piecees to move with their valid moves when in check state.
		checkHandlerBlack();

		//checks on what to set checkmate status for black side.
		setIsCheckMateOnBlack();

		bool isSelectedPieceValid = false;
		Chess_Piece_Node associatedNode;

		if (selectedPiece) {
			int xCoord = selectedPiece->GetX();
			int yCoord = selectedPiece->GetY();

			for (unsigned int i = 0; i < validPiecesToMoveDuringCheckBlack.size(); i++) {
				if (xCoord == validPiecesToMoveDuringCheckBlack.at(i).piece->GetX() && yCoord == validPiecesToMoveDuringCheckBlack.at(i).piece->GetY()) {
					isSelectedPieceValid = true;
					associatedNode = validPiecesToMoveDuringCheckBlack.at(i);
				}
			}

		}

		//if black is in checkmate.
		if (getIsCheckMateOnBlack()) {
			Text blackCheckMated;
			blackCheckMated.setFont(font);
			blackCheckMated.setFillColor(Color::Red);
			blackCheckMated.setString("Black Is In Checkmate!");
			blackCheckMated.setCharacterSize(40);
			blackCheckMated.setPosition(Vector2f(150, 550));
			window.draw(blackCheckMated);
			return;
		}


		if (isSelectedPieceValid) {
			CircleShape pieceOutline;

			for (Pos move : associatedNode.validMoves) {
				pieceOutline.setFillColor(Color(0, 0, 0, 20));
				pieceOutline.setRadius(37.5);
				pieceOutline.setPosition(Vector2f(move.x * 75, move.y * 75));
				window.draw(pieceOutline);
			}

		}

		Text blackCheck;
		blackCheck.setFont(font);
		blackCheck.setFillColor(Color::Red);
		blackCheck.setString("Black is in check!");
		blackCheck.setCharacterSize(40);
		blackCheck.setPosition(Vector2f(150, 550));
		window.draw(blackCheck);
	}

	//if white is in check, could either be check or checkmate(Black Wins).
	if (getCheckFlagWhite()) {
		
		if (GetcurTurn() != WHITE) {
			this->isCheckMateOnWhite = true;
		}

		//updates container of valid piecees to move with their valid moves when in check state.
		checkHandlerWhite();

		//checks what to set for checkmate status on white.
		setIsCheckMateOnWhite();


		if (getIsCheckMateOnWhite()) {
			Text whiteCheckMated;
			whiteCheckMated.setFont(font);
			whiteCheckMated.setFillColor(Color::Red);
			whiteCheckMated.setString("White Is In Checkmate!");
			whiteCheckMated.setCharacterSize(40);
			whiteCheckMated.setPosition(Vector2f(150, 550));
			window.draw(whiteCheckMated);
			return;
		}


		bool isSelectedPieceValid = false;
		Chess_Piece_Node associatedNode;
		if (selectedPiece) {
			int xCoord = selectedPiece->GetX();
			int yCoord = selectedPiece->GetY();

			for (unsigned int i = 0; i < validPiecesToMoveDuringCheckWhite.size(); i++) {
				if (xCoord == validPiecesToMoveDuringCheckWhite.at(i).piece->GetX() && yCoord == validPiecesToMoveDuringCheckWhite.at(i).piece->GetY()) {
					isSelectedPieceValid = true;
					associatedNode = validPiecesToMoveDuringCheckWhite.at(i);
				}
			}
		}



		if (isSelectedPieceValid) {
			CircleShape pieceOutline;

			for (Pos move : associatedNode.validMoves) {
				pieceOutline.setFillColor(Color(0, 0, 0, 20));
				pieceOutline.setRadius(37.5);
				pieceOutline.setPosition(Vector2f(move.x * 75, move.y * 75));
				window.draw(pieceOutline);
			}

		}


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

	//first check if checkmate state for either white or black, if so then ignore all clicks.
	if (getIsCheckMateOnBlack() || getIsCheckMateOnWhite()) {
		return;
	}


	if ((!getCheckFlagBlack()) && (!getCheckFlagWhite())) {
		// if we have a piece selected
		if (selectedPiece) {
			// find all of its possible moves
			vector<Pos> Moves = selectedPiece->PossibleMoves(piecePos);

			// check the spot we just clicked to see if its in the possible move
			for (Pos pos : Moves) {

				// if it is in the possible move, move your piece over to that spot.
				if (pos.x == x && pos.y == y) {
					delete piecePos[x][y];
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
	else if (getCheckFlagBlack()) {
		Chess_Piece_Node associatedNode;

		if (selectedPiece) {
			bool isValidPieceSelected = false;

			for (unsigned int i = 0; i < validPiecesToMoveDuringCheckBlack.size(); i++) {
					if (selectedPiece->GetX() == validPiecesToMoveDuringCheckBlack.at(i).piece->GetX() && selectedPiece->GetY() == validPiecesToMoveDuringCheckBlack.at(i).piece->GetY()) {
						isValidPieceSelected = true;
						associatedNode = validPiecesToMoveDuringCheckBlack.at(i);
					}
			}
			if (!isValidPieceSelected) {
				selectedPiece = nullptr;
			}
		}
		else if (selectedPiece == nullptr) {
			if (piecePos[x][y]->GetSide() == curTurn) {
				selectedPiece = piecePos[x][y];
			}
			else {
				selectedPiece = nullptr;
			}
		}


		if (selectedPiece) {
			// find all of its possible moves
			vector<Pos> Moves = associatedNode.validMoves;

			// check the spot we just clicked to see if its in the possible move
			for (Pos pos : Moves) {

				// if it is in the possible move, move your piece over to that spot.
				if (pos.x == x && pos.y == y) {
					delete piecePos[x][y];
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


	}

	else if (getCheckFlagWhite()) {
		Chess_Piece_Node associatedNode;

		if (selectedPiece) {
			bool isValidPieceSelected = false;

			for (unsigned int i = 0; i < validPiecesToMoveDuringCheckWhite.size(); i++) {
					if (selectedPiece->GetX() == validPiecesToMoveDuringCheckWhite.at(i).piece->GetX() && selectedPiece->GetY() == validPiecesToMoveDuringCheckWhite.at(i).piece->GetY()) {
						isValidPieceSelected = true;
						associatedNode = validPiecesToMoveDuringCheckWhite.at(i);
					}
			}
			if (!isValidPieceSelected) {
				selectedPiece = nullptr;
			}
		}
		else if (selectedPiece == nullptr) {
			if (piecePos[x][y]->GetSide() == curTurn) {
				selectedPiece = piecePos[x][y];
			}
			else {
				selectedPiece = nullptr;
			}
		}


		if (selectedPiece) {
			// find all of its possible moves
			vector<Pos> Moves = associatedNode.validMoves;

			// check the spot we just clicked to see if its in the possible move
			for (Pos pos : Moves) {

				// if it is in the possible move, move your piece over to that spot.
				if (pos.x == x && pos.y == y) {
					delete piecePos[x][y];
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

void ChessBoard::checkHandlerWhite() {

	//stores all found attack lines of black pieces that are checking the white king.
	vector<Pos> attackLines;

	validPiecesToMoveDuringCheckWhite.clear();


	//at this point, there should be pieces in this container representing black pieces that are checking the white king. If not found, unexpected error has occurred.
	if (blackPiecesChecking.size() == 0) {
		printf("Error. White King is detected to be in check but no black pieces checking the white king were found.\n");
		exit(0);
	}

	//blackPiecesChecking should have container of size > 0, representing pieces involved in attacking the King.
	for (unsigned int i = 0; i < blackPiecesChecking.size(); i++) {
		//condition that determines if selected piece has an attack line (invalid is there just in case, but there should not be an invalid/empty chess piece type in the container to begin with).
		bool hasAttackLine = ((blackPiecesChecking.at(i)->getPieceType() != KING) && (blackPiecesChecking.at(i)->getPieceType() != INVALID) && (blackPiecesChecking.at(i)->getPieceType() != PAWN) && (blackPiecesChecking.at(i)->getPieceType() != KNIGHT));
		//determine the attack lines for all of the black pieces participating in attacking the white king (**ONLY APPLICABLE FOR QUEENS, BISHOPS, AND ROOKS).
		if (hasAttackLine) {
			//if the attackLines container is of size zero, set container equal to found attack line.
			if (attackLines.size() == 0) {
				attackLines = blackPiecesChecking.at(i)->AttackingLine(piecePos, blackPiecesChecking.at(i)->GetSide());
			}
			//otherwise, attackLines container of non-zero size (more than 1 piece attacking), append newly found attack line to others previously found.
			else {
				vector<Pos> newlyFoundAttackLine = blackPiecesChecking.at(i)->AttackingLine(piecePos, blackPiecesChecking.at(i)->GetSide());
				attackLines.insert(attackLines.end(), newlyFoundAttackLine.begin(), newlyFoundAttackLine.end());
			}

		}
	}


	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			ChessPiece* currPiece = piecePos[i][j];
			//if it is a non-empty chess piece that is white.
			if (currPiece->GetSide() == WHITE) {
				//stores all the possible moves that the current piece can make under the current check state.
				vector<Pos> moves;
				//calls possible moves and gets all possible moves assuming no check state. Since we are in check, very high chance that this needs to be filtered down.
				moves = currPiece->PossibleMoves(piecePos, currPiece->GetSide());

				//lets make another vector that will become the size of the vector of bool values, the indexes are a direct mapping to the elements in the move vector and the bool value represents whether if specific move pos is valid or not.
				vector<bool> isMoveElementValid;

				//initially, assume that all elements are invalid moves until proven otherwise.
				for (unsigned int k = 0; k < moves.size(); k++) {
					isMoveElementValid.push_back(false);
				}

				//moves get filtered out differently for kings, so make a distinction between the current piece type.
				//current piece is not a white king.
				if (currPiece->getPieceType() != KING) {

					//now iterate through the moves container and figure out which moves need to be filtered out individually.
					for (unsigned int k = 0; k < moves.size(); k++) {
						/* CRITERIA TO CHECK FOR VALID MOVE.
							1.	Valid move if the position also happens to be a position that is a part of an attacking line (in chess, this represents a piece blocking an attack to its respective king from an enemy piece)
						*/
						//represents current move to check if valid.
						Pos currMove = moves.at(k);
						//First checking criteria number 1.

						//now we are iterating through attackLines to see if we can find a corresponding equivalent position in attackLines 
						//(there could be more than 1 of the same position in attackLines so each element is not guaranteed to be unique).
						for (unsigned int l = 0; l < attackLines.size(); l++) {
							//represents a position of an attack line.
							Pos currAttackLineLocation = attackLines.at(l);

							//found a corresponding attack line location so set this to true so that this move does not get filtered out (valid move).
							if ((currMove.x == currAttackLineLocation.x) && (currMove.y == currAttackLineLocation.y)) {
								isMoveElementValid.at(k) = true;
							}
						}


						//there must only be one black piece checking the white king for a check to be able to be "Uplifted.".
						if (blackPiecesChecking.size() == 1) {
							//if this move represents a move where the checking piece can get killed, mark this also as a valid move. The black piece will be at the first index so no need to determine the index.
							if ((currMove.x == blackPiecesChecking.at(0)->GetX()) && (currMove.y == blackPiecesChecking.at(0)->GetY())) {
								isMoveElementValid.at(k) = true;
							}
						}
					}

					vector<Pos> validMovements;

					//if after going through both criteria, certain move positions are still considered invalid, this move must be filtered out of the moves vector as a possible move.
					for (unsigned int k = 0; k < moves.size(); k++) {
						//if the move is considered an invalid move for the current piece.
						if (isMoveElementValid.at(k)) {
							//remove or filter out the current move position at k since it is an invalid move.
							validMovements.push_back(moves.at(k));
						}
					}

					//if the piece actually has valid moves to make, then it is worth adding as a valid piece to move under the current check state.
					if (validMovements.size() != 0) {
						Chess_Piece_Node newNode;
						newNode.piece = currPiece;
						newNode.validMoves = validMovements;
						validPiecesToMoveDuringCheckWhite.push_back(newNode);
					}
				}


				//current piece is a white king.
				else{
					for (unsigned int k = 0; k < moves.size(); k++) {
						/* CRITERIA TO CHECK FOR VALID MOVES FOR KING 
							1. King's move position must not be a position on an attack line (line where enemy pieces are attacking the king).
							2. Can kill a piece doing a check, if after killing piece, not on an attack line.
						*/
						
						isMoveElementValid.at(k) = true;

						//represents current move to check if valid.
						Pos currMove = moves.at(k);
						//First checking criteria number 1.

						//now we are iterating through attackLines to see if we can find a corresponding equivalent position in attackLines 
						//(there could be more than 1 of the same position in attackLines so each element is not guaranteed to be unique).
						for (unsigned int l = 0; l < attackLines.size(); l++) {
						//	//represents a position of an attack line.
							Pos currAttackLineLocation = attackLines.at(l);



						//	//if it is not the same as an attackLine position, valid move (so the moment it finds that an attackLine is the same as the current move, current move is not valid).
							if ((currMove.x == currAttackLineLocation.x) && (currMove.y == currAttackLineLocation.y)) {
								isMoveElementValid.at(k) = false;
							}
						}
						//now checking second criteria.
							
						Pos position;
						position.x = piecePos[i][j]->GetX();
						position.y = piecePos[i][j]->GetY();


						ChessPiece* nodeToReplace = piecePos[currMove.x][currMove.y];

						if (nodeToReplace->GetSide() != BLACK) {
							piecePos[currMove.x][currMove.y] = piecePos[i][j];
							piecePos[currMove.x][currMove.y]->SetX(currMove.x);
							piecePos[currMove.x][currMove.y]->SetY(currMove.x);
							piecePos[i][j] = nodeToReplace;
							nodeToReplace->SetX(position.x);
							nodeToReplace->SetY(position.y);

							determineIfAnyCheck();

							if (getCheckFlagBlack()) {
								isMoveElementValid.at(k) = false;
							}

							nodeToReplace = piecePos[i][j];
							piecePos[i][j] = piecePos[currMove.x][currMove.y];
							piecePos[i][j]->SetX(position.x);
							piecePos[i][j]->SetY(position.y);
							piecePos[currMove.x][currMove.y] = nodeToReplace;
							piecePos[currMove.x][currMove.y]->SetX(currMove.x);
							piecePos[currMove.x][currMove.y]->SetY(currMove.y);

							determineIfAnyCheck();
						}
						else {
							piecePos[currMove.x][currMove.y] = piecePos[i][j];
							piecePos[currMove.x][currMove.y]->SetX(currMove.x);
							piecePos[currMove.x][currMove.y]->SetY(currMove.x);

							Pos emptyPos(position.x, position.y);

							Empty* newEmpty = new Empty(emptyPos, NodeLabel(emptyPos));

							piecePos[i][j] = newEmpty;

							determineIfAnyCheck();

							if (getCheckFlagBlack()) {
								isMoveElementValid.at(k) = false;
							}

							delete newEmpty;

							piecePos[i][j] = piecePos[currMove.x][currMove.y];
							piecePos[i][j]->SetX(position.x);
							piecePos[i][j]->SetY(position.y);
							piecePos[currMove.x][currMove.y] = nodeToReplace;
							piecePos[currMove.x][currMove.y]->SetX(currMove.x);
							piecePos[currMove.x][currMove.y]->SetY(currMove.y);

							determineIfAnyCheck();
						}

					}


					vector<Pos> validMovements;

					//if after going through both criteria, certain move positions are still considered invalid, this move must be filtered out of the moves vector as a possible move.
					for (unsigned int k = 0; k < moves.size(); k++) {
						//if the move is considered an invalid move for the current piece.
						if (isMoveElementValid.at(k)) {
							//remove or filter out the current move position at k since it is an invalid move.
							validMovements.push_back(moves.at(k));
						}
					}

					//if the piece actually has valid moves to make, then it is worth adding as a valid piece to move under the current check state.
					if (validMovements.size() != 0) {
						Chess_Piece_Node newNode;
						newNode.piece = currPiece;
						newNode.validMoves = validMovements;
						validPiecesToMoveDuringCheckWhite.push_back(newNode);
					}
				}

	
			}
		
		}
	}

	return;
}

void ChessBoard::checkHandlerBlack() {
	//stores all found attack lines of white pieces that are checking the black king.
	vector<Pos> attackLines;

	validPiecesToMoveDuringCheckBlack.clear();

	//at this point, there should be pieces in this container representing white pieces that are checking the black king. If not found, unexpected error has occurred.
	if (whitePiecesChecking.size() == 0) {
		printf("Error. Black King is detected to be in check but no white pieces checking the black king were found.\n");
		exit(0);
	}

	//whitePiecesChecking should have container of size > 0, representing pieces involved in attacking the King.
	for (unsigned int i = 0; i < whitePiecesChecking.size(); i++) {
		//condition that determines if selected piece has an attack line (invalid is there just in case, but there should not be an invalid/empty chess piece type in the container to begin with).
		bool hasAttackLine = ((whitePiecesChecking.at(i)->getPieceType() != KING) && (whitePiecesChecking.at(i)->getPieceType() != INVALID) && (whitePiecesChecking.at(i)->getPieceType() != PAWN) && (whitePiecesChecking.at(i)->getPieceType() != KNIGHT));
		//determine the attack lines for all of the white pieces participating in attacking the black king (**ONLY APPLICABLE FOR QUEENS, BISHOPS, AND ROOKS).
		if (hasAttackLine) {
			//if the attackLines container is of size zero, set container equal to found attack line.
			if (attackLines.size() == 0) {
				attackLines = whitePiecesChecking.at(i)->AttackingLine(piecePos, whitePiecesChecking.at(i)->GetSide());
			}
			//otherwise, attackLines container of non-zero size (more than 1 piece attacking), append newly found attack line to others previously found.
			else {
				vector<Pos> newlyFoundAttackLine = whitePiecesChecking.at(i)->AttackingLine(piecePos, whitePiecesChecking.at(i)->GetSide());
				attackLines.insert(attackLines.end(), newlyFoundAttackLine.begin(), newlyFoundAttackLine.end());
			}

		}
	}

	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			ChessPiece* currPiece = piecePos[i][j];
			//if it is a non-empty chess piece that is white.
			if (currPiece->GetSide() == BLACK) {
				//stores all the possible moves that the current piece can make under the current check state.
				vector<Pos> moves;
				//calls possible moves and gets all possible moves assuming no check state. Since we are in check, very high chance that this needs to be filtered down.
				moves = currPiece->PossibleMoves(piecePos, currPiece->GetSide());

				//lets make another vector that will become the size of the vector of bool values, the indexes are a direct mapping to the elements in the move vector and the bool value represents whether if specific move pos is valid or not.
				vector<bool> isMoveElementValid;

				//initially, assume that all elements are invalid moves until proven otherwise.
				for (unsigned int k = 0; k < moves.size(); k++) {
					isMoveElementValid.push_back(false);
				}

				//moves get filtered out differently for kings, so make a distinction between the current piece type.
				//current piece is not a black king.
				if (currPiece->getPieceType() != KING) {

					//now iterate through the moves container and figure out which moves need to be filtered out individually.
					for (unsigned int k = 0; k < moves.size(); k++) {
						/* CRITERIA TO CHECK FOR VALID MOVE.
							1.	Valid move if the position also happens to be a position that is a part of an attacking line (in chess, this represents a piece blocking an attack to its respective king from an enemy piece)
						*/
						//represents current move to check if valid.
						Pos currMove = moves.at(k);
						//First checking criteria number 1.

						//now we are iterating through attackLines to see if we can find a corresponding equivalent position in attackLines 
						//(there could be more than 1 of the same position in attackLines so each element is not guaranteed to be unique).
						for (unsigned int l = 0; l < attackLines.size(); l++) {
							//represents a position of an attack line.
							Pos currAttackLineLocation = attackLines.at(l);

							//found a corresponding attack line location so set this to true so that this move does not get filtered out (valid move).
							if ((currMove.x == currAttackLineLocation.x) && (currMove.y == currAttackLineLocation.y)) {
								isMoveElementValid.at(k) = true;
							}
						}

						////there must only be one black piece checking the white king for a check to be able to be "Uplifted.".
						if (whitePiecesChecking.size() == 1) {
							//if this move represents a move where the checking piece can get killed, mark this also as a valid move. The black piece will be at the first index so no need to determine the index.
							if ((currMove.x == whitePiecesChecking.at(0)->GetX()) && (currMove.y == whitePiecesChecking.at(0)->GetY())) {
								isMoveElementValid.at(k) = true;
							}
						}
					}
					vector<Pos> validMovements;

					//if after going through both criteria, certain move positions are still considered invalid, this move must be filtered out of the moves vector as a possible move.
					for (unsigned int k = 0; k < moves.size(); k++) {
						//if the move is considered an invalid move for the current piece.
						if (isMoveElementValid.at(k)) {
							//remove or filter out the current move position at k since it is an invalid move.
							validMovements.push_back(moves.at(k));
						}
					}

					//if the piece actually has valid moves to make, then it is worth adding as a valid piece to move under the current check state.
					if (validMovements.size() != 0) {
						Chess_Piece_Node newNode;
						newNode.piece = currPiece;
						newNode.validMoves = validMovements;
						validPiecesToMoveDuringCheckBlack.push_back(newNode);
					}
				}


				//current piece is a black king.
				else {
					for (unsigned int k = 0; k < moves.size(); k++) {
						/* CRITERIA TO CHECK FOR VALID MOVES FOR KING
							1. King's move position must not be a position on an attack line (line where enemy pieces are attacking the king).
							2. Can kill a piece doing a check, if after killing piece, not on an attack line.
						*/

						isMoveElementValid.at(k) = true;

						//represents current move to check if valid.
						Pos currMove = moves.at(k);
						//First checking criteria number 1.

						//now we are iterating through attackLines to see if we can find a corresponding equivalent position in attackLines 
						//(there could be more than 1 of the same position in attackLines so each element is not guaranteed to be unique).
						for (unsigned int l = 0; l < attackLines.size(); l++) {
							//	//represents a position of an attack line.
							Pos currAttackLineLocation = attackLines.at(l);



							//	//if it is not the same as an attackLine position, valid move (so the moment it finds that an attackLine is the same as the current move, current move is not valid).
							if ((currMove.x == currAttackLineLocation.x) && (currMove.y == currAttackLineLocation.y)) {
								isMoveElementValid.at(k) = false;
							}
						}

							Pos position;
							position.x = piecePos[i][j]->GetX();
							position.y = piecePos[i][j]->GetY();


							ChessPiece* nodeToReplace = piecePos[currMove.x][currMove.y];
							
							if (nodeToReplace->GetSide() != WHITE) {
								piecePos[currMove.x][currMove.y] = piecePos[i][j];
								piecePos[currMove.x][currMove.y]->SetX(currMove.x);
								piecePos[currMove.x][currMove.y]->SetY(currMove.x);
								piecePos[i][j] = nodeToReplace;
								nodeToReplace->SetX(position.x);
								nodeToReplace->SetY(position.y);

								determineIfAnyCheck();

								if (getCheckFlagBlack()) {
									isMoveElementValid.at(k) = false;
								}

								nodeToReplace = piecePos[i][j];
								piecePos[i][j] = piecePos[currMove.x][currMove.y];
								piecePos[i][j]->SetX(position.x);
								piecePos[i][j]->SetY(position.y);
								piecePos[currMove.x][currMove.y] = nodeToReplace;
								piecePos[currMove.x][currMove.y]->SetX(currMove.x);
								piecePos[currMove.x][currMove.y]->SetY(currMove.y);

								determineIfAnyCheck();
							}
							else{
								piecePos[currMove.x][currMove.y] = piecePos[i][j];
								piecePos[currMove.x][currMove.y]->SetX(currMove.x);
								piecePos[currMove.x][currMove.y]->SetY(currMove.x);
								
								Pos emptyPos(position.x, position.y);

								Empty* newEmpty = new Empty(emptyPos, NodeLabel(emptyPos));

								piecePos[i][j] = newEmpty;

								determineIfAnyCheck();

								if (getCheckFlagBlack()) {
									isMoveElementValid.at(k) = false;
								}

								delete newEmpty;

								piecePos[i][j] = piecePos[currMove.x][currMove.y];
								piecePos[i][j]->SetX(position.x);
								piecePos[i][j]->SetY(position.y);
								piecePos[currMove.x][currMove.y] = nodeToReplace;
								piecePos[currMove.x][currMove.y]->SetX(currMove.x);
								piecePos[currMove.x][currMove.y]->SetY(currMove.y);

								determineIfAnyCheck();
							}



					}
					vector<Pos> validMovements;

					//if after going through both criteria, certain move positions are still considered invalid, this move must be filtered out of the moves vector as a possible move.
					for (unsigned int k = 0; k < moves.size(); k++) {
						//if the move is considered an invalid move for the current piece.
						if (isMoveElementValid.at(k)) {
							//remove or filter out the current move position at k since it is an invalid move.
							validMovements.push_back(moves.at(k));
						}
					}

					//if the piece actually has valid moves to make, then it is worth adding as a valid piece to move under the current check state.
					if (validMovements.size() != 0) {
						Chess_Piece_Node newNode;
						newNode.piece = currPiece;
						newNode.validMoves = validMovements;
						validPiecesToMoveDuringCheckBlack.push_back(newNode);
					}
				}


			}

		}
	}


	return;
}


void ChessBoard::setIsCheckMateOnBlack() {
	if (checkFlagBlack) {
		if (validPiecesToMoveDuringCheckBlack.size() == 0) {
			this->isCheckMateOnBlack = true;
		}
	}
}

void ChessBoard::setIsCheckMateOnWhite() {
	if (checkFlagWhite) {
		if (validPiecesToMoveDuringCheckWhite.size() == 0) {
			this->isCheckMateOnWhite = true;
		}
	}
}

bool ChessBoard::getIsCheckMateOnWhite() {
	return this->isCheckMateOnWhite;
}

bool ChessBoard::getIsCheckMateOnBlack() {
	return this->isCheckMateOnBlack;
}
