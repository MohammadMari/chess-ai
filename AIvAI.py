import chess
import chess.engine
import time
import pygame
import random
import numpy as np
import chess.svg
import io
from AI_Player import get_ai_move

pygame.init()

SQUARE_SIZE = 100
NUM_SQUARE = 8

SIZE = width, height = SQUARE_SIZE * NUM_SQUARE, SQUARE_SIZE * NUM_SQUARE 
screen = pygame.display.set_mode(SIZE)
surface = pygame.Surface((width,height), pygame.SRCALPHA)

board =  chess.Board()
selectedpiece = None
firstMove = True

engine = chess.engine.SimpleEngine.popen_uci("./CNN/Stockfish/src/stockfish")

def DrawBoard():
    for i in range(NUM_SQUARE):
        for j in range(NUM_SQUARE):
            col = (238,238,210)
            if (i + j) % 2 == 1:
                col = (118,150,86)
            pygame.draw.rect(screen, col, pygame.Rect((i * SQUARE_SIZE), (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE))

def DrawPossibleMoves():
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
                image = pygame.transform.smoothscale(image, (40,40))
                screen.blit(image,(i * SQUARE_SIZE + 15,j * SQUARE_SIZE + 15))

    
def CheckStatus():
    if board.is_stalemate():
        return "STALEMATE"
    if board.is_insufficient_material():
        return "INSUFF"
    return board.outcome()
            


while True:
   for event in pygame.event.get():
      if event.type == pygame.QUIT:
         quit()
      
   DrawBoard()
   DrawPieces()    
   pygame.display.flip()
   surface = pygame.Surface((width,height), pygame.SRCALPHA)
   
   # Get first move as a random move (reduce repitition)
   if firstMove:
      firstMove = False
      all_moves = list(board.legal_moves)
      random_move = random.choice(all_moves)
      board.push(random_move)
      print('First Move: ', random_move)
   
   # Checking for game completeion
   outcome = CheckStatus()
   if outcome:
      # NEED TO UPDATE ALL THESE PRINTS TO DISPLAY TEXT ON GAME SCREEN
      # Winner = True means white won, false black won
      if outcome == "STALEMATE":
         print('Stalemate')
      if outcome == "INSUFF":
         print("Insufficient Materials")
      if outcome.termination:
         print(outcome)
         if outcome.winner:
            print('White Wins!')
         else:
            print('Black Wins!')
      
      # Sleeping for 5 seconds
      time.sleep(5)
      
      # Reset board and move stack
      board.clear()
      board.reset()
   
   # Getting our AI turn
   # board.turn; True = White; False = Black
   if board.turn is False and outcome == None:
      move = get_ai_move(board, 2)
      Nf3 = chess.Move.from_uci(str(move))
      board.push(Nf3)  # Make the move
      print("AI does: ", move)
      
   # Getting stockfish engine turn
   elif board.turn is True and outcome == None:
      result = engine.play(board, chess.engine.Limit(time=0.1))
      board.push(result.move)  # Make the move
      print("Stockfish does: ", result.move)
      time.sleep(1)
      