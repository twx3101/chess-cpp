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
    ChessPiece(Colour bw, string _name, int rank, int file);
    virtual ~ChessPiece(){}
    Colour get_team();
    string get_name();
    virtual bool move(int destination_rank, int destination_file, ChessPiece* destination_piece) = 0;
    void update_current_location(int destination_rank, int destination_file);
    virtual Type get_type() = 0;
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
    ~King(){}
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece) override;
    Type get_type(){
      return KING;
    }
  private:
};

class Queen: public ChessPiece{
  public:
    Queen(Colour bw, string _name,int rank, int file): ChessPiece(bw, _name, rank, file){};
    ~Queen(){}
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece) override;
    Type get_type() override{
      return QUEEN;
    }
  private:

};

class Rook: public ChessPiece{
  public:
    Rook(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    ~Rook(){}
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;
    Type get_type()override{
      return ROOK;
    }
  private:

};

class Knight: public ChessPiece{
  public:
    Knight(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    ~Knight(){}
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;
    Type get_type()override{
      return KNIGHT;
    }
  private:

};

class Bishop: public ChessPiece{
  public:
    Bishop(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    ~Bishop(){}
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;
    Type get_type()override{
      return BISHOP;
    }
  private:

};

class Pawn: public ChessPiece{
  public:
    Pawn(Colour bw, string _name, int rank, int file): ChessPiece(bw, _name, rank, file){};
    ~Pawn(){}
    bool move(int destination_rank, int destination_file, ChessPiece* destination_piece)override;
    Type get_type()override{
      return PAWN;
    }
  private:

};

#endif
