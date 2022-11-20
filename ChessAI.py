import chess
import pygame
import numpy as np
import chess.svg

#pygame.init()

SQUARE_SIZE = 100
NUM_SQUARE = 8
size = width, height = SQUARE_SIZE * NUM_SQUARE, SQUARE_SIZE * NUM_SQUARE 
#screen = pygame.display.set_mode(size)
board =  chess.Board()


# def DrawBoard():
#     for i in range(NUM_SQUARE):
#         for j in range(NUM_SQUARE):
#             col = (238,238,210)
#             if (i + j) % 2 == 1:
#                 col = (118,150,86)
#             pygame.draw.rect(screen, col, pygame.Rect((i * SQUARE_SIZE), (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE))

#             chess.svg.piece(chess.Piece.from_symbol("R"))  
            
while True: 
    chess.svg.board()

# while True:
#     for event in pygame.event.get():
#         if event.type == pygame.QUIT:
#             quit()
    
#     DrawBoard()
#     pygame.display.flip()

    