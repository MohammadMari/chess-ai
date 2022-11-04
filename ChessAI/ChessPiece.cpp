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


// Rook
Rook::Rook(SIDE side, Pos pos, string label)
{
	this->TypeLabel = label;
	pieceSide = side;
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

		if (board[curI][curJ]->GetSide() == NONE) {
			moves.push_back(Pos(curI, curJ)); // no piece blocking path, add it and continue
		}
		else if (board[curI][curJ]->GetSide() == board[startI][startJ]->GetSide()) { 
			return moves; // teammate blocking path, we return what we have so far
		}
		else if (board[curI][curJ]->GetSide() != board[startI][startJ]->GetSide()) {
			moves.push_back(Pos(curI, curJ)); // enemy blocking path, we can take it, so we add and return
			return moves;
		}
	}

	return moves;
}



vector<Pos> Rook::PossibleMoves(ChessPiece*** board)
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

vector<Pos> Bishop::PossibleMoves(ChessPiece*** board)
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

vector<Pos> King::PossibleMoves(ChessPiece*** board)
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
		Left = MoveHelper(1, i, j, 1, -0, board);;

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

vector<Pos> Queen::PossibleMoves(ChessPiece*** board)
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

vector<Pos> Pawn::PossibleMoves(ChessPiece*** board)
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
		Up = MoveHelper(1, i, j, 0, side, board);


	if (Up.size()) {
		SIDE PosSide = board[Up.front().x][Up.front().y]->GetSide();
		if (PosSide == NONE) {
			PossibleMove = Up;
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
		printf("%d", PosSide);
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

vector<Pos> Knight::PossibleMoves(ChessPiece*** board)
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
