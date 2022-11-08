#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

enum SIDE {
	NONE,
	WHITE,
	BLACK
};


//defines general piece type.
enum PIECE_TYPE {
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PAWN,
	INVALID
};

using namespace sf;

struct Pos {
	Pos(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Pos(){

	}

	int x = 0;
	int y = 0;
};

class ChessPiece {
public:
	ChessPiece();
	ChessPiece(SIDE side);
	SIDE GetSide();
	void SetSide(SIDE side);
	Texture GetTexture();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	string TypeLabel;




	//has the piece been moved yet? Intially false, and currently only implemented for double step for pawns.
	bool isMoved = false;

	//return defined piece type.
	PIECE_TYPE getPieceType();

	bool getCheckStatusForPiece();
	void setCheckStatusForPiece(bool valueToSet);

	bool ProtectingQueen() {
		return false; // temporary
	}
	virtual vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE) = 0;
	
	//determines attacking line for chess pieces checking their respective enemy kings King (This is not applicable for knight pieces or king pieces or pawn pieces). 
	virtual vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE) = 0;

	protected:
	//this determines whether if a given piece is currently checking enemy King or not.
	bool isPiecePartCheck = false;

	//label to identify general type of piece.
	PIECE_TYPE pieceName = INVALID;

	SIDE pieceSide = NONE;
	Texture texture;
	Pos pos = Pos(0, 0);
};


class Empty : public ChessPiece {
public:
	Empty(Pos pos, string label);
	//not applicable for this class.
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE) {
		return vector<Pos>();
	}
	//not applicable for this class.
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE) {
		return vector<Pos>();
	}
};


class Rook : public ChessPiece {
public:
	Rook(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE);
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE);
};

class Bishop : public ChessPiece {
public:
	Bishop(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE);
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE);
};

class King : public ChessPiece {
public:
	King(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE);
	//not applicable for King.
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE) {
		return vector<Pos>();
	}
};

class Queen : public ChessPiece {
public:
	Queen(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE);
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE);
};

class Knight : public ChessPiece {
public:
	Knight(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE);
	//not applicable for a knight piece.
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE) {
		return vector<Pos>();
	}
};

class Pawn : public ChessPiece {
public:
	Pawn(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board, SIDE pieceColor = NONE);
	//not applicable for a pawn piece.
	vector<Pos> AttackingLine(ChessPiece*** board, SIDE pieceColor = NONE) {
		return vector<Pos>();
	}
private:
	bool Moved = false; // used for en passant
};
