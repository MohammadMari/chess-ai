#pragma once
#include "ChessPiece.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class ChessBoard {
public:
	SIDE GetcurTurn();
	void SwapcurTurn();
	void DisplayBoard(RenderWindow &window);
	ChessBoard();
private:
	SIDE curTurn = NONE;
	ChessPiece piecePos[8][8];
};
