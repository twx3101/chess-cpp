OBJ = Chesspiece.o Chessboard.o ChessMain.o
EXE = main
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

Chesspiece.o : Chesspiece.h

Chessboard.o : Chesspiece.h Chessboard.h

ChessMain.o : Chesspiece.h Chessboard.h

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean
