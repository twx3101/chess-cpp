#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <ostream>

using std::ostream;
using std::string;

enum Colour{White, Black};
enum Type{KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE};


class ChessPiece{
  public:
    /*Constructor */
    ChessPiece(Colour bw, string _name, int rank, int file);

    /*virtual destructor */
    virtual ~ChessPiece(){}

    /* Returns chesspiece team */
    Colour get_team();

    /* Returns name of chesspiece */
    string get_name();

    /* virtual move function that returns true for a valid move */
    virtual bool move(int destination_rank, int destination_file, ChessPiece* destination_piece) = 0;

    /* Updates location of chesspiece */
    void update_current_location(int destination_rank, int destination_file);

    /* virtual function that returns the chesspiece type */
    virtual Type get_type() = 0;

    /* check if piece is on its first move */
    virtual bool get_first_move(){
      return false;
    }

    /*set first move to false when a piece makes a move */
    virtual void set_first_move(){
      return;
    }

    /* << overloaded operator to print name of piece and it's team */
    friend ostream& operator <<(ostream& o, const ChessPiece* a);

  protected:
      Colour team;
      string name;
      int current_rank;
      int current_file;
};

class King: public ChessPiece{
  public:
    /* constructor */
    King(Colour bw, string _name, int rank, int file);

    /* destructor */
    ~King(){}

    /* Check if king has made a valid move (one space only in each direction) */
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece) override;

    /* Returns type KING */
    Type get_type(){
      return KING;
    }

    /* Returns first move */
    bool get_first_move(){
      return first_move;
    }

    /* Sets first move to false once move has been made */
    void set_first_move(){
      first_move = false;
    }

  private:
    bool first_move; // first_move only in king and rook to check for castling
};

class Queen: public ChessPiece{
  public:
    /* constructor */
    Queen(Colour bw, string _name,int rank, int file): ChessPiece(bw, _name, rank, file){};

    /* destructor */
    ~Queen(){}

    /* Check if queen has made a valid move (moving in any direction) */
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece) override;

    /* Returns type QUEEN */
    Type get_type() override{
      return QUEEN;
    }
  private:

};

class Rook: public ChessPiece{
  public:
    /* Constructor */
    Rook(Colour bw, string _name, int rank, int file);

    /* Destructor */
    ~Rook(){}

    /* Check if rook has made a valid move (only along ranks and files) */
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;

    /*returns type ROOK */
    Type get_type()override{
      return ROOK;
    }

    /* check whether the piece is still on its first move */
    bool get_first_move(){
      return first_move;
    }

    /* sets first move to false once it has made a valid move */
    void set_first_move(){
      first_move = false;
    }
  private:
      bool first_move;

};

class Knight: public ChessPiece{
  public:
    /* Constructor */
    Knight(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};

    /* Destructor */
    ~Knight(){}

    /* Check if knight has made a a valid move ('L' shaped moves only) */
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;

    /* Returns type KNIGHT */
    Type get_type()override{
      return KNIGHT;
    }
  private:

};

class Bishop: public ChessPiece{
  public:
    /* Constructor */
    Bishop(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};

    /* Destructor */
    ~Bishop(){}

    /* Check if bishop has made a valid move (only diagonals) */
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;

    /* returns type BISHOP */
    Type get_type()override{
      return BISHOP;
    }
  private:

};

class Pawn: public ChessPiece{
  public:
    /* Constructor */
    Pawn(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};

    /* Destructor */
    ~Pawn(){}

    /* Check if pawn has made a valid move (forward one space or 2 only if
    on its first move or diagonal to take an opponent's piece) */
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;

    /*Returns type PAWN */
    Type get_type()override{
      return PAWN;
    }
  private:

};

#endif
