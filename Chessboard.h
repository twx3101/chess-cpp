#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Chesspiece.h"
#include <string>
#include <array>

using std::string;
using std::array;


class ChessBoard{
  public:
    ChessBoard();
    void submitMove(string source_square, string destination_square);
    int check_valid_move(string source_square, string destination_square);
    bool check_piece_blocking(int source_rank, int source_file, int destination_rank, int destination_file);
    void update_board(int source_rank, int source_file, int destination_rank, int destination_file, ChessPiece* destination_piece);
    void update_future(int source_rank, int source_file, int destination_rank, int destination_file, ChessPiece* destination_piece);
    bool check_opponent(int checking_piece_rank, int checking_piece_file);
    bool checkmate(Colour team);
    void resetBoard();
    void buildBoard();
    void print();
    bool in_check(int source_rank, int source_file, int destination_rank, int destination_file, Colour team);
    int generate_legal_moves(int source_rank, int source_file, Colour team);
    int char_to_int(char a);
  private:
    array <array<ChessPiece*, 8> ,8 > chessboard;
    Colour turn;
    ChessPiece* graveyard[32];
    int dead;
    int b_king_rank;
    int b_king_file;
    int w_king_rank;
    int w_king_file;
    bool b_check;
    bool w_check;
    bool GameOver;

};

#endif
