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
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					cout << "mouse x:" << event.mouseButton.x << endl;
					cout << "mouse y:" << event.mouseButton.y << endl;
					board.ProcessClickEvent(event.mouseButton.x, event.mouseButton.y);
				}
			}
		}

		board.DisplayBoard(window);
		window.display();
	}
}