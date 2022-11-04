#include "ChessBoard.h"

/*
ChessBoard::ChessBoard()
{
	piecePos[0][0] = Rook(BLACK);
	piecePos[1][0] = Knight(BLACK);
	piecePos[2][0] = Bishop(BLACK);
	piecePos[3][0] = Queen(BLACK);
	piecePos[4][0] = King(BLACK);
	piecePos[5][0] = Bishop(BLACK);
	piecePos[6][0] = Knight(BLACK);
	piecePos[7][0] = Rook(BLACK);

	for (int i = 0; i < 8; i++) {
		piecePos[i][1] = Pawn(BLACK);
		piecePos[i][6] = Pawn(WHITE);
	}
	
	piecePos[0][7] = Rook(WHITE);
	piecePos[1][7] = Knight(WHITE);
	piecePos[2][7] = Bishop(WHITE);
	piecePos[3][7] = Queen(WHITE);
	piecePos[4][7] = King(WHITE);
	piecePos[5][7] = Bishop(WHITE);
	piecePos[6][7] = Knight(WHITE);
	piecePos[7][7] = Rook(WHITE);
}


SIDE ChessBoard::GetcurTurn()
{
	return curTurn;
}

void ChessBoard::SwapcurTurn()
{
	if (curTurn == NONE) {
		curTurn = WHITE;
	}
	else if (curTurn == WHITE) {
		curTurn == BLACK;
	} 
	else if (curTurn == BLACK) {
		curTurn = WHITE;
	}
}

void ChessBoard::DisplayBoard(RenderWindow &window)
{
	RectangleShape boardSquare;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {		
			Color squareColor = (i + j) % 2 == 0 ? Color(238,238,213) : Color(125,148,93);

			// set rectangle properties
			boardSquare.setSize(Vector2f(75, 75));
			boardSquare.setPosition(Vector2f(i * 75, j * 75));
			boardSquare.setFillColor(squareColor);

			// add rectangle to draw list
			window.draw(boardSquare);

			//draw chess pieces
			if (piecePos[i][j].GetSide() != NONE) {
				Sprite piecePic;
				Texture pieceText = piecePos[i][j].GetTexture();
				piecePic.setTexture(pieceText);
				piecePic.setScale(Vector2f(1,1));
				piecePic.setPosition(Vector2f((i * 75) + 15, (j * 75) + 10));
				window.draw(piecePic);
			}
		}
	}
}
*/

void ChessBoard::DisplayBoard(RenderWindow& window)
{
	RectangleShape boardSquare;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Color squareColor = (i + j) % 2 == 0 ? Color(238, 238, 213) : Color(125, 148, 93);

			// set rectangle properties
			boardSquare.setSize(Vector2f(75, 75));
			boardSquare.setPosition(Vector2f(i * 75, j * 75));
			boardSquare.setFillColor(squareColor);

			// add rectangle to draw list
			window.draw(boardSquare);

			//draw chess pieces
            //if there is an actual piece on that node to draw.
            if (chessGrid[i][j].currPieceOnNode.getPieceName() != "EmptyString") {
                chessGrid[i][j].currPieceOnNode.loadTexture();
                Sprite piecePic;
                Texture pieceText = chessGrid[i][j].currPieceOnNode.GetTexture();
                piecePic.setTexture(pieceText);
                piecePic.setScale(Vector2f(1, 1));
                piecePic.setPosition(Vector2f((i * 75) + 15, (j * 75) + 10));
                window.draw(piecePic);
            }
		}
	}
}



//intializes chessGrid and chessPieces and their positions on the chessGrid before the game starts.
void ChessBoard::InitializeGrid() {


    //set the labels for the grid_nodes (for non-display nodes), and also sets every grid node as empty.
    for (unsigned int i = 0; i < 8; i++) {
        int rowNumber = 1 + i;
        for (unsigned int j = 0; j < 8; j++) {
            string newNodeLabel = ((char)('a' + j)) + to_string(rowNumber);
            chessGrid[i][j].nodeLabel = newNodeLabel;
            ChessPiece emptyPiece;
            chessGrid[i][j].currPieceOnNode = emptyPiece;
        }
    }



    //create the pieces to be populated into the chess board and black/white pieces vectors.

    //8 pawns, 2 knights, 2 bishops, 2 rooks, 1 queen and 1 king per side.

    //black pieces, place these pieces into the blackPieces container.
    ChessPiece blackPawn1("Black", "Pawn");
    blackPieces.push_back(blackPawn1);
    ChessPiece blackPawn2("Black", "Pawn");
    blackPieces.push_back(blackPawn2);
    ChessPiece blackPawn3("Black", "Pawn");
    blackPieces.push_back(blackPawn3);
    ChessPiece blackPawn4("Black", "Pawn");
    blackPieces.push_back(blackPawn4);
    ChessPiece blackPawn5("Black", "Pawn");
    blackPieces.push_back(blackPawn5);
    ChessPiece blackPawn6("Black", "Pawn");
    blackPieces.push_back(blackPawn6);
    ChessPiece blackPawn7("Black", "Pawn");
    blackPieces.push_back(blackPawn7);
    ChessPiece blackPawn8("Black", "Pawn");
    blackPieces.push_back(blackPawn8);
    ChessPiece blackHorse1("Black", "Horse");
    blackPieces.push_back(blackHorse1);
    ChessPiece blackHorse2("Black", "Horse");
    blackPieces.push_back(blackHorse2);
    ChessPiece blackRook1("Black", "Rook");
    blackPieces.push_back(blackRook1);
    ChessPiece blackRook2("Black", "Rook");
    blackPieces.push_back(blackRook2);
    ChessPiece blackBishop1("Black", "Bishop");
    blackPieces.push_back(blackBishop1);
    ChessPiece blackBishop2("Black", "Bishop");
    blackPieces.push_back(blackBishop2);
    ChessPiece blackQueen1("Black", "Queen");
    blackPieces.push_back(blackQueen1);
    ChessPiece blackKing("Black", "King");
    blackPieces.push_back(blackKing);

    //white pieces, also placing them into their respective whitePieces container.
    ChessPiece whitePawn1("White", "Pawn");
    whitePieces.push_back(whitePawn1);
    ChessPiece whitePawn2("White", "Pawn");
    whitePieces.push_back(whitePawn2);
    ChessPiece whitePawn3("White", "Pawn");
    whitePieces.push_back(whitePawn3);
    ChessPiece whitePawn4("White", "Pawn");
    whitePieces.push_back(whitePawn4);
    ChessPiece whitePawn5("White", "Pawn");
    whitePieces.push_back(whitePawn5);
    ChessPiece whitePawn6("White", "Pawn");
    whitePieces.push_back(whitePawn6);
    ChessPiece whitePawn7("White", "Pawn");
    whitePieces.push_back(whitePawn7);
    ChessPiece whitePawn8("White", "Pawn");
    whitePieces.push_back(whitePawn8);
    ChessPiece whiteHorse1("White", "Horse");
    whitePieces.push_back(whiteHorse1);
    ChessPiece whiteHorse2("White", "Horse");
    whitePieces.push_back(whiteHorse2);
    ChessPiece whiteRook1("White", "Rook");
    whitePieces.push_back(whiteRook1);
    ChessPiece whiteRook2("White", "Rook");
    whitePieces.push_back(whiteRook2);
    ChessPiece whiteBishop1("White", "Bishop");
    whitePieces.push_back(whiteBishop1);
    ChessPiece whiteBishop2("White", "Bishop");
    whitePieces.push_back(whiteBishop2);
    ChessPiece whiteQueen1("White", "Queen");
    whitePieces.push_back(whiteQueen1);
    ChessPiece whiteKing("White", "King");
    whitePieces.push_back(whiteKing);


    //sets up the intial arrangement of chess pieces for a chess game the very moment it starts, on the chess board.
    for (unsigned int i = 0; i < 8; i++) {
        for (unsigned int j = 0; j < 8; j++) {

            //based on the specified nodeLabel, place the correct chess pieces (both black and white) on the board to mimic the starting state of a real chessboard.

            if (chessGrid[i][j].nodeLabel == "a1") {
                whiteRook1.setCurrNodeLabel("a1");
                chessGrid[i][j].currPieceOnNode = whiteRook1;
            }
            if (chessGrid[i][j].nodeLabel == "b1") {
                whiteHorse1.setCurrNodeLabel("b1");
                chessGrid[i][j].currPieceOnNode = whiteHorse1;
            }
            if (chessGrid[i][j].nodeLabel == "c1") {
                whiteBishop1.setCurrNodeLabel("c1");
                chessGrid[i][j].currPieceOnNode = whiteBishop1;
            }
            if (chessGrid[i][j].nodeLabel == "d1") {
                whiteQueen1.setCurrNodeLabel("d1");
                chessGrid[i][j].currPieceOnNode = whiteQueen1;
            }
            if (chessGrid[i][j].nodeLabel == "e1") {
                whiteKing.setCurrNodeLabel("e1");
                chessGrid[i][j].currPieceOnNode = whiteKing;
            }
            if (chessGrid[i][j].nodeLabel == "f1") {
                whiteBishop2.setCurrNodeLabel("f1");
                chessGrid[i][j].currPieceOnNode = whiteBishop2;
            }
            if (chessGrid[i][j].nodeLabel == "g1") {
                whiteHorse2.setCurrNodeLabel("g1");
                chessGrid[i][j].currPieceOnNode = whiteHorse2;
            }
            if (chessGrid[i][j].nodeLabel == "h1") {
                whiteRook2.setCurrNodeLabel("h1");
                chessGrid[i][j].currPieceOnNode = whiteRook2;
            }
            if (chessGrid[i][j].nodeLabel == "a2") {
                whitePawn1.setCurrNodeLabel("a2");
                chessGrid[i][j].currPieceOnNode = whitePawn1;
            }
            if (chessGrid[i][j].nodeLabel == "b2") {
                whitePawn2.setCurrNodeLabel("b2");
                chessGrid[i][j].currPieceOnNode = whitePawn2;
            }
            if (chessGrid[i][j].nodeLabel == "c2") {
                whitePawn3.setCurrNodeLabel("c2");
                chessGrid[i][j].currPieceOnNode = whitePawn3;
            }
            if (chessGrid[i][j].nodeLabel == "d2") {
                whitePawn4.setCurrNodeLabel("d2");
                chessGrid[i][j].currPieceOnNode = whitePawn4;
            }
            if (chessGrid[i][j].nodeLabel == "e2") {
                whitePawn5.setCurrNodeLabel("e2");
                chessGrid[i][j].currPieceOnNode = whitePawn5;
            }
            if (chessGrid[i][j].nodeLabel == "f2") {
                whitePawn6.setCurrNodeLabel("f2");
                chessGrid[i][j].currPieceOnNode = whitePawn6;
            }
            if (chessGrid[i][j].nodeLabel == "g2") {
                whitePawn7.setCurrNodeLabel("g2");
                chessGrid[i][j].currPieceOnNode = whitePawn7;
            }
            if (chessGrid[i][j].nodeLabel == "h2") {
                whitePawn8.setCurrNodeLabel("h2");
                chessGrid[i][j].currPieceOnNode = whitePawn8;
            }


            if (chessGrid[i][j].nodeLabel == "a8") {
                blackRook1.setCurrNodeLabel("a8");
                chessGrid[i][j].currPieceOnNode = blackRook1;
            }
            if (chessGrid[i][j].nodeLabel == "b8") {
                blackHorse1.setCurrNodeLabel("b8");
                chessGrid[i][j].currPieceOnNode = blackHorse1;
            }
            if (chessGrid[i][j].nodeLabel == "c8") {
                blackBishop1.setCurrNodeLabel("c8");
                chessGrid[i][j].currPieceOnNode = blackBishop1;
            }
            if (chessGrid[i][j].nodeLabel == "d8") {
                blackQueen1.setCurrNodeLabel("d8");
                chessGrid[i][j].currPieceOnNode = blackQueen1;
            }
            if (chessGrid[i][j].nodeLabel == "e8") {
                blackKing.setCurrNodeLabel("e8");
                chessGrid[i][j].currPieceOnNode = blackKing;
            }
            if (chessGrid[i][j].nodeLabel == "f8") {
                blackBishop2.setCurrNodeLabel("f8");
                chessGrid[i][j].currPieceOnNode = blackBishop2;
            }
            if (chessGrid[i][j].nodeLabel == "g8") {
                blackHorse2.setCurrNodeLabel("g8");
                chessGrid[i][j].currPieceOnNode = blackHorse2;
            }
            if (chessGrid[i][j].nodeLabel == "h8") {
                blackRook2.setCurrNodeLabel("h8");
                chessGrid[i][j].currPieceOnNode = blackRook2;
            }
            if (chessGrid[i][j].nodeLabel == "a7") {
                blackPawn1.setCurrNodeLabel("a7");
                chessGrid[i][j].currPieceOnNode = blackPawn1;
            }
            if (chessGrid[i][j].nodeLabel == "b7") {
                blackPawn2.setCurrNodeLabel("b7");
                chessGrid[i][j].currPieceOnNode = blackPawn2;
            }
            if (chessGrid[i][j].nodeLabel == "c7") {
                blackPawn3.setCurrNodeLabel("c7");
                chessGrid[i][j].currPieceOnNode = blackPawn3;
            }
            if (chessGrid[i][j].nodeLabel == "d7") {
                blackPawn4.setCurrNodeLabel("d7");
                chessGrid[i][j].currPieceOnNode = blackPawn4;
            }
            if (chessGrid[i][j].nodeLabel == "e7") {
                blackPawn5.setCurrNodeLabel("e7");
                chessGrid[i][j].currPieceOnNode = blackPawn5;
            }
            if (chessGrid[i][j].nodeLabel == "f7") {
                blackPawn6.setCurrNodeLabel("f7");
                chessGrid[i][j].currPieceOnNode = blackPawn6;
            }
            if (chessGrid[i][j].nodeLabel == "g7") {
                blackPawn7.setCurrNodeLabel("g7");
                chessGrid[i][j].currPieceOnNode = blackPawn7;
            }
            if (chessGrid[i][j].nodeLabel == "h7") {
                blackPawn8.setCurrNodeLabel("h7");
                chessGrid[i][j].currPieceOnNode = blackPawn8;
            }
        }
    }

    //We also need to determine the initial set of possible moves for all pieces.
    for (unsigned int i = 0; i < CHESS_BOARD_ROWS; i++) {
        for (unsigned int j = 0; j < CHESS_BOARD_COLS; j++) {
            //iterating through the whole grid, find nodes which have pieces in them. "EmptyString" correlates to a grid node with no piece in it.
            if (chessGrid[i][j].currPieceOnNode.getPieceName() != "EmptyString") {
                //if a piece is there, we must determine the possible valid moves for the piece.
                determinePossibleMoves(chessGrid[i][j].currPieceOnNode);
            }
        }
    }
}



void ChessBoard::determinePossibleMoves(ChessPiece& pieceToUpdate) {

    //clears the previously calculated possible moves (if any).
    pieceToUpdate.erase();

    //stores the index where this piece is located on the chess board.
    unsigned int pieceIndexRow, pieceIndexColumn;

    //finds the indexes of the piece on the chessboard.
    for (unsigned int i = 0; i < CHESS_BOARD_ROWS; i++) {
        for (unsigned int j = 0; j < CHESS_BOARD_COLS; j++) {
            //if the piece we stumble across is the piece we are currently referencing (each piece will always have unique position on the board in a given state).
            if (chessGrid[i][j].currPieceOnNode.GetCurrNodeLabel() == pieceToUpdate.GetCurrNodeLabel()) {
                //found the row and column indexes to reference this piece easily.
                pieceIndexRow = i;
                pieceIndexColumn = j;
            }
        }
    }

    //stores the next index location on the chess board to check if valid move possible or not.
    int potentialNewColumn;
    int potentialNewRow;

    //if the piece to have its possible moves calculated is a pawn. Pawns can only go straight in front if it 1 space, but for killing can only kill pieces diagionally in front of it with a distance of 1 space away from it.
    if (pieceToUpdate.getPieceName() == "Pawn") {
        //if it is a white pawn (goes top to bottom only) 
        if (pieceToUpdate.getPieceColor() == "White") {
            //checking for if white pawn can move down 1.

            potentialNewRow = pieceIndexRow + 1;
            //checks to see if within chess board and there is no piece in the way (for either black or white). If met, then this move is possible.
            if ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }

            //checking for if white pawn can kill a piece diagonally to the right of it (has to be black and cannot be a king)
            potentialNewColumn = pieceIndexColumn + 1;
            potentialNewRow = pieceIndexRow + 1;

            //if within bounds and there is a piece to kill of the opposite color only (cannot be a king), valid move.
            if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //else if king of opposite color, just set check flag
            if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

            //similarly, checking for if white pawn can kill a piece diagonally to the left of it (has to be black and cannot be a king)
            potentialNewColumn = pieceIndexColumn - 1;
            potentialNewRow = pieceIndexRow + 1;

            //if within bounds and there is a piece to kill of the opposite color only (cannot be a king), valid move.
            if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //else if king of opposite color, just set check flag
            if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }
        }
        //otherwise its a black pawn and goes bottom to top of chess board.
        else {
            //checking for if black pawn can move up 1.
            potentialNewRow = pieceIndexRow - 1;
            //checks to see if within chess board and there is no piece in the way (for either black or white). If met, then this move is possible.
            if ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }

            //checking for if black pawn can kill a piece diagonally to the right of it (has to be white and cannot be a king)
            potentialNewColumn = pieceIndexColumn + 1;
            potentialNewRow = pieceIndexRow - 1;

            //if within bounds and there is a piece to kill of the opposite color only (cannot be a king), valid move.
            if ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if it is a king of the opposite color, set checkflag (king is in check)
            if ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King"))
            {
                setCheckFlagWhite(true);
            }
            //similarly, checking for if black pawn can kill a piece diagonally to the left of it (has to be white and cannot be a king)
            potentialNewColumn = pieceIndexColumn - 1;
            potentialNewRow = pieceIndexRow - 1;

            //if within bounds and there is a piece to kill of the opposite color only (cannot be a king), valid move.
            if ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //set checkflag if opposite colored king there instead.
            if ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }

    }

    //if the current piece is a Rook, which can in a straight line in any direction.
    if (pieceToUpdate.getPieceName() == "Rook") {
        //initially set to the pieces current position, but down 1 space on the board. 
        potentialNewRow = pieceIndexRow + 1;

        //checks how far down the board it is possible to go in a straight line without out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            potentialNewRow++;

            //set checkflags for associated colors as well if opposite colored king blocks path. 

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow < CHESS_BOARD_ROWS)) {
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //set checkflag if king of opposite color "in the way".
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }
        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow < CHESS_BOARD_ROWS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //set check flag if white king blocking it.
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }
        //set to current piece position, but up 1 space on the board.
        potentialNewRow = pieceIndexRow - 1;

        //checks how far can go up board without going out of bounds or bumping into another piece.
        while ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            potentialNewRow--;

            //set checkflags for associated colors as well if opposite colored king blocks path. 

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

        }

        //if the piece being updated is white and still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //if black king blocking, set check flag to true.
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //if white king blocking, set check flag to true.
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }

        //original position of column but to the right 1.
        potentialNewColumn = pieceIndexColumn + 1;

        //checks how far right the piece can go while remaining in bounds and not bumping into any other chess piece.
        while ((potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            potentialNewColumn++;

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

        }

        //if the piece being updated is white and still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }

            //if black piece blocked it and it is a king, set checkflag to true.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }
            //if white king is in the way, set check flag to true.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //original position of column but to the left 1.
        potentialNewColumn = pieceIndexColumn - 1;

        //checks how far left the piece can go while remaining in bounds and not bumping into any other chess piece.
        while ((potentialNewColumn > 0) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            potentialNewColumn--;

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewColumn > 0) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewColumn > 0) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }
        }

        //if the piece being updated is white and still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewColumn > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }

            //if black piece blocked it and it is a king, set checkflag.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewColumn > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }

            //if a white king is blocking it, set checkflag.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }
    }

    //if the current piece selected is a Bishop. Bishops can move diagionally in any direction for as much spaces as they are able.
    if (pieceToUpdate.getPieceName() == "Bishop") {

        //initially set to the pieces current position, but diagionally down-right on the board by 1. 
        potentialNewRow = pieceIndexRow + 1;
        potentialNewColumn = pieceIndexColumn + 1;

        //checks how far down-right the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow++;
            potentialNewColumn++;

            //detection for if king of opposite color blocking way. If so, then set appropriate checkflag.

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if it is a black king blocking it, set checkflag to true.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if a white king is blocking it, set checkflag to true. 
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally down-left on the board by 1. 
        potentialNewRow = pieceIndexRow + 1;
        potentialNewColumn = pieceIndexColumn - 1;

        //checks how far up-right the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow++;
            potentialNewColumn--;

            //detection for if king of opposite color blocking way. If so, then set appropriate checkflag.

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }



        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //if black king blocking, set checkflag.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //if white king blocking, set checkflag
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally up-right on the board by 1. 
        potentialNewRow = pieceIndexRow - 1;
        potentialNewColumn = pieceIndexColumn + 1;

        //checks how far up-right the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow--;
            potentialNewColumn++;

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if black piece is a king, set checkflag
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if white piece is a king, set checkflag.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally up-left on the board by 1. 
        potentialNewRow = pieceIndexRow - 1;
        potentialNewColumn = pieceIndexColumn - 1;

        //checks how far up-left the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow--;
            potentialNewColumn--;

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow > 0) && (potentialNewColumn > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if black piece is king, set checkflag.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow > 0) && (potentialNewColumn > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if white piece is a king, set checkflag
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

    }

    //This is if the current piece selected was a Queen. The Queen can move like a Rook and a Bishop combined, thus logic from both Rook and Bishop is sufficient to represent this and shall be explicity shown here.
    if (pieceToUpdate.getPieceName() == "Queen") {

        //initially set to the pieces current position, but down 1 space on the board. 
        potentialNewRow = pieceIndexRow + 1;

        //checks how far down the board it is possible to go in a straight line without out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            potentialNewRow++;

            //set checkflags for associated colors as well if opposite colored king blocks path. 

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow < CHESS_BOARD_ROWS)) {
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //set checkflag if king of opposite color "in the way".
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }
        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow < CHESS_BOARD_ROWS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //set check flag if white king blocking it.
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }
        //set to current piece position, but up 1 space on the board.
        potentialNewRow = pieceIndexRow - 1;

        //checks how far can go up board without going out of bounds or bumping into another piece.
        while ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            potentialNewRow--;

            //set checkflags for associated colors as well if opposite colored king blocks path. 

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow > 0) && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

        }

        //if the piece being updated is white and still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //if black king blocking, set check flag to true.
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][pieceIndexColumn].nodeLabel);
            }
            //if white king blocking, set check flag to true.
            if ((chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }

        //original position of column but to the right 1.
        potentialNewColumn = pieceIndexColumn + 1;

        //checks how far right the piece can go while remaining in bounds and not bumping into any other chess piece.
        while ((potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            potentialNewColumn++;

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

        }

        //if the piece being updated is white and still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }

            //if black piece blocked it and it is a king, set checkflag to true.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }
            //if white king is in the way, set check flag to true.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //original position of column but to the left 1.
        potentialNewColumn = pieceIndexColumn - 1;

        //checks how far left the piece can go while remaining in bounds and not bumping into any other chess piece.
        while ((potentialNewColumn > 0) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            potentialNewColumn--;

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewColumn > 0) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewColumn > 0) && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }
        }

        //if the piece being updated is white and still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewColumn > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }

            //if black piece blocked it and it is a king, set checkflag.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewColumn > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[pieceIndexRow][potentialNewColumn].nodeLabel);
            }

            //if a white king is blocking it, set checkflag.
            if ((chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[pieceIndexRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally down-right on the board by 1. 
        potentialNewRow = pieceIndexRow + 1;
        potentialNewColumn = pieceIndexColumn + 1;

        //checks how far down-right the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow++;
            potentialNewColumn++;

            //detection for if king of opposite color blocking way. If so, then set appropriate checkflag.

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if it is a black king blocking it, set checkflag to true.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if a white king is blocking it, set checkflag to true. 
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally down-left on the board by 1. 
        potentialNewRow = pieceIndexRow + 1;
        potentialNewColumn = pieceIndexColumn - 1;

        //checks how far up-right the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow++;
            potentialNewColumn--;

            //detection for if king of opposite color blocking way. If so, then set appropriate checkflag.

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }



        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //if black king blocking, set checkflag.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow < CHESS_BOARD_ROWS) && (potentialNewColumn > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //if white king blocking, set checkflag
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally up-right on the board by 1. 
        potentialNewRow = pieceIndexRow - 1;
        potentialNewColumn = pieceIndexColumn + 1;

        //checks how far up-right the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow--;
            potentialNewColumn++;

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if black piece is a king, set checkflag
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow > 0) && (potentialNewColumn < CHESS_BOARD_COLS)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if white piece is a king, set checkflag.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //initially set to the pieces current position, but diagionally up-left on the board by 1. 
        potentialNewRow = pieceIndexRow - 1;
        potentialNewColumn = pieceIndexColumn - 1;

        //checks how far up-left the board it is possible to go without going out of bounds or bumping into another chess piece. All are valid moves if possible.
        while ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "EmptyString")) {
            pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            potentialNewRow--;
            potentialNewColumn--;

            if (pieceToUpdate.getPieceColor() == "Black") {
                if ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White")) {
                    setCheckFlagWhite(true);
                }
            }

            if (pieceToUpdate.getPieceColor() == "White") {
                if ((potentialNewRow > 0) && (potentialNewColumn > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black")) {
                    setCheckFlagBlack(true);
                }
            }

        }
        //if the piece being updated is white and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "White") && (potentialNewRow > 0) && (potentialNewColumn > 0)) {
            //if black piece blocked it, can also move to this spot since black piece can be killed (excluding King)
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if black piece is king, set checkflag.
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][pieceIndexColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the piece being updated is black and current position is still within bounds
        if ((pieceToUpdate.getPieceColor() == "Black") && (potentialNewRow > 0) && (potentialNewColumn > 0)) {
            //if white piece blocked it, can also move to this spot since white piece can be killed (excluding King).
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if white piece is a king, set checkflag
            if ((chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }
    }

    //if the selected piece is a horse. Horse can move in an any method that creates an "L shape".
    if (pieceToUpdate.getPieceName() == "Horse") {

        //potential L shape number 1.
        potentialNewRow = pieceIndexRow + 1;
        potentialNewColumn = pieceIndexColumn + 2;

        //if selected horse is white.
        if (pieceToUpdate.getPieceColor() == "White") {
            //as long as not same color piece or king is there and within bounds, acceptable move.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if there is a king there of the opposite color, set checkflag.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }


        }
        //if the horse was instead black
        if (pieceToUpdate.getPieceColor() == "Black") {
            //as long as not a king or same colored piece not there and within bounds, acceptable.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //if a white king is blocking, set checkflag.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }

        //potential L shape 2.
        potentialNewRow = pieceIndexRow + 2;
        potentialNewColumn = pieceIndexColumn + 1;

        //if selected horse white.
        if (pieceToUpdate.getPieceColor() == "White") {
            //if within bounds and no king or other same colored piece is there, acceptable move.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if black king blocking, set checkflag to true.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }

        //if horse was instead black
        if (pieceToUpdate.getPieceColor() == "Black") {
            //within bounds and no king or same colored piece there, acceptable move.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }
            //if a opposite colored king is there, set checkflag.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }
        }


        //potential L shape 3.
        potentialNewRow = pieceIndexRow - 1;
        potentialNewColumn = pieceIndexColumn + 2;

        //if white horse.
        if (pieceToUpdate.getPieceColor() == "White") {
            //within bounds and no king or same colored piece is there, acceptable move.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if there is an opposited colored king piece there, set checkflag
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }

        //if the horse piece is instead black.
        if (pieceToUpdate.getPieceColor() == "Black") {
            //within bounds and not same colored piece or a king. Acceptable move.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if within bounds and different colored king, set checkflag.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //potential L shape 4.
        potentialNewRow = pieceIndexRow + 1;
        potentialNewColumn = pieceIndexColumn - 2;

        //if the horse piece selected is white.
        if (pieceToUpdate.getPieceColor() == "White") {

            //if the horse piece selected is still within bounds and not a same colored piece or king blocking it, acceptable move.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if an opposite colored king there, set checkflag.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }

        //if the selected horse was black.
        if (pieceToUpdate.getPieceColor() == "Black") {
            //if the piece still in bounds and not same colored piece in the way, move possible.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if opposite colored king, set checkflag.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //potential L shape 5.
        potentialNewRow = pieceIndexRow - 2;
        potentialNewColumn = pieceIndexColumn + 1;

        //if the horse selected is white
        if (pieceToUpdate.getPieceColor() == "White") {
            //if still within bounds and no king or not a piece of same color there, can move there.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if a king of opposite color blocking, set checkflag.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }

        //otherwise if black colored horse.
        if (pieceToUpdate.getPieceColor() == "Black") {
            //if piece of opposite color and no king, and also within bounds then this is an acceptable move.
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if king of opposite color, set checkflag
            if ((potentialNewColumn < CHESS_BOARD_COLS) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //potential L shape 6.
        potentialNewRow = pieceIndexRow + 2;
        potentialNewColumn = pieceIndexColumn - 1;

        //if horse is white.
        if (pieceToUpdate.getPieceColor() == "White") {
            //if still within bounds and not same colored piece or king, acceptable move.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if different colored king,, then set checkflag.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }
        //if the horse piece is black.
        if (pieceToUpdate.getPieceColor() == "Black") {
            //if it is still within bounds and not blocked by a same colored piece or king, can move here.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if it is a king of a different color, set the checkflag.
            if ((potentialNewColumn > 0) && (potentialNewRow < CHESS_BOARD_ROWS) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //potential L shape 7.
        potentialNewRow = pieceIndexRow - 2;
        potentialNewColumn = pieceIndexColumn - 1;

        //if horse is white.
        if (pieceToUpdate.getPieceColor() == "White") {
            //if within bounds and not blocked by a king or a same colored piece, valid move.
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //else if king of different color, set checkflag. 
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }
        }
        //if horse is black.
        if (pieceToUpdate.getPieceColor() == "Black") {
            //if still within bounds and not blocked by same color or king, valid move
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //else if king of opposite color, check flag will be set.
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

        //potential L shape 8.
        potentialNewRow = pieceIndexRow - 1;
        potentialNewColumn = pieceIndexColumn - 2;

        //if horse is white.
        if (pieceToUpdate.getPieceColor() == "White") {
            //if still within bounds and not blocked by piece of same color or king, valid move.
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if a king of the opposite color, set checkflag
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagBlack(true);
            }

        }

        //if its a black horse.
        if (pieceToUpdate.getPieceColor() == "Black") {
            //if within bounds and not a king or a piece of the opposite color, valid move.
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() != "Black") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() != "King")) {
                pieceToUpdate.add(chessGrid[potentialNewRow][potentialNewColumn].nodeLabel);
            }

            //if a king of the opposite color, not necessarily a valid place to move to but still set the checkflag.
            if ((potentialNewColumn > 0) && (potentialNewRow > 0) && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceColor() == "White") && (chessGrid[potentialNewRow][potentialNewColumn].currPieceOnNode.getPieceName() == "King")) {
                setCheckFlagWhite(true);
            }

        }

    }

}
