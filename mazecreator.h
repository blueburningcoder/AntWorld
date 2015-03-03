#ifndef MAZECREATOR_H
#define MAZECREATOR_H

#include "maze.hpp"
#include <ctime>
#include <cstdlib>
#include <math.h>




class RandomCreator {
private:
    int runs = -1, tick = -1;
    Maze *mazetoDo;
public:
    RandomCreator(Maze *maze);
    void doTicks(int num);
};










#endif