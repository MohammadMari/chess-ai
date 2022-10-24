#include "ChessPiece.h"
#include <assert.h>

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

Texture ChessPiece::GetTexture()
{
	return texture;
}


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
