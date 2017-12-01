
#include <string>;
#include <map>;

using std::string;

class ChessBoard{
  public:
    ChessBoard();
    void submitMove(string source_square, string destination_square);
    int check_valid_move(string source_square, string destination_square);
    void resetBoard();
    void print();
  private:
    array <array<ChessPiece*, 8> ,8 > chessboard;
    Colour turn;

};
