#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;



enum SIDE {
	NONE,
	WHITE,
	BLACK
};



using namespace sf;

/*
class ChessPiece {
public:
	ChessPiece();
	ChessPiece(SIDE side);
	SIDE GetSide();
	void SetSide(SIDE side);
	Texture GetTexture();


};
*/


//chess piece class that represents an instance of a chess piece.
class ChessPiece {
private:
    //either has values of "White" or "Black" (correlating to player)
    string pieceColor;
    //type of piece. Possible values are "Horse", "Rook", "Bishop", "Pawn", "Queen" and "King".
    string pieceName;
    //the current node that the chess piece instance is on (primary purpose is to uniquely identify an instance of a chess piece since every piece has unique location on chess board).
    string currNodeLabel;
    //stores the possible moves that can be made in string format (each value using chess notation for representing grid nodes, as in "A3" or etc).
    vector<string> possibleMoves;
    //defines the texture of the current chess piece.
    Texture texture;

public:
    //constructor that accepts values for pieceColor and pieceName, else emptyString assigned to indicate an empty instance of a chess piece.
    ChessPiece(string pieceColor = "EmptyString", string pieceName = "EmptyString", string currNodeLabel = "EmptyString") {
        this->pieceColor = pieceColor;
        this->pieceName = pieceName;
        this->currNodeLabel = currNodeLabel;
    }

    //gets and sets for pieceColor, pieceName and uniqueID.
    string getPieceColor() { return this->pieceColor; }
    void setPieceColor(string newValuePieceColor) { this->pieceColor = newValuePieceColor; }
    void setPieceName(string newPieceName) { this->pieceName = newPieceName; }
    string getPieceName() { return this->pieceName; }
    string GetCurrNodeLabel() { return this->currNodeLabel; }
    void setCurrNodeLabel(string newNodeLocation) { this->currNodeLabel = newNodeLocation; }

    //returns the chess pieces texture.
    Texture GetTexture() { return this->texture; }
    //sets the current chess pieces texture to the one specified by textureToSet.
    void setTexture(Texture textureToSet) { this->texture = textureToSet; }

    //called to intially load textures for a particular chessPiece instance. 
    void loadTexture();

    //these are functions that manage the possibleMoves container.

    //inserts new possible move into the possible move container (new grid node label).
    void add(string newPossibleMove);
    //checks whether if the potentialMove is a move that is possible to make for this piece or not by checking if it is within the possibleMoves container(returns true) or not (returns false).
    bool search(string potentialMove);
    //just erases everything currently in the container and sets it to zero in length.
    void erase();
    //returns the size of the possibleMoves container.
    int size();

    //used to test if possibleMovies has correct values for valid moves.
    void print() {
        for (unsigned int i = 0; i < possibleMoves.size(); i++) {
            cout << possibleMoves.at(i) << " ";
        }
        cout << endl;
    }

};


/*
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
*/
