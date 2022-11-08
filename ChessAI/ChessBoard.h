#pragma once
#include "ChessPiece.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class ChessBoard {
public:

	//this is only used for check state handling. This will store the valid moves in "validMoves" of the chess piece "piece" that can be selected and utilized during check state. 
	struct Chess_Piece_Node {
		ChessPiece* piece;
		vector<Pos> validMoves;
	};

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

	//handles situations of check state for white or black side respectively.
	void checkHandlerWhite();
	void checkHandlerBlack();

	void setIsCheckMateOnBlack();
	void setIsCheckMateOnWhite();
	bool getIsCheckMateOnWhite();
	bool getIsCheckMateOnBlack();

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
	
	//stores all of the chess pieces that can be moved during check state for the white side.
	vector<Chess_Piece_Node> validPiecesToMoveDuringCheckWhite;
	//stores all of the chess pieces that can be moved during check state for the black side.
	vector<Chess_Piece_Node> validPiecesToMoveDuringCheckBlack;

	//if black is in check mate or not.
	bool isCheckMateOnBlack = false;
	//if white is in check mate or not.
	bool isCheckMateOnWhite = false;
};
