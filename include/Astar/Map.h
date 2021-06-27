#pragma once

#include<iostream>
#include <vector>
#include <stack>
#include "Box.h"

using std::vector;

namespace maze
{
class Box;
class Map {
  
 public:
  Map() = default;
  Map(int i)
  {
    if (i == 1)
    {
      _maze = _maze1;
    } else {
      _maze = _maze2;
    }
    
  }

  ~Map() = default;


  // vector<vector<Box>> get_Map() const { return _map; }
  vector<vector<int>> get_Map() const { return _maze; }


  int get_MapRowNumb() const { return _maze.size(); }
  int get_MapColNumb() const { return _maze[0].size(); }
 private:
  void initMap();
  vector<vector<Box>>    _map;
  vector<vector<int>>    _maze;
 // "1" means this road is not available;
 // "0" means passable.
  vector<vector<int>> _maze1 = {  { 0,1,1,0,1,1 },
                                { 0,0,1,0,1,0 },
                                { 0,0,1,0,0,0 },
                                { 1,0,0,0,1,0 },
                                { 0,1,1,1,0,0 },
                                { 0,1,1,1,0,0 } };
  vector<vector<int>> _maze2 = {  { 0,0,0,0,1,1,1,1 },
                                { 0,0,0,0,0,1,1,1 },
                                { 1,1,0,1,1,0,0,0 },
                                { 1,0,0,0,0,0,0,0 } };


};
} // namespace Maze
