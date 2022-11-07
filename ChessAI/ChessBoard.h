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

	bool getCheckFlagWhite();
	bool getCheckFlagBlack();
	void setCheckFlagWhite(bool valueToSet);
	void setCheckFlagBlack(bool valueToSet);
	//determines if either black or white is in check, if so then set appropriate flag value(s) to true, if not then set appropriate flag value(s) to false.
	void determineIfAnyCheck();

private:
	SIDE curTurn = WHITE;
	SIDE userSide = WHITE; // keep white for now, later we make it so that it supports both
	ChessPiece** piecePos[8];
	ChessPiece* selectedPiece = nullptr;

	//containers that store any chess pieces, either white or black, participating in checking their respective enemy kings.
	vector<ChessPiece*> blackPiecesChecking;
	vector<ChessPiece*> whitePiecesChecking;

	//represents if white is in check or not. Initially false since at initial state, check is impossible.
	bool checkFlagWhite = false;
	//represents if black is in check or not. Intially false since at initial state, check is impossible.
	bool checkFlagBlack = false;
};
