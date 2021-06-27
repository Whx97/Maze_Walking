#include "Astar.h"
#include "Box.h"
#include "Map.h"

#include <iostream>
#include <vector>
#include <stack>
#include <array>

#include <math.h>

using std::vector;
using std::cout;
using std::endl;
using std::sqrt;

namespace maze
{

vector<vector<Box>> AStar::initMap() {
  int map_row = _maze.size();
  int map_col = _maze[0].size();
  cout << map_row << " ,"<< map_col << endl;

  vector<Box> vtemp(map_col, Box(0,0));
  vector<vector<Box>> map(map_row, vtemp);

  for (int i = 0; i < map_row; ++i)
  {
    for (int j = 0; j < map_col; ++j)
    {
      if (_maze[i][j] == 0)
      {
        Box box(i, j);
        map[i][j] = Box(box);
      } else {
          Box box1(i, j);
          box1.setObstacle(true);
          map[i][j] = Box(box1);
        }      
    }    
  }
  return map;
}

void AStar::getPath(Box start, Box tag) {
  _map = initMap();
  _map_row_numb = _map.size();
  _map_col_numb = _map[0].size();

  if (isLegalStartorTagert(start, tag)) {

    Box *result = findPath(start, tag);

    while (result) {
      // cout << "result " << endl;
      _path.push_front(result);
      result = result->get_FatherBox();
    }
  
    _open_list.clear();
    _close_list.clear();
    for (auto &p : _path) {
		cout << '(' << p->getX() << ',' << p->getY() << ")  " ;   
    }
    cout << endl;   
  }
  
}

void AStar::visualization(Box start, Box tag) {
  vector<string> vtemp(_map_col_numb, "⬛");
  vector<vector<string>> vis(_map_row_numb, vtemp);
  for (int i = 0; i < _map_row_numb; ++i) {
    for (int j = 0; j < _map_col_numb; ++j) {
      if (_maze[i][j] == 1) {
        vis[i][j] = "⬜";
      }     
    }    
  }
  for (auto &p : _path) {
    vis[p->getX()][p->getY()] = "🐁";
  }
  vis[start.getX()][start.getY()] = "🚩";
  vis[tag.getX()][tag.getY()] = "🏁";
  for (int i = 0; i < _map_row_numb; ++i) {
    for (int j = 0; j < _map_col_numb; ++j) {
      cout << vis[i][j];
    }
    cout << endl;
  }
}


bool AStar::isLegalStartorTagert(Box start, Box tag) {
  int curr_x = start.getX();
  int curr_y = start.getY();
  int tag_x = tag.getX();
  int tag_y = tag.getY();
  Box start_bx = _map[curr_x][curr_y];
  Box tag_bx = _map[tag_x][tag_y];

  if (start_bx.get_isObstacle() || tag_bx.get_isObstacle()) {
    return false;
  }
  return true;
}

// void AStar::showList() {
//   cout << "              open list";
//   for (auto p : _open_list)
//   {
//     cout <<"("<< p->getX() << "."<<p->getY() << ")";
//   }
//   cout << endl;

//   cout << "              close list";
//   for (auto p : _close_list)
//   {
//     cout <<"("<< p->getX() << "."<<p->getY() << ")";
//   }
//   cout << endl;
  
// }

Box * AStar::findPath(Box &start, Box &tag) {

  _open_list.push_back(new Box(start));

  while (!_open_list.empty()) {
    // find next Box.
    Box * curr_box = findMinimalFscoreBox();
    // cout << "curr box" << curr_box->getX() << curr_box->getY() << endl;

    _open_list.remove(curr_box);
    _close_list.push_back(curr_box);
    // find the neighbor Box of curr_box;
    vector<Box*> neighborBox = findNeighbor(curr_box);

    for (auto &neighbor : neighborBox) {
      // if not in open list, update H、G、F score, and set father as curr_box;
      if (!isInOpenList(neighbor))
      { 
        _open_list.push_back(neighbor);
        neighbor->setFather(curr_box);
 
        // showList();

        updateInfo(neighbor, curr_box, tag);

      } else {
        // if in open list, judge whether to change his father
          int tempG = calcG(neighbor, curr_box);
          if (tempG < neighbor->getG()) {
            neighbor->setFather(curr_box);
            neighbor->setG(tempG);
            calcF(neighbor);
          } 
        }
      
      // judge if target node is find
      Box *resPoint = isInOpenList(&tag);
			if (resPoint) {
        return resPoint;
      }      
    }
    neighborBox.clear();
  }
  return nullptr;
}

///////////////////////////////////////////////////////////////////
// update H、G、F score
void AStar::updateInfo(Box * curr, Box* center, Box tag) {
  int G = calcG(curr, center);
  curr->setG(G);
  calcH(curr, tag);
  calcF(curr);
}

int AStar::calcG(Box *curr, Box *center) {
  int curr_x = curr->getX();
  int curr_y = curr->getY();
  int start_x = center->getX();
  int start_y = center->getY();

  int extraG = (abs(curr_x - start_x) + abs(curr_y - start_y)) == 1 
                ? straight_move : oblique_mov;
	int parentG = center->get_FatherBox() == NULL 
                ? 0 : center->get_FatherBox()->getG(); //如果是初始节点，则其父节点是空
  
  return parentG + extraG;

}

void AStar::calcH(Box *curr, Box tag) {
  int curr_x = curr->getX();
  int curr_y = curr->getY();
  int tag_x = tag.getX();
  int tag_y = tag.getY();
	int H = abs(curr_x - tag_x) + abs(curr_y - tag_y);
  curr->setH(H*10);
}

void AStar::calcF(Box *curr) {
  curr->setF(curr->getG() + curr->getH());
}
////////////////////////////////////////////////////////////////////

Box *AStar::findMinimalFscoreBox() {

  if (!_open_list.empty())
	{
		auto resPoint = _open_list.front();
		for (auto &point : _open_list)
		if (point->getF()< resPoint->getF())
			resPoint = point;
		return resPoint;
	}
  return nullptr;
}

vector<Box *> AStar::findNeighbor(const Box* tagBox) {

  int start_x = tagBox->getX();
  int start_y = tagBox->getY();
  vector<Box *> surroundBox;

  for (int i = start_x - 1; i <= start_x + 1; i++) {
    for (int j = start_y - 1; j <= start_y + 1; j++) {
      // Make sure the point is within the map and do not coincide with the center point
      if (i >= 0 && i < _map_row_numb &&
          j >= 0 && j < _map_col_numb &&
          !(i == start_x && j == start_y)) {
        Box temp = _map[i][j];
        // Make sure the point is not an obstacle, and not in close list
        if (!isObstacle(temp) && !isInCloseList(temp)) {
          surroundBox.push_back(new Box(temp));
        }
      }         
    }     
  }
  return surroundBox;
}
  
bool AStar::isObstacle(Box tagBox){
  return tagBox.get_isObstacle();
}

Box * AStar::isInOpenList(const Box *tagBox) {
  for (auto p : _open_list) {
    if (p->getX() == tagBox->getX() && p->getY() == tagBox->getY()) {
      return p;
    }
  }
	return nullptr;
}

Box * AStar::isInCloseList(const Box tagBox) {
  for (auto p : _close_list) {
    if (p->getX() == tagBox.getX() && p->getY() == tagBox.getY()) {
      return p;
    }
  }
	return nullptr;
}
} // namespace maze
