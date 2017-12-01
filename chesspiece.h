
enum Colour{White, Black};


class ChessPiece{
  public:
    ChessPiece(Colour bw, string _name);
    //virtual void move();
    //virtual void check_valid_move();
    //void in_check();
    friend ostream& operator <<(ostream& o, const ChessPiece* a);

  private:
      Colour team;
      string name;

};

class King: public ChessPiece{
  public:
    King(Colour bw, string _name): ChessPiece(bw, _name){};
    void move();

  private:
};

class Queen: public ChessPiece{
  public:
    Queen(Colour bw, string _name): ChessPiece(bw, _name){};
    void move();

  private:

};

class Rook: public ChessPiece{
  public:
    Rook(Colour bw, string _name): ChessPiece(bw, _name){};
    void move();

  private:

};

class Knight: public ChessPiece{
  public:
    Knight(Colour bw, string _name): ChessPiece(bw, _name){};
    void move();

  private:

};

class Bishop: public ChessPiece{
  public:
    Bishop(Colour bw, string _name): ChessPiece(bw, _name){};
    void move();

  private:

};

class Pawn: public ChessPiece{
  public:
    Pawn(Colour bw, string _name): ChessPiece(bw, _name){};
    void move();

  private:
