#include "Astar.h"
#include "Map.h"
#include "Box.h"
#include <gtest/gtest.h>

int main() {
  maze::Map * map = new maze::Map(2);
  maze::AStar astar(map);
  maze::Box start(0, 0);
  maze::Box target(2, 7);
  astar.getPath(start, target);
  astar.visualization(start, target);


  maze::Map * map2 = new maze::Map(1);
  maze::AStar astar2(map2);
  maze::Box start2(0, 0);
  maze::Box target2(5, 5);
  astar2.getPath(start2, target2);
  astar2.visualization(start2, target2);

  std::cout << "\nDone" << std::endl;
  return 0;

}