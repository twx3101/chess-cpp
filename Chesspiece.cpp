#include "Chesspiece.h"
#include <cstdlib>

ChessPiece::ChessPiece(Colour bw, string _name, int rank, int file) : team(bw), name(_name), current_rank(rank), current_file(file){};

//Rook Constructor
Rook::Rook(Colour bw, string _name, int rank, int file) : ChessPiece(bw, _name, rank, file){
  first_move = true;
}

//King Constructor
King::King(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){
  first_move = true;
}

Colour ChessPiece::get_team(){
  return team;
}

string ChessPiece::get_name(){
  return name;
}

void ChessPiece::update_current_location(int destination_rank, int destination_file){
  current_rank = destination_rank;
  current_file = destination_file;
}

bool Pawn::move(int destination_rank, int destination_file, ChessPiece* destination_piece){

  /* Move forward twice possible for first turn */
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

  /* Move forawrd once */
  if ((team ==  White) && (destination_rank - current_rank) == 1  && (destination_file == current_file) && destination_piece == NULL) {
    return true;
  }
  if ((team ==  Black) && (current_rank - destination_rank ) == 1 && (destination_file == current_file) && destination_piece == NULL) {
    return true;
  }

  /* Diagonal movement possible if to take opponent piece */
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
    if ((destination_piece == NULL) || (destination_piece->get_team() != team)) {
    return true;
    }
  }
  if ((destination_rank == current_rank) && (destination_file - current_file) != 0){
    if ((destination_piece == NULL) || (destination_piece->get_team() != team)){
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

ostream& operator <<(ostream& o, const ChessPiece* a){
  if ( a->team == White){
    o << "White's " << a->name;
    return o;
  }
  else{
    o << "Black's " << a->name;
    return o;
  }
}
