import chess
import chess.engine
import random
import numpy as np


# this function will create our x (board)
def random_board(max_depth=20):
  board = chess.Board()
  depth = random.randrange(0, max_depth)

  for _ in range(depth):
    all_moves = list(board.legal_moves)
    random_move = random.choice(all_moves)
    board.push(random_move)
    if board.is_game_over():
      break

  return board

# This is used for board representation in an array
squares_index = {
  'a': 0,
  'b': 1,
  'c': 2,
  'd': 3,
  'e': 4,
  'f': 5,
  'g': 6,
  'h': 7
}


# Convert between board representation and array
def square_to_index(square):
  letter = chess.square_name(square)
  return 8 - int(letter[1]), squares_index[letter[0]]


# Creating the 2D represenation of the board
def split_dims(board):
  # this is the 3d matrix
  board3d = np.zeros((14, 8, 8), dtype=np.int8)

  # here we add the pieces's view on the matrix
  for piece in chess.PIECE_TYPES:
    for square in board.pieces(piece, chess.WHITE):
      idx = np.unravel_index(square, (8, 8))
      board3d[piece - 1][7 - idx[0]][idx[1]] = 1
    for square in board.pieces(piece, chess.BLACK):
      idx = np.unravel_index(square, (8, 8))
      board3d[piece + 5][7 - idx[0]][idx[1]] = 1

  # add attacks and valid moves too
  # so the network knows what is being attacked
  aux = board.turn
  board.turn = chess.WHITE
  for move in board.legal_moves:
      i, j = square_to_index(move.to_square)
      board3d[12][i][j] = 1
  board.turn = chess.BLACK
  for move in board.legal_moves:
      i, j = square_to_index(move.to_square)
      board3d[13][i][j] = 1
  board.turn = aux

  return board3d

# Creating the stockfish engine to rate our random boards
def stockfish_rater(board, depth):
   with chess.engine.SimpleEngine.popen_uci('Stockfish/src/stockfish') as sf:
      result = sf.analyse(board, chess.engine.Limit(depth=depth))
      score = result['score'].white().score()
   return score

# "C:/Users/tuffd/OneDrive/School/UNT/Fall_2022/Intro2AI/Project/chess-ai/ChessAI/CNN/Python/stockfish/13/bin/stockfish"

def main():
   iterations = 1000
   board_list = []
   score_list =[]
   for x in range(iterations):
      # Get the board
      board = random_board()
      # Convert and score
      np_arr = split_dims(board)
      score = stockfish_rater(board, 20)
      print("Iteration: ", x, "score: ", score)
      if (score == None):
        score = 0
        print('Updated Score from None to ', score)
      # Save to list
      board_list.append(np_arr)
      score_list.append(score)
   
   # Saviing the np list of np arrays to file
   np.savez('Dataset02', b=board_list, s=score_list)
   print('Dataset Created.')
       

if __name__ == "__main__":
    main()