#pragma once

#include "Map.h"
#include "Box.h"

#include<iostream>
#include <vector>
#include <stack>
#include <list>

using std::vector;
using std::stack;
using std::string;
using std::list;
using std::cout;
using std::endl;


namespace maze
{
// class MoveLocation : public Box {
//  public:
//   MoveLocation(int x, int y)
//     : Box(x, y) {
//         this->_x = x;
//         this->_y = y;
//   }

//  private:
//   int _x;
//   int _y;
// };
const int straight_move = 10; //直移一格消耗
const int oblique_mov = 14; //斜移一格消耗

class AStar {

 public:
  enum class Action{go_right, go_down, go_left, go_up};

  AStar(Map *map){
    _maze = map->get_Map();
  };

  void getPath(Box start, Box tag);
// visualization must be carried out after getPath()
  void visualization(Box start, Box tag);

 private:
  void showList();

  vector<vector<Box>> initMap();
// whether the start box and target box is available
  bool isLegalStartorTagert (Box start, Box tag);

  Box * findPath(Box &start, Box &tag);

  void updateInfo(Box * curr, Box *center, Box tag);
  int calcG(Box *curr, Box *start);
  void calcH(Box *curr, Box tag);
  void calcF(Box *curr);


// find the Box with minimal F score in open list
  Box * findMinimalFscoreBox();

// Take the tagBox as the center and find its nearby Box
  vector<Box *> findNeighbor (const Box* tagBox);

  bool          isObstacle   (Box tagBox);
  Box *         isInOpenList (const Box* tagBox);
  Box *         isInCloseList(const Box tagBox);

  vector<vector<int>>    _maze;
  vector<vector<Box>>    _map; 

  

  int                    _map_row_numb;
  int                    _map_col_numb;

  list<Box *>            _open_list;
  list<Box *>            _close_list;


	std::list<Box *>       _path;


  // Movement direction
  // vector<MoveLocation>  _move_dire;

  // used to record action
  vector<Action>        _act;
};
} // namespace maze
