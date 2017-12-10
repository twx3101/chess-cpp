#include <string>
#include <array>
#include <iostream>

enum Colour{White, Black};
enum Type{KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE};
using namespace std;

int char_to_int(char a);

class ChessPiece{
  public:
    ChessPiece(Colour bw, string _name, int rank, int file);
    Colour get_team();
    virtual bool move(int destination_rank, int destination_file, ChessPiece* destination_piece){return false;}
    void update_current_location(int destination_rank, int destination_file);
    virtual Type get_type(){return NONE;}
    friend ostream& operator <<(ostream& o, const ChessPiece* a);

  protected:
      Colour team;
      string name;
      int current_rank;
      int current_file;
};

class King: public ChessPiece{
  public:
    King(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece);
    Type get_type(){
      return KING;
    }
  private:
};

class Queen: public ChessPiece{
  public:
    Queen(Colour bw, string _name,int rank, int file): ChessPiece(bw, _name, rank, file){};
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece);
    Type get_type(){
      return QUEEN;
    }
  private:

};

class Rook: public ChessPiece{
  public:
    Rook(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece);
    Type get_type(){
      return ROOK;
    }
  private:

};

class Knight: public ChessPiece{
  public:
    Knight(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece);
    Type get_type(){
      return KNIGHT;
    }
  private:

};

class Bishop: public ChessPiece{
  public:
    Bishop(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece);
    Type get_type(){
      return BISHOP;
    }
  private:

};

class Pawn: public ChessPiece{
  public:
    Pawn(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece);
    Type get_type(){
      return PAWN;
    }
  private:

};
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
    void print();
    bool in_check(int source_rank, int source_file, int destination_rank, int destination_file, Colour team);
    int generate_legal_moves(int source_rank, int source_file, Colour team);
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



int main(){
  ChessBoard cb;
  cb.print();
  cb.submitMove("F6", "G6");

  return 0;
}


ChessBoard::ChessBoard(){
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
              chessboard[rank][0] = new Rook(t, "Rook1", rank, 0);
              case 1:
              chessboard[rank][1] = new Knight(t, "Knight1", rank, 1);
              case 2:
              chessboard[rank][2] = new Bishop(t, "Bishop1", rank, 2);
              case 3:
              chessboard[rank][3] = new Queen(t, "Queen", rank, 3);
              case 4:
              chessboard[rank][4] = new King(t, "King", rank, 4);
              case 5:
              chessboard[rank][5] = new Bishop(t, "Bishop2", rank, 5);
              case 6:
              chessboard[rank][6] = new Knight(t, "Knight2", rank, 6);
              case 7:
              chessboard[rank][7] = new Rook(t, "Rook2", rank, 7);
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
  /*cout << "A new chess game is started!" << endl;

    turn = White;
    dead = 0;
    b_check = false;
    w_check = false;
    GameOver = false;

    int rank;
    int file;
    Colour t;

    b_king_rank = 7;
    b_king_file = 7;
    w_king_rank = 6;
    w_king_file = 5;

    for(rank = 0; rank < 8; rank++){
        for(file = 0; file < 8; file++){
          if (rank == 7 && file == 7){
            chessboard[rank][file] = new King(Black, "King", rank, file);
          }
          else if (rank == 6 && file == 5){
            chessboard[rank][file] = new King(White, "King", rank, file);
          }
          else if(rank == 5 && file == 5){
            chessboard[rank][file] = new Queen(White, "Queen", rank, file);
          }
          else{
            chessboard[rank][file] = NULL;
          }
        }
      }*/
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
        cout <<  chessboard[col][row] << " ";
      }
    }
    cout <<"\n\n\n\n\n";
  }
cout <<  "      ======================================================================================================= \n\n";
}

void ChessBoard::submitMove(string source_square, string destination_square){
  bool valid;
  int error_code;
  int source_rank;
  int source_file;
  int destination_rank;
  int destination_file;

  if (GameOver == true){
    cout << "Game has ended, please restart a new game.\n";
    return;
  }

  error_code = check_valid_move(source_square, destination_square);
  if (error_code > 0){
    return;
  }

  source_rank = (source_square[1] - '0') - 1;
  source_file = char_to_int(source_square[0]);

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
      cout << "It is not Black's turn to move!.\n";
    }
    else
      cout << "It is not White's turn to move!.\n";
    return;
  }
  if(destination_piece != NULL && destination_piece->get_team() == turn){
    cout << "You cannot move to " << destination_square << " which is occupied by a friendly piece\n";
    return;
  }

  valid = source_piece->move(destination_rank, destination_file, destination_piece);

  if (valid == true){
    if(check_piece_blocking(source_rank, source_file, destination_rank, destination_file)){
      if(in_check(source_rank, source_file, destination_rank, destination_file, turn)){
        cout << "Your king is still in check! Invalid move" << endl;
        return;
      }
      else{
        update_board(source_rank, source_file, destination_rank, destination_file, destination_piece);
        cout << "Piece moves from " << source_square << " to " << destination_square << endl;

        if(source_piece->get_team() == White && check_opponent(destination_rank, destination_file)){
          cout << "Black is in check!" << endl;
          b_check = true;
        }
        else if (source_piece->get_team() == Black && check_opponent(destination_rank, destination_file)){
          cout << "White is in check!" << endl;
          w_check = true;
        }
      }
    }
    else{
      cout << "Can't jump ahead of piece " << source_square << " to " << destination_square << endl;
      return;
    }
  }
  else{
    cout << "Invalid move\n";
    return;
  }

  if (w_check == true){
    if (checkmate(White)){
      cout << "Checkmate! Black wins! \n";
      GameOver = true;
    }
  }
  else if (b_check == true){
    if (checkmate(Black)){
      GameOver = true;
      cout << "Checkmate! White wins! \n";
    }
  }
  else if ((turn == White && checkmate(Black)) || (turn == Black && checkmate(White))){
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

bool ChessBoard::check_piece_blocking(int source_rank, int source_file, int destination_rank, int destination_file){

  if(chessboard[destination_rank][destination_file] != NULL && chessboard[destination_rank][destination_file]->get_team() == chessboard[source_rank][source_file]->get_team() ){
    return false;
  }

  if (chessboard[source_rank][source_file]->get_type() == KNIGHT){
    return true;
  }

  if (source_rank == destination_rank){
    if ((destination_file - source_file) > 0){
      for (int i = 1; i < (destination_file - source_file); i++){
        if (chessboard[source_rank][source_file + i] != NULL){
          return false;
        }
      }
    }
    else if ((destination_file - source_file) < 0){
      for (int i = 1; i < (source_file - destination_file); i++){
        if (chessboard[source_rank][source_file - i] != NULL){
          return false;
        }
      }
    }
  }

  if (source_file == destination_file){
    if ((destination_rank - source_rank) > 0){
      for (int i = 1; i < (destination_rank - source_rank); i++){
        if (chessboard[source_rank + i][source_file] != NULL){
          return false;
        }
      }
    }
    else if ((destination_rank - source_rank) < 0){
      for (int i = 1; i < (source_rank - destination_rank); i++){
        if (chessboard[source_rank - i][source_file] != NULL){
          return false;
        }
      }
    }
  }

  if (destination_rank - source_rank > 0 && destination_file - source_file > 0){
    for (int i = 1; i < (destination_rank - source_rank); i++){
      if (chessboard[source_rank + i][source_file + i] != NULL){
        return false;
      }
    }
  }

  if (destination_rank - source_rank < 0 && destination_file - source_file > 0){
    for (int i = 1; i < (source_rank - destination_rank); i++){
      if (chessboard[source_rank - i][source_file + i] != NULL){
        return false;
      }
    }
  }

  if (destination_rank - source_rank > 0 && destination_file - source_file < 0){
    for (int i = 1; i < (destination_rank - source_rank); i++){
      if (chessboard[source_rank + i][source_file - i] != NULL){
        return false;
      }
    }
  }
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


  char ans;
  cout << "Print?\n";
  cin >> ans;
  if (ans == 'y'){
    print();
  }
  if (turn == White && w_check == true){
      w_check = false;
    }
  else if (b_check == true && turn == Black){
      b_check = false;
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


  if (source_piece->get_type() == KING && source_piece->get_team() == White){

    w_king_rank = destination_rank;
    w_king_file = destination_file;
  }
  else if(source_piece->get_type() == KING && source_piece->get_team() == Black){
    b_king_rank = destination_rank;
    b_king_file = destination_file;
  }

  update_future(source_rank, source_file, destination_rank, destination_file, destination_piece);

  for(int rank = 0; rank < 8; rank++){
    for (int file = 0; file < 8; file++){
      if (chessboard[rank][file] != NULL && chessboard[rank][file]->get_team()!= team){
        if (check_opponent(rank, file)){
          if (source_piece->get_type() == KING && source_piece->get_team() == White){
            w_king_rank = current_k_rank;
            w_king_file = current_k_file;
          }
          else if(source_piece->get_type() == KING && source_piece->get_team() == Black){
            b_king_rank = current_k_rank;
            b_king_file = current_k_file;
          }
          chessboard = current_chessboard;
          return true;
        }
      }

    }
  }
  chessboard = current_chessboard;
  return false;
}

bool ChessBoard::check_opponent(int checking_piece_rank, int checking_piece_file){
  ChessPiece* source_piece = chessboard[checking_piece_rank][checking_piece_file];


  if (source_piece->get_team() == White){
    ChessPiece* B_King = chessboard[b_king_rank][b_king_file];
    if(source_piece->move(b_king_rank, b_king_file, B_King) && check_piece_blocking(checking_piece_rank, checking_piece_file, b_king_rank, b_king_file)){
      return true;
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
      legal_moves += 1;
    }
  }
  return legal_moves;
}

ChessPiece::ChessPiece(Colour bw, string _name, int rank, int file) : team(bw), name(_name), current_rank(rank), current_file(file){};

Colour ChessPiece::get_team(){
  return team;
}

void ChessPiece::update_current_location(int destination_rank, int destination_file){
  current_rank = destination_rank;
  current_file = destination_file;
}



ostream& operator <<(ostream& o, const ChessPiece* a){
  o.width(10);
  o << a->name << " ";
  o.width(2);
  o << a->team;
  return o;
}

bool Pawn::move(int destination_rank, int destination_file, ChessPiece* destination_piece){


  if (team == White && current_rank == 1){
    if ((destination_rank - current_rank  == 2) && (destination_file == current_file) && destination_piece == NULL){
      return true;
    }
  }
  else if (team == Black && current_rank == 6){
    if((current_rank - destination_rank == 2) && (destination_file == current_file) && destination_piece == NULL) {
      return true;
    }
  }


  if ((team ==  White) && (destination_rank - current_rank) == 1  && (destination_file == current_file) && destination_piece == NULL) {
    return true;
  }
  if ((team ==  Black) && (current_rank - destination_rank ) == 1 && (destination_file == current_file) && destination_piece == NULL) {
    return true;
  }

  if (destination_piece != NULL && destination_piece->get_team() != team){
    if (team == White && (destination_rank - current_rank) == 1  &&  ((destination_file - current_file) == 1 || current_file - destination_file == 1)){
      return true;
    }
    if (team == Black && (current_rank - destination_rank) == 1  &&  ((destination_file - current_file) == 1 || current_file - destination_file == 1)){
      return true;
    }
  }

  return false;
}

bool Rook::move(int destination_rank, int destination_file, ChessPiece* destination_piece){
  if ((destination_rank - current_rank) != 0 && destination_file == current_file){
    if (destination_piece == NULL){
    return true;
    }
    else if (destination_piece->get_team() != team){
      return true;
    }
  }
  if ((destination_rank == current_rank) && (destination_file - current_file) != 0){
    if (destination_piece == NULL){
    return true;
    }
    else if (destination_piece->get_team() != team){
      return true;
    }
  }
  return false;
}

bool Bishop::move(int destination_rank, int destination_file, ChessPiece* destination_piece){
  int diagonal = abs(destination_rank - current_rank);

  if (abs(destination_file - current_file) == diagonal){
    if (destination_piece == NULL){
    return true;
    }
    else if (destination_piece->get_team() != team){
      return true;
    }
  }
  return false;
}

bool Queen::move(int destination_rank, int destination_file, ChessPiece* destination_piece){
    int diagonal = abs(destination_rank - current_rank);

    if ((destination_rank - current_rank) != 0 && (destination_file - current_file) == 0){
      if (destination_piece == NULL){
      return true;
      }
      else if (destination_piece->get_team() != team){
        return true;
      }
    }
    if ((destination_rank - current_rank) == 0 && (destination_file - current_file) != 0){
      if (destination_piece == NULL){
      return true;
      }
      else if (destination_piece->get_team() != team){
        return true;
      }
    }
    if (abs(destination_file - current_file) == diagonal){
      if (destination_piece == NULL){
      return true;
      }
      else if (destination_piece->get_team() != team){
        return true;
      }
    }
    return false;
}

bool Knight::move(int destination_rank, int destination_file, ChessPiece* destination_piece){
  if(abs(destination_rank - current_rank) == 2 && abs(destination_file - current_file) == 1 &&
  (destination_piece == NULL || destination_piece->get_team() != team)){
    return true;
  }
  if(abs(destination_rank - current_rank) == 1 && abs(destination_file - current_file) == 2 &&
  (destination_piece == NULL || destination_piece->get_team() != team)){
    return true;
  }
  return false;
}

bool King::move(int destination_rank, int destination_file, ChessPiece* destination_piece){
  if (abs(destination_rank - current_rank) == 1  && (destination_file == current_file)) {
      if (destination_piece == NULL || destination_piece->get_team() != team){
        return true;
      }
  }
  if (abs(destination_file - current_file) == 1  && (destination_rank == current_rank)) {
    if (destination_piece == NULL || destination_piece->get_team() != team){
      return true;
    }
  }
  if (abs(destination_file - current_file) == 1 && abs(destination_rank - current_rank) == 1){
    if (destination_piece == NULL || destination_piece->get_team() != team){
      return true;
    }
  }
  return false;
}

int char_to_int(char a){
  int i;
  i = static_cast<int>(a - 65);
  return i;
}
