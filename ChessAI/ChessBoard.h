#pragma once
#include "ChessPiece.h"
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

//the chess board size is always fixed, and is provided as below (8x8 grid for pieces but the very bottom row (8) and right column (8) is used to display fixed node label letters/numbers).
#define CHESS_BOARD_ROWS 8
#define CHESS_BOARD_COLS 8

//the number of chess pieces (in total), on the board initially.
#define NUM_CHESS_PIECES_INITIALLY 32

/*
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
*/

class ChessBoard {

private:
    //defines a node or grid square of the chess board.
    typedef struct grid_node {
        string nodeLabel;
        ChessPiece currPieceOnNode;
    }grid_node;
	
    //defines the chess board itself.
    grid_node chessGrid[CHESS_BOARD_ROWS][CHESS_BOARD_COLS];
    //holds all of the pieces that black currently has.
    vector<ChessPiece> blackPieces;
    //holds all of the pieces that white currently has.
    vector<ChessPiece> whitePieces;

    //states whether if black or white has their respective kings in a "check" (not checkmate) state or not. Initially this is false as a check cannot occur at the start of a game.
    bool checkFlagBlack = false;
    bool checkFlagWhite = false;

public:

    //constructor sets up intial board layout with initializeGrid.
    ChessBoard() {
        InitializeGrid();
    }

    //determines the grid node locations for either of the kings and returns their respective current node label.
   //string determinePositionWhiteKing();
    //string determinePositionBlackKing();
    
    //intializes chessGrid and chessPieces and their positions on the chessGrid before the game starts.
    void InitializeGrid();

    //outputs the current state of the grid.
    void DisplayBoard(RenderWindow& window);

    //updates the possibleMoves vector of the given piece and sets the checkflags to detect check. Clears possibleMoves vector first then calculates the possible moves for that piece type. This function does not handle the appropriate moves calculations for a king piece. This function also does not actually move the chess piece.
    void determinePossibleMoves(ChessPiece& pieceToUpdate);

    //handles actually moving the chess piece based on a user requested choice.
    //void requestedMove(string userChoice);

    //updates pawns that meet the critera for promotion and what that pawn will update too.
   // void promotion();

    //for every state, this is checked (in requestedMove after the requested move is executed), to see if checkmate.
  //  bool isCheckMate();

    //updates all possible moves for a king, meant to be called after "determinePossibleMoves" function updates all the pieces.
   // void determinePossibleMovesKing();

    //gets and sets for checkflags.
    void setCheckFlagBlack(bool checkFlagBlack) { this->checkFlagBlack = checkFlagBlack; }
    bool getCheckFlagBlack() { return this->checkFlagBlack; }
    void setCheckFlagWhite(bool checkFlagWhite) { this->checkFlagWhite = checkFlagWhite; }
    bool getCheckFlagWhite() { return this->checkFlagWhite; }
};
