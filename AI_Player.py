from tensorflow.keras import models
import numpy as np
from CNN.dataPrep import split_dims

model = models.load_model('./CNN/Models/Black/blackModel02.h5')

def minmax_eval(board):
   # board3d = numpy.zeros((14, 8, 8), dtype=numpy.int8)
   board3d = split_dims(board)
   board3d = np.expand_dims(board3d, 0)
   return model(board3d)[0][0]

def minimax(board, depth, alpha, beta, maximizing_player):
  if depth == 0 or board.is_game_over():
    return minmax_eval(board)
  
  if maximizing_player:
    max_eval = -np.inf
    for move in board.legal_moves:
      board.push(move)
      # right here
      # make a list, compare with things of similar depth
      # if its like top 50% go ahead, if not just return.

      calc = minimax(board, depth - 1, alpha, beta, False)
      board.pop()
      max_eval = max(max_eval, calc)
      alpha = max(alpha, calc)
      if beta <= alpha:
        break
    return max_eval
  else:
    min_eval = np.inf
    for move in board.legal_moves:
      board.push(move)
      calc = minimax(board, depth - 1, alpha, beta, True)
      board.pop()
      min_eval = min(min_eval, calc)
      beta = min(beta, calc)
      if beta <= alpha:
        break
    return min_eval


# this is the actual function that gets the move from the neural network
def get_ai_move(board, depth):
  max_move = None
  max_eval = -np.inf

  for move in board.legal_moves:
    board.push(move)
    calc = minimax(board, depth - 1, -np.inf, np.inf, False)
    board.pop()
    if calc > max_eval:
      max_eval = calc
      max_move = move
  
  return max_move