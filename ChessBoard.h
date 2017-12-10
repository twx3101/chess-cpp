#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Chesspiece.h"
#include <string>
#include <array>

using std::string;
using std::array;


class ChessBoard{
  public:
    /* Constructor */
    ChessBoard();

    /* Builds the chessboard */
    void buildBoard();

    /* Resets the chessboard */
    void resetBoard();

    /*print the current board to the screen */
    void print();

    /* Function that accepts 2 args of string type that checks if the moves
    submitted are valid, and if so, updates the board, if not returns an error*/
    void submitMove(string source_square, string destination_square);

    /*Check if the submitted moves are valid i.e only A-H and 1-8 are accepted */
    int check_valid_move(string source_square, string destination_square);

    /* Returns true if the move submitted is a valid castling move */
    bool check_castling(int source_rank, int source_file, int destination_rank, int destination_file);

    /* Updates the position of the rook after the castling move */
    void update_castling(int source_rank, int source_file, int destination_rank, int destination_file);

    /* Returns true if there is no piece blocking between the starting position
    of the piece and the destination piece or if the piece is a knight */
    bool check_piece_blocking(int source_rank, int source_file, int destination_rank, int destination_file);

    /*  Returns true if the submitted move leads to the current team's king being in check */
    bool in_check(int source_rank, int source_file, int destination_rank, int destination_file, Colour team);

    /* Returns true if the submitted move puts the opponent team's king in check */
    bool check_opponent(int checking_piece_rank, int checking_piece_file);

    /* Updates the board location once the submitted move has passed all checks */
    void update_board(int source_rank, int source_file, int destination_rank, int destination_file, ChessPiece* destination_piece);

    /*Updates the board location without changing the current location of the pieces.
    For checking future moves */
    void update_future(int source_rank, int source_file, int destination_rank, int destination_file, ChessPiece* destination_piece);

    /* returns true if the opponent team is in check and there are no more valid
    moves to be made */
    bool checkmate(Colour team);

    /* Returns the number of valid moves of a team */
    int generate_legal_moves(int source_rank, int source_file, Colour team);

    /* Converts an char (A-H) to int (0-7) */
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
