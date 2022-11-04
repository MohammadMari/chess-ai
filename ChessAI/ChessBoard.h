#pragma once
#include "ChessPiece.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class ChessBoard {
public:
	ChessBoard();
	SIDE GetcurTurn();
	SIDE SwapCurTurn();
	void DisplayBoard(RenderWindow& window);
	void ProcessClickEvent(int x, int y);
private:
	SIDE curTurn = WHITE;
	SIDE userSide = WHITE; // keep white for now, later we make it so that it supports both
	ChessPiece** piecePos[8];
	ChessPiece* selectedPiece = nullptr;
};
