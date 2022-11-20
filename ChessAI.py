import chess
import pygame
import numpy as np
import chess.svg
import io

pygame.init()

SQUARE_SIZE = 100
NUM_SQUARE = 8

SIZE = width, height = SQUARE_SIZE * NUM_SQUARE, SQUARE_SIZE * NUM_SQUARE 
screen = pygame.display.set_mode(SIZE)
surface = pygame.Surface((width,height), pygame.SRCALPHA)

board =  chess.Board()
selectedpiece = None

def DrawBoard():
    for i in range(NUM_SQUARE):
        for j in range(NUM_SQUARE):
            col = (238,238,210)
            if (i + j) % 2 == 1:
                col = (118,150,86)
            pygame.draw.rect(screen, col, pygame.Rect((i * SQUARE_SIZE), (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE))

def DrawPossibleMoves():
    piece = board.piece_at(chess.SQUARES[selectedpiece[0] + (selectedpiece[1] * 8)])
    all_moves = list(board.legal_moves)
    tomove = []

    for move in all_moves:
        if move.from_square == selectedpiece[0] + (selectedpiece[1] * 8):
            tomove.append(move.to_square)
    col = (0,0,0,100)
    for move in tomove:
        x = move % 8
        y = (move - x) / 8
        pygame.draw.circle(surface, col, (x * SQUARE_SIZE + 50,y * SQUARE_SIZE + 50), 50)
        screen.blit(surface, (0,0))
    pass


def DrawPieces():
    for i in range(NUM_SQUARE):
        for j in range(NUM_SQUARE):
            piece = board.piece_at(chess.SQUARES[i + (j * 8)])
            if piece != None:
                piecesvg = io.BytesIO(chess.svg.piece(chess.Piece.from_symbol(piece.symbol())).encode())
                image = pygame.image.load(piecesvg)
                screen.blit(image,(i * SQUARE_SIZE,j * SQUARE_SIZE))


def ProcessClick(selectedpiece):
    if selectedpiece == None:
        pos = pygame.mouse.get_pos()
        x = int(pos[0] / SQUARE_SIZE)
        y = int(pos[1] / SQUARE_SIZE)
        piece = board.piece_at(chess.SQUARES[x + (y * 8)])
        sp = None
        if piece != None:
            sp = [x,y]
        else:
            sp = None
        return sp
    else:
        pos = pygame.mouse.get_pos()
        x = int(pos[0] / SQUARE_SIZE)
        y = int(pos[1] / SQUARE_SIZE)
        pass
            

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            quit()
        if event.type == pygame.MOUSEBUTTONDOWN:
            selectedpiece = ProcessClick(selectedpiece)


    DrawBoard()
    if selectedpiece != None:
        DrawPossibleMoves()
    DrawPieces()    
    pygame.display.flip()
    surface = pygame.Surface((width,height), pygame.SRCALPHA)