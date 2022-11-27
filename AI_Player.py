from tensorflow.keras import models
import numpy as np
from CNN.CNNModel import split_dims


model = models.load_model('./CNN/Models/model02.h5')


def minmax_eval(board):
   board3D = split_dims(board)
   board3D = np.expand_dims(board3d, 0)
   return model(board3d)[0][0]

def minimax(board, depth, alpha, beta, maximizing_player):
  if depth == 0 or board.is_game_over():
    return minmax_eval(board)
  
  if maximizing_player:
    max_eval = -np.inf
    for move in board.legal_moves:
      board.push(move)
      eval = minimax(board, depth - 1, alpha, beta, False)
      board.pop()
      max_eval = max(max_eval, eval)
      alpha = max(alpha, eval)
      if beta <= alpha:
        break
    return max_eval
  else:
    min_eval = np.inf
    for move in board.legal_moves:
      board.push(move)
      eval = minimax(board, depth - 1, alpha, beta, True)
      board.pop()
      min_eval = min(min_eval, eval)
      beta = min(beta, eval)
      if beta <= alpha:
        break
    return min_eval


# this is the actual function that gets the move from the neural network
def get_ai_move(board, depth):
  max_move = None
  max_eval = -np.inf

  for move in board.legal_moves:
    board.push(move)
    eval = minimax(board, depth - 1, -np.inf, np.inf, False)
    board.pop()
    if eval > max_eval:
      max_eval = eval
      max_move = move
  
  return max_move