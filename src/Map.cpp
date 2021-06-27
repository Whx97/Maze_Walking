#include "Astar.h"
#include "Box.h"
#include "Map.h"

#include <iostream>
#include <vector>
#include <stack>
#include <array>


using std::vector;
using std::cout;
using std::endl;

namespace maze
{
void Map::initMap() {
  int map_row = _maze.size();
  int map_col = _maze[0].size();
  cout << map_row << map_col << endl;

  vector<Box> vtemp(map_col, Box(0,0));
  vector<vector<Box>> _map(map_row, vtemp);

  for (int i = 0; i < map_row; ++i)
  {
    for (int j = 0; j < map_col; ++j)
    {
      if (_maze[i][j] == 0)
      {
        Box box(i, j);
        _map[i][j] = box;
      } else {
          Box box1(i, j);
          box1.setObstacle(true);
          _map[i][j] = box1;
        }      
    }    
  }
  // cout << _map[0].size();
  cout << _map[0][1].getX() << " " << _map[0][1].getY() << endl;    
}


} // namespace maze
