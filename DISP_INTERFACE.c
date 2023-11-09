#pragma ONCE
#define NULLPTR 0x0
struct player {
  // track current player position on map
  unsigned short row;
  unsigned short column;
  char character;
};

class matrix {
public:
  char **map;
  matrix(player *_p, unsigned short rows, unsigned short cols) {
    this->p = _p;
    this->map = new char *[rows];
    for (int i = 0; i < rows; ++i)
      this->map[i] = new char[cols];
    map[0][0] = p->character;
    p->row = 0;
    p->column = 0;
  }

  bool spawned() { return (p != NULLPTR); }

  void right() {
    if (p->column < 16) {
      p->column += 1;
      // y represents columns
      map[0][p->column] = p->character;
      map[0][p->column - 1] = ' ';
    }
    if (p->column == 16) {
      p->row = 0;
      p->column = 0;
    }
  }
  void left() {
    if (p->column > 0) {
      p->column -= 1;
      // y represents columns
      map[0][p->column] = p->character;
      map[0][p->column + 1] = ' ';
    }
    if (p->column == 0) {
      p->row = 0;
      p->column = 16;
      map[p->row][p->column] = p->character;
      map[p->row + 1][p->column] = ' ';
    }
  }
  void up() {
    if (p->row > 0) {
      p->row -= 1;
      map[p->row][p->column] = p->character;
      map[p->row + 1][p->column] = ' ';
    }
    if (p->row == 0) {
      p->row = 1;
      map[p->row][p->column] = p->character;
      map[0][p->column] = ' ';
    }
  }
  void down() {
    if (p->row < 1) {
      p->row += 1;
      map[p->row][p->column] = p->character;
      map[p->row - 1][p->column] = ' ';
    }
    if (p->row == 1) {
      p->row = 0;
      map[p->row][p->column] = p->character;
      map[1][p->column] = ' ';
    }
  }
  void clear() {
    for (int i = 0; i < 2; i++) {
      if (map[i]) {
        delete[] map[i];
        map[i] = NULLPTR;
      }
    }
    delete[] map;
    map = NULLPTR;
    delete p;
    p = NULLPTR;
  }

private:
  player *p;
};
