#include "ChessPiece.h"
#include <assert.h>


ChessPiece::ChessPiece()
{
	pieceSide = NONE;
}

ChessPiece::ChessPiece(SIDE side) {
	pieceSide = side;
}

SIDE ChessPiece::GetSide()
{
	return pieceSide;
}

void ChessPiece::SetSide(SIDE side)
{
	pieceSide = side;
}

Texture ChessPiece::GetTexture()
{
	return texture;
}

int ChessPiece::GetX()
{
	return pos.x;
}

int ChessPiece::GetY()
{
	return pos.y;
}

void ChessPiece::SetX(int x)
{
	pos.x = x;
}

void ChessPiece::SetY(int y)
{
	pos.y = y;
}

PIECE_TYPE ChessPiece::getPieceType() {
	return this->pieceName;
}


bool ChessPiece::getCheckStatusForPiece() {
	return this->isPiecePartCheck;
}
void ChessPiece::setCheckStatusForPiece(bool valueToSet) {
	this->isPiecePartCheck = valueToSet;
	return;
}

// Rook
Rook::Rook(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
	this->pieceName = ROOK;

	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/rookw.png")) {
			printf("rookw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/rookb.png")) {
			printf("rookb error\n");
			exit(0);
		}
	}
	else {
		printf("rook error\n");
		exit(0);
	}

	this->pos = pos;
}



// is the move in bounds of the chess board?
bool inBounds(int num) {
	if (num < 0 || num > 7) {
		return false;
	}

	return true;
}

// Max move: maximum amount of squares the piece can travel in one move
// StartI, startJ: starting I and J positions
// addI, addJ: how much we will move each move
vector<Pos> MoveHelper(int maxMove, int startI, int startJ, int addI, int addJ, ChessPiece*** board) {

	
	vector<Pos> moves;
	for (int i = 1; i <= maxMove; i++) {
		int curI = (addI * i) + startI;
		int curJ = (addJ * i) + startJ;

		if (!inBounds(curI) || !inBounds(curJ)) {
			continue;
		}

		//if there is an enemy king blocking your way, piece is involved in a check (or potentially a checkmate). Set check flag for piece and return whatever moves were added.
		if ((board[curI][curJ]->GetSide() != board[startI][startJ]->GetSide()) && (board[curI][curJ]->getPieceType() == KING)) {
			board[startI][startJ]->setCheckStatusForPiece(true);
			return moves;
		}

		if (board[curI][curJ]->GetSide() == NONE) {
			moves.push_back(Pos(curI, curJ)); // no piece blocking path, add it and continue
		}
		else if (board[curI][curJ]->GetSide() == board[startI][startJ]->GetSide()) {
			return moves; // teammate blocking path, we return what we have so far
		}

		//if there is an enemy which is not a king blocking the path, we can add this to possible moves as a potential piece to kill.
		else if ((board[curI][curJ]->GetSide() != board[startI][startJ]->GetSide()) && (board[curI][curJ]->getPieceType() != KING)) {
			moves.push_back(Pos(curI, curJ));
			return moves;
		}
	}
	return moves;

}

//returns attacking line for a piece checking an enemy king. If not found, then this is not the attacking line.
vector<Pos> checkHelper(int maxMove, int startI, int startJ, int addI, int addJ, ChessPiece*** board) {
	
	//stores the potential final result attacking line.
	vector<Pos> potentialAttackingLine;
	
	for (int i = 1; i <= maxMove; i++) {
		int curI = (addI * i) + startI;
		int curJ = (addJ * i) + startJ;

		//out of bounds.
		if (!inBounds(curI) || !inBounds(curJ)) {
			continue;
		}

		//if there is an enemy king blocking your way, piece is involved in a check (or potentially a checkmate). Set check flag for piece and return whatever moves were added.
		if ((board[curI][curJ]->GetSide() != board[startI][startJ]->GetSide()) && (board[curI][curJ]->getPieceType() == KING)) {
			return potentialAttackingLine;
		}

		if (board[curI][curJ]->GetSide() == NONE) {
			potentialAttackingLine.push_back(Pos(curI, curJ)); //no piece blocking path, add it as a potential attacking line and continue.
		}
		else if (board[curI][curJ]->GetSide() == board[startI][startJ]->GetSide()) {
			return (vector<Pos>()); // teammate blocking path, not an attacking line so return empty set.
		}

		//if there is an enemy which is not a king blocking the path, not an attacking line so return empty set.
		else if ((board[curI][curJ]->GetSide() != board[startI][startJ]->GetSide()) && (board[curI][curJ]->getPieceType() != KING)) {
			return (vector<Pos>());
		}
	}
	//didn't find attacking line, so return empty set.
	return (vector<Pos>());
}

//returns found attacking line for Rook, else returns empty set if unexpected error occurs.
vector<Pos> Rook::AttackingLine(ChessPiece*** board, SIDE pieceColor) {

	int i = pos.x;
	int j = pos.y;

	vector<Pos> Up = checkHelper(8, i, j, 0, 1, board),
		Down = checkHelper(8, i, j, 0, -1, board),
		Right = checkHelper(8, i, j, 1, 0, board),
		Left = checkHelper(8, i, j, -1, 0, board);

	if (Up.size() != 0) {
		return Up;
	}
	else if (Down.size() != 0) {
		return Down;
	}
	else if (Right.size() != 0) {
		return Right;
	}
	else if (Left.size() != 0) {
		return Left;
	}

	return vector<Pos>();

}

//returns found attacking line for Bishop, else returns empty set if unexpected error occurs.
vector<Pos> Bishop::AttackingLine(ChessPiece*** board, SIDE pieceColor) {
	int i = pos.x;
	int j = pos.y;
	vector<Pos> Up = checkHelper(8, i, j, 1, 1, board),
		Down = checkHelper(8, i, j, -1, -1, board),
		Right = checkHelper(8, i, j, -1, 1, board),
		Left = checkHelper(8, i, j, 1, -1, board);
	if (Up.size() != 0) {
		return Up;
	}
	else if (Down.size() != 0) {
		return Down;
	}
	else if (Right.size() != 0) {
		return Right;
	}
	else if (Left.size() != 0) {
		return Left;
	}

	return vector<Pos>();

}

//returns found attacking line for Queen, else returns empty set if unexpected error occurs.
vector<Pos> Queen::AttackingLine(ChessPiece*** board, SIDE pieceColor) {
	int i = pos.x;
	int j = pos.y;
	vector<Pos> UpRight = checkHelper(8, i, j, 1, 1, board),
		DownLeft = checkHelper(8, i, j, -1, -1, board),
		DownRight = checkHelper(8, i, j, -1, 1, board),
		UpLeft = checkHelper(8, i, j, 1, -1, board),
		Up = checkHelper(8, i, j, 0, 1, board),
		Down = checkHelper(8, i, j, 0, -1, board),
		Right = checkHelper(8, i, j, -1, 0, board),
		Left = checkHelper(8, i, j, 1, -0, board);

	if (Up.size() != 0) {
		return Up;
	}
	else if (Down.size() != 0) {
		return Down;
	}
	else if (Right.size() != 0) {
		return Right;
	}
	else if (Left.size() != 0) {
		return Left;
	}

	if (UpRight.size() != 0) {
		return UpRight;
	}

	if (UpLeft.size() != 0) {
		return UpLeft;
	}

	if (DownRight.size() != 0) {
		return DownRight;
	}

	if (DownLeft.size() != 0) {
		return DownLeft;
	}


	return vector<Pos>();

}




vector<Pos> Rook::PossibleMoves(ChessPiece*** board, SIDE pieceColor)
{
	// find a different way instead of this function
	if (ProtectingQueen()) {
		return vector<Pos>();
	}

	vector<Pos> PossibleMove;
	
	int i = pos.x;
	int j = pos.y;
	vector<Pos> Up = MoveHelper(8, i, j, 0, 1, board), 
		Down = MoveHelper(8, i, j, 0, -1, board), 
		Right = MoveHelper(8, i, j, 1, 0, board), 
		Left = MoveHelper(8, i, j, -1, 0, board);

	PossibleMove = Up;
	PossibleMove.insert(PossibleMove.end(), Down.begin(), Down.end());
	PossibleMove.insert(PossibleMove.end(), Right.begin(), Right.end());
	PossibleMove.insert(PossibleMove.end(), Left.begin(), Left.end());

	return PossibleMove;
}

Bishop::Bishop(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
	this->pieceName = BISHOP;

	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/bishopw.png")) {
			printf("bishopw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/bishopb.png")) {
			printf("bishopb error\n");
			exit(0);
		}
	}
	else {
		printf("bishop error\n");
		exit(0);
	}

	this->pos = pos;
}

vector<Pos> Bishop::PossibleMoves(ChessPiece*** board, SIDE pieceColor)
{
	// find a different way instead of this function
	if (ProtectingQueen()) {
		return vector<Pos>();
	}

	vector<Pos> PossibleMove;

	int i = pos.x;
	int j = pos.y;
	vector<Pos> Up = MoveHelper(8, i, j, 1, 1, board),
		Down = MoveHelper(8, i, j, -1, -1, board),
		Right = MoveHelper(8, i, j, -1, 1, board),
		Left = MoveHelper(8, i, j, 1, -1, board);

	PossibleMove = Up;
	PossibleMove.insert(PossibleMove.end(), Down.begin(), Down.end());
	PossibleMove.insert(PossibleMove.end(), Right.begin(), Right.end());
	PossibleMove.insert(PossibleMove.end(), Left.begin(), Left.end());

	return PossibleMove;
}

King::King(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
	this->pieceName = KING;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/kingw.png")) {
			printf("kingw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/kingb.png")) {
			printf("kingb error\n");
			exit(0);
		}
	}
	else {
		printf("king error\n");
		exit(0);
	}

	this->pos = pos;
}

vector<Pos> King::PossibleMoves(ChessPiece*** board, SIDE pieceColor)
{
	vector<Pos> PossibleMove;

	int i = pos.x;
	int j = pos.y;
	vector<Pos> UpRight = MoveHelper(1, i, j, 1, 1, board),
		DownLeft = MoveHelper(1, i, j, -1, -1, board),
		DownRight = MoveHelper(1, i, j, -1, 1, board),
		UpLeft = MoveHelper(1, i, j, 1, -1, board),
		Up = MoveHelper(1, i, j, 0, 1, board),
		Down = MoveHelper(1, i, j, 0, -1, board),
		Right = MoveHelper(1, i, j, -1, 0, board),
		Left = MoveHelper(1, i, j, 1, -0, board);
	PossibleMove = Up;
	PossibleMove.insert(PossibleMove.end(), Down.begin(), Down.end());
	PossibleMove.insert(PossibleMove.end(), Right.begin(), Right.end());
	PossibleMove.insert(PossibleMove.end(), Left.begin(), Left.end());
	PossibleMove.insert(PossibleMove.end(), UpLeft.begin(), UpLeft.end());
	PossibleMove.insert(PossibleMove.end(), UpRight.begin(), UpRight.end());
	PossibleMove.insert(PossibleMove.end(), DownLeft.begin(), DownLeft.end());
	PossibleMove.insert(PossibleMove.end(), DownRight.begin(), DownRight.end());

	return PossibleMove;
}

Queen::Queen(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
	this->pieceName = QUEEN;

	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/queenw.png")) {
			printf("queenw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/queenb.png")) {
			printf("queenb error\n");
			exit(0);
		}
	}
	else {
		printf("queen error\n");
		exit(0);
	}

	this->pos = pos;
}

vector<Pos> Queen::PossibleMoves(ChessPiece*** board, SIDE pieceColor)
{
	if (ProtectingQueen()) {
		return vector<Pos>();
	}

	vector<Pos> PossibleMove;

	int i = pos.x;
	int j = pos.y;
	vector<Pos> UpRight = MoveHelper(8, i, j, 1, 1, board),
		DownLeft = MoveHelper(8, i, j, -1, -1, board),
		DownRight = MoveHelper(8, i, j, -1, 1, board),
		UpLeft = MoveHelper(8, i, j, 1, -1, board), 
		Up = MoveHelper(8, i, j, 0, 1, board),
		Down = MoveHelper(8, i, j, 0, -1, board),
		Right = MoveHelper(8, i, j, -1, 0, board),
		Left = MoveHelper(8, i, j, 1, -0, board);;

	PossibleMove = Up;
	PossibleMove.insert(PossibleMove.end(), Down.begin(), Down.end());
	PossibleMove.insert(PossibleMove.end(), Right.begin(), Right.end());
	PossibleMove.insert(PossibleMove.end(), Left.begin(), Left.end());
	PossibleMove.insert(PossibleMove.end(), UpLeft.begin(), UpLeft.end());
	PossibleMove.insert(PossibleMove.end(), UpRight.begin(), UpRight.end());
	PossibleMove.insert(PossibleMove.end(), DownLeft.begin(), DownLeft.end());
	PossibleMove.insert(PossibleMove.end(), DownRight.begin(), DownRight.end());

	return PossibleMove;
}

Pawn::Pawn(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
	this->pieceName = PAWN;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/pawnw.png")) {
			printf("pawnw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/pawnb.png")) {
			printf("pawnb error\n");
			exit(0);
		}
	}
	else {
		printf("king error\n");
		exit(0);
	}

	this->pos = pos;
}

vector<Pos> Pawn::PossibleMoves(ChessPiece*** board, SIDE pieceColor)
{
	if (ProtectingQueen()) {
		return vector<Pos>();
	}
	vector<Pos> PossibleMove;

	int i = pos.x;
	int j = pos.y;
	int side = this->pieceSide == BLACK ? 1 : -1;

	vector<Pos> UpRight = MoveHelper(1, i, j, 1, side, board),
		UpLeft = MoveHelper(1, i, j, -1, side, board),
		Up = MoveHelper(1, i, j, 0, side, board),
		Up2 = MoveHelper(2, i, j, 0, side, board);

	if (Up.size()) {
		if (this->isMoved) {
			SIDE PosSide = board[Up.front().x][Up.front().y]->GetSide();
			if (PosSide == NONE) {
				PossibleMove = Up;
			}
		}
	}


	if (Up2.size()) {
		if (!this->isMoved) {
			SIDE PosSide1 = board[Up2.front().x][Up2.front().y]->GetSide();
			SIDE PosSide2 = board[Up2.back().x][Up2.back().y]->GetSide();
			if (PosSide1 == NONE) {
				PossibleMove = Up;
			}
			if (PosSide2 == NONE) {
				PossibleMove = Up2;
			}
			
		}
	}

	if (!UpRight.empty()) {
		SIDE PosSide = board[UpRight.front().x][UpRight.front().y]->GetSide();
		if (PosSide != NONE && PosSide != this->pieceSide) {
			PossibleMove.insert(PossibleMove.end(), UpRight.begin(), UpRight.end());
		}
	}

	if (!UpLeft.empty()) {
		SIDE PosSide = board[UpLeft.front().x][UpLeft.front().y]->GetSide();
		//printf("%d", PosSide);
		if (PosSide != NONE && PosSide != this->pieceSide) {
			PossibleMove.insert(PossibleMove.end(), UpLeft.begin(), UpLeft.end());
		}
	}
	

	return PossibleMove;
}

Knight::Knight(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
	this->pieceName = KNIGHT;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/knightw.png")) {
			printf("knightw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/knightb.png")) {
			printf("knightb error\n");
			exit(0);
		}
	}
	else {
		printf("pawn error\n");
		exit(0);
	}

	this->pos = pos;
}

vector<Pos> Knight::PossibleMoves(ChessPiece*** board, SIDE pieceColor)
{
	vector<Pos> PossibleMove;

	int i = pos.x;
	int j = pos.y;
	vector<Pos> UpRight = MoveHelper(1, i, j, -1, -2, board),
		DownLeft = MoveHelper(1, i, j, 1, 2, board),
		DownRight = MoveHelper(1, i, j, -1, 2, board),
		UpLeft = MoveHelper(1, i, j, 1, -2, board),
		Up = MoveHelper(1, i, j, 2, 1, board),
		Down = MoveHelper(1, i, j, -2, -1, board),
		Right = MoveHelper(1, i, j, -2, 1, board),
		Left = MoveHelper(1, i, j, 2, -1, board);;

	PossibleMove = Up;
	PossibleMove.insert(PossibleMove.end(), Down.begin(), Down.end());
	PossibleMove.insert(PossibleMove.end(), Right.begin(), Right.end());
	PossibleMove.insert(PossibleMove.end(), Left.begin(), Left.end());
	PossibleMove.insert(PossibleMove.end(), UpLeft.begin(), UpLeft.end());
	PossibleMove.insert(PossibleMove.end(), UpRight.begin(), UpRight.end());
	PossibleMove.insert(PossibleMove.end(), DownLeft.begin(), DownLeft.end());
	PossibleMove.insert(PossibleMove.end(), DownRight.begin(), DownRight.end());

	return PossibleMove;
}

Empty::Empty(Pos pos, string label)
{
	this->TypeLabel = label;
	this->pieceSide = NONE;
	this->pos = pos;
}
