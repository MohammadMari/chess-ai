#pragma once
#include <SFML/Graphics.hpp>



enum SIDE {
	NONE,
	WHITE,
	BLACK
};

using namespace sf;

class ChessPiece {
public:
	ChessPiece();
	ChessPiece(SIDE side);
	SIDE GetSide();
	void SetSide(SIDE side);
	Texture GetTexture();
protected:
	SIDE pieceSide = NONE;
	Texture texture;
};


class Rook : public ChessPiece {
public:
	Rook(SIDE side);
};

class Bishop : public ChessPiece {
public:
	Bishop(SIDE side);
};

class King : public ChessPiece {
public:
	King(SIDE side);
};

class Queen : public ChessPiece {
public:
	Queen(SIDE side);
};

class Knight : public ChessPiece {
public:
	Knight(SIDE side);
};

class Pawn : public ChessPiece {
public:
	Pawn(SIDE side);
private:
	bool Moved = false; // used for en passant
};

