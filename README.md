# chess-ai
Chess AI for CSCE 4201

## Python version
This is a chess game written in python that has an AI to play against. 

### Packages Used:
* __Note:__ Stockfish is used to evaluate the board state to give a numerical expression. Stockfish is located in CNN/Stockfish. To build Stockfish please read the [Stockfish Readme](https://github.com/official-stockfish/Stockfish#compiling-stockfish-yourself-from-the-sources)
```
pip install chess
pip install tensorflow
pip install numpy
pip install pygame
```

### To Run the Game: 
There are two way of running the game. You can either play against our AI or you can watch our AI play against Stockfish's AI. 

#### Play Against our AI
To play against our AI is pretty straight forward. Simply run ChessAI.py.
```
python3 ChessAI.py
```

#### Watch our AI play against Stockfish
To watch our AI play against Stockfish, you will first have to navigate to Stockfish src folder and make a local build of Stockfish. Once that is done, you can come back to the main directory and run AIvAI.py.
```
cd ./CNN/Stockfish/src
make net
make build
cd ../../..
python3 AIvAI.py
```

Note: If you plan to make a push to GitHub after building Stockfish, run make clean before the push. 
```
cd ./CNN/Stockfish/src
make clean
```


### Citations:
The data handeling into and from the model come from [Training a Chess AI using Tensorflow Article](https://medium.com/@nihalpuram/training-a-chess-ai-using-tensorflow-e795e1377af2). 
Source Code from the Article: [Chess-AI-with-Tensorflow](https://github.com/realnihal/Chess-AI-with-TensorFlow).
