#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


int main()
{
	ChessBoard board;
	RenderWindow window(sf::VideoMode(600, 600), "CHESS AI");
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		board.DisplayBoard(window);
		window.display();
	}
}