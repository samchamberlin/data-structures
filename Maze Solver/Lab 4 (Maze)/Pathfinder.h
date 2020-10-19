#pragma once
#include "PathfinderInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Pathfinder : public PathfinderInterface{
public:
    Pathfinder() {}
    ~Pathfinder() {}

    string toString() const;
    void createRandomMaze();
    bool importMaze(string file_name);
    vector<string> solveMaze();
    bool findPath(int x,int y,int z);
    string currentMaze[5][5][5];
    bool wasHere[5][5][5];
    bool mazeAvailable = false;
    vector<string> solution;
    stack<string> stack_solution;

};
