#pragma once

namespace maze
{
class Box {

 public:
  Box (int x, int y)
    : _x(x),
      _y(y) {
  }
  ~Box () = default;

  Box(const Box& b) {
    _father_box = b.get_FatherBox();
    _x= b.getX();
    _y = b.getY();
    _G_score = b.getG();
    _H_score = b.getH();
    _F_score = b.getF();
    _is_obstacle = b.get_isObstacle();
  }

  int getX()            const { return _x; }
  int getY()            const { return _y; }
  bool get_isObstacle() const { return _is_obstacle; }
  int getH()            const { return _H_score; }
  int getG()            const { return _G_score; }
  int getF()            const { return _F_score; }

  Box *get_FatherBox()  const { return _father_box; }

  void setObstacle(bool b)    { _is_obstacle = b; }
  void setH(int h)            { _H_score = h; }
  void setG(int g)            { _G_score = g; }
  void setF(int f)            { _F_score = f; }
  void setFather(Box *father) { _father_box = father; }

 private:
  Box *     _father_box = nullptr;
  int       _x;
  int       _y;
  int       _G_score = 0;
  int       _H_score = 0;
  int       _F_score = 0;
  bool      _is_obstacle = false;
};
} // namespace maze
