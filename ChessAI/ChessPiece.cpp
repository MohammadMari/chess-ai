#include "ChessPiece.h"
#include <assert.h>

/*
ChessPiece::ChessPiece()
{
	pieceSide = NONE;
}

ChessPiece::ChessPiece(SIDE side) {
	pieceSide = side;
}

SIDE ChessPiece::GetSide()
{
	return pieceSide;
}

void ChessPiece::SetSide(SIDE side)
{
	pieceSide = side;
}

*/


//adds given string into the possibleMoves container.
void ChessPiece::add(string newPossibleMove) {
	this->possibleMoves.push_back(newPossibleMove);
	return;
}

//true if potentialMove found, else false if not.
bool ChessPiece::search(string potentialMove) {

	//iterates through container.
	for (unsigned int i = 0; i < this->possibleMoves.size(); i++) {
		//if possible move (found in container) then return true.
		if (this->possibleMoves.at(i) == potentialMove) {
			return true;
		}
	}
	//else, not a possible move so return false.
	return false;
}

//empties the entire possibleMoves container.
void ChessPiece::erase() {
	this->possibleMoves.clear();
	return;
}

//returns the current size of the possibleMoves container.
int ChessPiece::size() {
	return this->possibleMoves.size();
}

//sets the texture for the specified chess piece instance.
void ChessPiece::loadTexture() {
	//if the color associated with the game piece is white, load from white pool of textures.
	if (this->pieceColor == "White") {
		//if this is true, we need to load a white pawn texture.
		if (this->pieceName == "Pawn") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/pawnw.png")) {
				printf("pawnw error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Horse") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/knightw.png")) {
				printf("horsew error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Rook") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/rookw.png")) {
				printf("rookw error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Bishop") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/bishopw.png")) {
				printf("bishopw error\n");
				exit(0);
			}
		}

		if (this->pieceName == "King") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/kingw.png")) {
				printf("kingw error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Queen") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/queenw.png")) {
				printf("queenw error\n");
				exit(0);
			}
		}
	}
	//else, must be black so load from black pool of textures.
	else {
		if (this->pieceName == "Pawn") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/pawnb.png")) {
				printf("pawnb error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Horse") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/knightb.png")) {
				printf("knightb error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Rook") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/rookb.png")) {
				printf("rookb error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Bishop") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/bishopb.png")) {
				printf("bishopb error\n");
				exit(0);
			}
		}

		if (this->pieceName == "King") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/kingb.png")) {
				printf("kingb error\n");
				exit(0);
			}
		}

		if (this->pieceName == "Queen") {
			//if the texture cannot be found, print associated error and exit.
			if (!texture.loadFromFile("sprites/queenb.png")) {
				printf("queenb error\n");
				exit(0);
			}
		}
	}

}


/*
// Rook
Rook::Rook(SIDE side)
{
	pieceSide = side;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/rookw.png")) {
			printf("rookw error\n");
			exit(0);
		}
	} 
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/rookb.png")) {
			printf("rookb error\n");
			exit(0);
		}
	} 
	else {
		printf("rook error\n");
		exit(0);
	}
}

Bishop::Bishop(SIDE side)
{
	pieceSide = side;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/bishopw.png")) {
			printf("bishopw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/bishopb.png")) {
			printf("bishopb error\n");
			exit(0);
		}
	}
	else {
		printf("bishop error\n");
		exit(0);
	}
}

King::King(SIDE side)
{
	pieceSide = side;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/kingw.png")) {
			printf("kingw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/kingb.png")) {
			printf("kingb error\n");
			exit(0);
		}
	}
	else {
		printf("king error\n");
		exit(0);
	}
}

Queen::Queen(SIDE side)
{
	pieceSide = side;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/queenw.png")) {
			printf("queenw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/queenb.png")) {
			printf("queenb error\n");
			exit(0);
		}
	}
	else {
		printf("queen error\n");
		exit(0);
	}
}

Pawn::Pawn(SIDE side)
{
	pieceSide = side;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/pawnw.png")) {
			printf("pawnw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/pawnb.png")) {
			printf("pawnb error\n");
			exit(0);
		}
	}
	else {
		printf("king error\n");
		exit(0);
	}
}

Knight::Knight(SIDE side)
{
	pieceSide = side;
	if (pieceSide == WHITE) {
		if (!texture.loadFromFile("sprites/knightw.png")) {
			printf("knightw error\n");
			exit(0);
		}
	}
	else if (pieceSide == BLACK) {
		if (!texture.loadFromFile("sprites/knightb.png")) {
			printf("knightb error\n");
			exit(0);
		}
	}
	else {
		printf("pawn error\n");
		exit(0);
	}
}

*/
