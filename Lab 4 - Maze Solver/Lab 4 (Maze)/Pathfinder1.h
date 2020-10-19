#pragma once
#include "PathfinderInterface.h"
#include <sstream>
#include <fstream>

class Pathfinder1 : public PathfinderInterface {
public:
    PathFinder1() {}
    PathFinder1() {}
    string toString();
    void createRandomMaze();
    bool importMaze(string file_name);
    bool findPath(int x, int y, int z);
    vector<string> solveMaze();
private:
    int maze[5][5][5];
    vector<string> p;
};

