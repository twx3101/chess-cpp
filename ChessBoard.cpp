#include "Chesspiece.h"
#include "ChessBoard.h"


#include <iostream>

using std::cout;
using std::endl;
using std::cin;

ChessBoard::ChessBoard(){
  buildBoard();
}

void ChessBoard::buildBoard(){
  cout << "A new chess game is started!" << endl;
  turn = White;
  dead = 0;
  b_check = false;
  w_check = false;
  GameOver = false;

  int rank;
  int file;
  Colour t;

  b_king_rank = 7;
  b_king_file = 4;
  w_king_rank = 0;
  w_king_file = 4;

  for(rank = 0; rank < 8; rank++){
      for(file = 0; file < 8; file++){
        if (rank == 0 || rank == 7){
          if (rank == 0){
           t = White;
         }
          else{
           t = Black;
         }

            switch(file){
              case 0:
              chessboard[rank][0] = new Rook(t, "Rook", rank, 0);
              case 1:
              chessboard[rank][1] = new Knight(t, "Knight", rank, 1);
              case 2:
              chessboard[rank][2] = new Bishop(t, "Bishop", rank, 2);
              case 3:
              chessboard[rank][3] = new Queen(t, "Queen", rank, 3);
              case 4:
              chessboard[rank][4] = new King(t, "King", rank, 4);
              case 5:
              chessboard[rank][5] = new Bishop(t, "Bishop", rank, 5);
              case 6:
              chessboard[rank][6] = new Knight(t, "Knight", rank, 6);
              case 7:
              chessboard[rank][7] = new Rook(t, "Rook", rank, 7);
            }
          }


        else if (rank == 1 || rank == 6){
          if (rank == 1){
           t = White;
         }
          else{
           t = Black;
        }
        chessboard[rank][file] = new Pawn(t, "Pawn", rank, file);
      }

      else{
        chessboard[rank][file] = NULL;
      }
    }
  }
  //print();
}


void ChessBoard::resetBoard(){
  for (int i = 0; i<8; i++){
    for(int j = 0; j<8; j++){
      if (chessboard[i][j] != NULL){
        delete chessboard[i][j];
      }
    }
  }
  for (int k = 0; k < dead; k++){
    delete graveyard[k];
  }
  buildBoard();
}


 void ChessBoard::print(){
  int col;
  int row;
  cout << endl << "      ======================================================================================================== \n\n" ;
  for(col = 7; col >= 0; col--){
      for(row = 0; row < 8; row++){
        if (chessboard[col][row] == NULL ){
          cout.width(14);
          cout <<  "NULL ";
        }
        else{
        cout.width(10);
        cout << chessboard[col][row]->get_name() << " ";
        cout.width(2);
        cout << chessboard[col][row]->get_team() << " ";
      }
    }
    cout <<"\n\n\n\n\n";
  }
cout <<  "      ======================================================================================================= \n\n";
}

void ChessBoard::submitMove(string source_square, string destination_square){
  bool valid;
  bool castling = false;
  int source_rank;
  int source_file;
  int destination_rank;
  int destination_file;

  if (GameOver == true){
    cout << "Game has ended, please restart a new game.\n";
    return;
  }

  //check if submitted moves are valid (A-H and 1-8)
  if (check_valid_move(source_square, destination_square) > 0){
    return;
  }

  source_rank = (source_square[1] - '0') - 1; //converts rank to int
  source_file = char_to_int(source_square[0]); //converts file to int

  destination_rank = (destination_square[1] - '0') - 1;
  destination_file = char_to_int(destination_square[0]);

  ChessPiece* source_piece = chessboard[source_rank][source_file];
  ChessPiece* destination_piece = chessboard[destination_rank][destination_file];

  if (source_piece == NULL){
    cout << "There is no piece at position " << source_square << "!" << endl;
    return;
  }

  if (source_piece->get_team() != turn){
    if (turn == White){
      cout << "It is not Black's turn to move!\n";
    }
    else
      cout << "It is not White's turn to move!\n";
    return;
  }

  if(destination_piece != NULL && destination_piece->get_team() == turn){
    cout << source_piece << " cannot move to " << destination_square << "!\n";
    return;
  }

  // check if piece can move to its destination due to its class
  valid = source_piece->move(destination_rank, destination_file, destination_piece);

  //check castling
  if (source_piece->get_type() == KING){
    if (source_piece->get_first_move() == true && source_rank == destination_rank && abs(destination_file - source_file) == 2){
      castling = check_castling(source_rank, source_file, destination_rank, destination_file);
      //if (castling == true){
      //  valid = true;
    //  }
    }
  }

  // if move is valid
  if (valid == true){
    // if piece is not blocking or castling is true
    if(check_piece_blocking(source_rank, source_file, destination_rank, destination_file) || castling == true){
      // if move puts king in check
      if(in_check(source_rank, source_file, destination_rank, destination_file, turn)){
        cout << "Your king is still in check! Invalid move" << endl;
        return;
      }
      else{
        if(destination_piece == NULL && castling == false){
        update_board(source_rank, source_file, destination_rank, destination_file, destination_piece);
        cout << chessboard[destination_rank][destination_file] << " moves from " << source_square << " to " << destination_square << endl;
        }
        else if(destination_piece != NULL && castling == false){
          update_board(source_rank, source_file, destination_rank, destination_file, destination_piece);
          cout << chessboard[destination_rank][destination_file] << " moves from " << source_square << " to " <<
          destination_square << " taking " << graveyard[dead-1] << endl;
        }
        else if(castling == true){
          update_board(source_rank, source_file, destination_rank, destination_file, destination_piece);
          cout << chessboard[destination_rank][destination_file] << " moves from " << source_square << " to " << destination_square << " via castling move."<< endl;
          update_castling(source_rank, source_file, destination_rank, destination_file);
        }

        if(source_piece->get_team() == White && check_opponent(destination_rank, destination_file)){
          b_check = true;

          if (checkmate(Black)){
              GameOver = true;
              cout << "Black is in checkmate\n";
            }

          else{
          cout << "Black is in check" << endl;
          }
        }
        else if (source_piece->get_team() == Black && check_opponent(destination_rank, destination_file)){
          w_check = true;
          if (checkmate(White)){
              GameOver = true;
              cout << "White is in checkmate\n";
            }
          else{
          cout << "White is in check" << endl;
            }
          }
        }
      }
    else{
      cout << source_piece << " cannot move to " << destination_square << "!\n";
      return;
    }
  }
  else{
    cout << source_piece << " cannot move to " << destination_square << "!\n";
    return;
  }

  // if black and white are not in check and there are no more legal moves
  if ((turn == White && b_check ==false && checkmate(Black)) || (turn == Black && w_check == false && checkmate(White))){
    GameOver = true;
    cout << "Stalemate! no more moves remaining \n";
  }

  if (turn == White){
    turn = Black;
  }
  else{
    turn = White;
  }

  return;

}

int ChessBoard::check_valid_move(string source_square, string destination_square){
  if (source_square.length() != 2 || destination_square.length() != 2){
    cout << "Moves must be entered in the format file(A-H) and rank(1-8)." << endl;
    return 1;
  }

  if (char_to_int(source_square[0]) < 0 || char_to_int(source_square[0]) > 7
  || char_to_int(destination_square[0]) < 0 || char_to_int(destination_square[0]) > 7){

    cout << "File must be entered in the format(A-H)" << endl;
    return 2;

  }

  if((source_square[1] - '0') < 1 || (source_square[1] - '0') > 8
  || (destination_square[1]) - '0' < 1 || (destination_square[1] - '0') > 8 ){

    cout << "Rank must be entered in the format (1-8)" << endl;
    return 3;

  }
  return 0;
}

bool ChessBoard::check_castling(int source_rank, int source_file, int destination_rank, int destination_file){
  if (chessboard[destination_rank][destination_file] != NULL){
    return false;
  }
  ChessPiece* source_piece = chessboard[source_rank][source_file];

  //long castling white king
  if (source_piece->get_type() == KING && source_piece->get_team() == White && chessboard[0][0] != NULL &&
  chessboard[0][0]->get_type() == ROOK && chessboard[0][0]->get_first_move() == true && w_check == false){
    if ((destination_rank == source_rank) && (source_file - destination_file == 2)){
      if(check_piece_blocking(source_rank, source_file, destination_rank, destination_file) &&
    check_piece_blocking(0,0,0,3) && !in_check(source_rank,source_file, source_rank, source_file-1, White)){
        return true;
      }
    }
  }

  //short castling white king
  if (source_piece->get_type() == KING && source_piece->get_team() == White && chessboard[0][7] != NULL &&
  chessboard[0][7]->get_type() == ROOK && chessboard[0][7]->get_first_move() == true && w_check == false){
    if ((destination_rank == source_rank) && (destination_file - source_file == 2)){
      if(check_piece_blocking(source_rank, source_file, destination_rank, destination_file) &&
    check_piece_blocking(0,7,0,5) && !in_check(source_rank,source_file, source_rank, source_file+1, White)){
        return true;
      }
    }
  }

  //long castling for black king
  if (source_piece->get_type() == KING && source_piece->get_team() == Black && chessboard[7][0] != NULL &&
  chessboard[7][0]->get_type() == ROOK && chessboard[7][0]->get_first_move() == true && b_check == false){
    if ((destination_rank == source_rank) && (source_file - destination_file == 2)){
      if( check_piece_blocking(source_rank, source_file, destination_rank, destination_file) &&
    check_piece_blocking(7,0,7,3) && !in_check(source_rank,source_file, source_rank, source_file-1, Black)){
        return true;
      }
    }
  }

  //short castling for black king
  if (source_piece->get_type() == KING && source_piece->get_team() == Black && chessboard[7][7] != NULL &&
  chessboard[7][7]->get_type() == ROOK && chessboard[7][7]->get_first_move() == true && b_check == false){
    if ((destination_rank == source_rank) && (destination_file - source_file == 2)){
      if(check_piece_blocking(source_rank, source_file, destination_rank, destination_file) &&
    check_piece_blocking(7,7,7,5) && !in_check(source_rank,source_file, source_rank, source_file+1, Black) ){
        return true;
      }
    }
  }

  return false;
}


bool ChessBoard::check_piece_blocking(int source_rank, int source_file, int destination_rank, int destination_file){

  if(chessboard[destination_rank][destination_file] != NULL && chessboard[destination_rank][destination_file]->get_team() == chessboard[source_rank][source_file]->get_team() ){
    return false;
  }

  if (chessboard[source_rank][source_file]->get_type() == KNIGHT){
    return true;
  }

  //right
  if (source_rank == destination_rank){
    if ((destination_file - source_file) > 0){
      for (int i = 1; i < (destination_file - source_file); i++){
        if (chessboard[source_rank][source_file + i] != NULL){
          return false;
        }
      }
    }
    //left
    else if ((destination_file - source_file) < 0){
      for (int i = 1; i < (source_file - destination_file); i++){
        if (chessboard[source_rank][source_file - i] != NULL){
          return false;
        }
      }
    }
  }

  //up
  if (source_file == destination_file){
    if ((destination_rank - source_rank) > 0){
      for (int i = 1; i < (destination_rank - source_rank); i++){
        if (chessboard[source_rank + i][source_file] != NULL){
          return false;
        }
      }
    }
    //down
    else if ((destination_rank - source_rank) < 0){
      for (int i = 1; i < (source_rank - destination_rank); i++){
        if (chessboard[source_rank - i][source_file] != NULL){
          return false;
        }
      }
    }
  }

  //diagonal up right
  if (destination_rank - source_rank > 0 && destination_file - source_file > 0){
    for (int i = 1; i < (destination_rank - source_rank); i++){
      if (chessboard[source_rank + i][source_file + i] != NULL){
        return false;
      }
    }
  }

  //diagonal down right
  if (destination_rank - source_rank < 0 && destination_file - source_file > 0){
    for (int i = 1; i < (source_rank - destination_rank); i++){
      if (chessboard[source_rank - i][source_file + i] != NULL){
        return false;
      }
    }
  }

  //diagonal up left
  if (destination_rank - source_rank > 0 && destination_file - source_file < 0){
    for (int i = 1; i < (destination_rank - source_rank); i++){
      if (chessboard[source_rank + i][source_file - i] != NULL){
        return false;
      }
    }
  }
  //diagonal down left
  if (destination_rank - source_rank < 0 && destination_file - source_file < 0){
    for (int i = 1; i < (source_rank - destination_rank); i++){
      if (chessboard[source_rank - i][source_file - i] != NULL){
        return false;
      }
    }
  }

  return true;
}

void ChessBoard::update_board(int source_rank, int source_file, int destination_rank, int destination_file, ChessPiece* destination_piece){
  if (destination_piece == NULL){
  chessboard[source_rank][source_file]->update_current_location(destination_rank, destination_file);
  chessboard[destination_rank][destination_file] = chessboard[source_rank][source_file];
  chessboard[source_rank][source_file] = NULL;
  }
  else{
    graveyard[dead] = chessboard[destination_rank][destination_file];
    chessboard[source_rank][source_file]->update_current_location(destination_rank, destination_file);
    chessboard[destination_rank][destination_file] = chessboard[source_rank][source_file];
    chessboard[source_rank][source_file] = NULL;
    dead++;
  }

  if (chessboard[destination_rank][destination_file]->get_type() == KING || chessboard[destination_rank][destination_file]->get_type() == ROOK ){
    if (chessboard[destination_rank][destination_file]->get_first_move() == true){
      chessboard[destination_rank][destination_file]->set_first_move();
      }
    }

// sets check to false if move is valid because it moves King out of check if
// all tests are passsed
  if (turn == White && w_check == true){
      w_check = false;
    }
  else if (b_check == true && turn == Black){
      b_check = false;
    }
}

void ChessBoard::update_castling(int source_rank, int source_file, int destination_rank, int destination_file){
  if (source_rank == 0){
    if (destination_file == 2){
      chessboard[0][0]->update_current_location(0, 3);
      chessboard[0][3] = chessboard[0][0];
      chessboard[0][0] = NULL;
      chessboard[0][3]->set_first_move();
    }
    else{
      chessboard[0][7]->update_current_location(0, 5);
      chessboard[0][5] = chessboard[0][7];
      chessboard[0][7] = NULL;
      chessboard[0][5]->set_first_move();
    }
  }
  if (source_rank == 7){
    if (destination_file == 2){
      chessboard[7][0]->update_current_location(7, 3);
      chessboard[7][3] = chessboard[7][0];
      chessboard[7][0] = NULL;
      chessboard[7][3]->set_first_move();
    }
    else{
      chessboard[7][7]->update_current_location(7, 5);
      chessboard[7][5] = chessboard[7][7];
      chessboard[7][7] = NULL;
      chessboard[7][5]->set_first_move();
    }
  }

}

void ChessBoard::update_future(int source_rank, int source_file, int destination_rank, int destination_file, ChessPiece* destination_piece){
  chessboard[destination_rank][destination_file] = chessboard[source_rank][source_file];
  chessboard[source_rank][source_file] = NULL;
}


bool ChessBoard::in_check(int source_rank, int source_file, int destination_rank, int destination_file, Colour team){


  array<array<ChessPiece*, 8>, 8> current_chessboard;
  current_chessboard = chessboard;
  ChessPiece* source_piece = chessboard[source_rank][source_file];
  ChessPiece* destination_piece = chessboard[destination_rank][destination_file];
  int current_k_rank = source_rank;
  int current_k_file = source_file;

//if moving piece is white king
  if (source_piece->get_type() == KING && source_piece->get_team() == White){

    w_king_rank = destination_rank;
    w_king_file = destination_file;
  }
  //if moving piece is white king
  else if(source_piece->get_type() == KING && source_piece->get_team() == Black){
    b_king_rank = destination_rank;
    b_king_file = destination_file;
  }

  // updates board for future move
  update_future(source_rank, source_file, destination_rank, destination_file, destination_piece);

  //check if future board will lead to king in check
  for(int rank = 0; rank < 8; rank++){
    for (int file = 0; file < 8; file++){
      if (chessboard[rank][file] != NULL && chessboard[rank][file]->get_team()!= team){
        if (check_opponent(rank, file)){
          if (source_piece->get_type() == KING && source_piece->get_team() == White){
            //reset king position
            w_king_rank = current_k_rank;
            w_king_file = current_k_file;
          }
          else if(source_piece->get_type() == KING && source_piece->get_team() == Black){
            //reset king position
            b_king_rank = current_k_rank;
            b_king_file = current_k_file;
          }
          //reset board to before move was made
          chessboard = current_chessboard;
          return true; //if move leads to king still in check invalid move
        }
      }

    }
  }
  chessboard = current_chessboard; //reset board
  return false; //valid move
}

bool ChessBoard::check_opponent(int checking_piece_rank, int checking_piece_file){
  ChessPiece* source_piece = chessboard[checking_piece_rank][checking_piece_file];


  if (source_piece->get_team() == White){
    ChessPiece* B_King = chessboard[b_king_rank][b_king_file];
    if(source_piece->move(b_king_rank, b_king_file, B_King) && check_piece_blocking(checking_piece_rank, checking_piece_file, b_king_rank, b_king_file)){
      return true; // if moving to opponent's king position is valid, return true
    }
  }
  if (source_piece->get_team() == Black){
    ChessPiece* W_King = chessboard[w_king_rank][w_king_file];
    if(source_piece->move(w_king_rank, w_king_file, W_King) && check_piece_blocking(checking_piece_rank, checking_piece_file, w_king_rank, w_king_file)){
      return true;
    }
  }
  return false;
}

bool ChessBoard::checkmate(Colour team){
  int legal_moves = 0;
  for (int rank = 0; rank < 8; rank++){
    for(int file = 0; file < 8; file++){
      if (chessboard[rank][file] != NULL && chessboard[rank][file]->get_team() != turn){
        legal_moves += generate_legal_moves(rank, file, team);
        if (legal_moves > 0){
          break;
        }
      }
    }
  }
  if (legal_moves == 0){
    return true;
  }
  else{
    return false;
  }
}

int ChessBoard::generate_legal_moves(int source_rank, int source_file, Colour team){
  int legal_moves = 0;
  ChessPiece* source_piece = chessboard[source_rank][source_file];
  ChessPiece* destination_piece;
  for (int rank = 0; rank < 8; rank++){
    for(int file = 0; file < 8; file++){
      destination_piece = chessboard[rank][file];
      if(source_piece->move(rank, file, destination_piece) && check_piece_blocking(source_rank, source_file, rank, file) && !in_check(source_rank, source_file, rank, file, team))
      // check if move can put king out of check
      legal_moves += 1;
    }
  }
  return legal_moves;
}

int ChessBoard::char_to_int(char a){
  int i;
  i = static_cast<int>(a - 65);
  return i;
}
