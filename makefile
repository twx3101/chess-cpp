OBJ = Chesspiece.o ChessBoard.o ChessMain.o
EXE = chess
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

Chesspiece.o : Chesspiece.h

ChessBoard.o : Chesspiece.h ChessBoard.h

ChessMain.o : Chesspiece.h ChessBoard.h

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean
