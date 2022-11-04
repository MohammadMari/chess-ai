#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

enum SIDE {
	NONE,
	WHITE,
	BLACK
};

using namespace sf;

struct Pos {
	Pos(int x, int y) {
		this->x = x;
		this->y = y;
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
	bool ProtectingQueen() {
		return false; // temporary
	}
	virtual vector<Pos> PossibleMoves(ChessPiece*** board) = 0;
protected:
	SIDE pieceSide = NONE;
	Texture texture;
	Pos pos = Pos(0, 0);
};


class Empty : public ChessPiece {
public:
	Empty(Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board) {
		return vector<Pos>();
	}
};


class Rook : public ChessPiece {
public:
	Rook(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board);
};

class Bishop : public ChessPiece {
public:
	Bishop(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board);
};

class King : public ChessPiece {
public:
	King(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board);
};

class Queen : public ChessPiece {
public:
	Queen(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board);
};

class Knight : public ChessPiece {
public:
	Knight(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board);
};

class Pawn : public ChessPiece {
public:
	Pawn(SIDE side, Pos pos, string label);
	vector<Pos> PossibleMoves(ChessPiece*** board);
private:
	bool Moved = false; // used for en passant
};

