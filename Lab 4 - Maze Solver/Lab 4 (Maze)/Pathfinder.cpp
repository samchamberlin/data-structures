#include "Pathfinder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

string Pathfinder::toString() const{
    string maze;
    if (mazeAvailable){
        for (int z = 0; z < 5; z++){
            for (int y = 0; y < 5; y++){
                for (int x = 0; x < 5; x++){
                    maze += currentMaze[x][y][z];
                    if (x != 4){
                        maze += " ";
                    }
                }
                maze += "\n"; //to put each row on a different line
            }
            if (z != 4){
                maze += "\n"; //to put each row on a different line
            }
        }
    } else{ //if maze isn't available, create one with 1's
        for (int z = 0; z < 5; z++){
            for (int y = 0; y < 5; y++){
                for (int x = 0; x < 5; x++){
                    maze += "1";
                    if (x != 4){
                        maze += " ";
                    }
                }
                maze += "\n"; //to put each row on a different line
            }
            if (z != 4){
                maze += "\n"; //to add another line between every 5 lines
            }
        }
    }
    return maze;
}

void Pathfinder::createRandomMaze(){
    string tempMaze[5][5][5];
    mazeAvailable = true;
    for (int z = 0; z < 5; z++){
        for (int y = 0; y < 5; y++){
            for (int x = 0; x < 5; x++){
                if ((z == 0 && y == 0 && x == 0) || (z == 4 && y == 4 && x == 4)){
                    tempMaze[x][y][z] = "1";
                    currentMaze[x][y][z] = "1";
                } else{
                    int i = rand()%2;
                    tempMaze[x][y][z] = to_string(i);
                    currentMaze[x][y][z] = tempMaze[x][y][z];
                }
            }
        }
    }
}

bool Pathfinder::importMaze(string file_name){
    string tempMaze[5][5][5];
    int count = 0;
    char token;
    ifstream fin;
    
    fin.open(file_name);
    
    //check maze validity
    if(fin.is_open()){
        while (fin >> token){ //if the numbers are all 1's and 0's
            if (token == '1' || token == '0'){
                count++;
            } else{
                return false;
            }
        }
        fin.close();
    } else{ //if file opened
        return false;
    }
    
    if (count != 125){ //if the maze is 5x5x5
        return false;
    }

    fin.open(file_name);

    if (fin.is_open()){ //imports the maze
        for (int z = 0; z < 5; z++){
            for (int y = 0; y < 5; y++){
                for (int x = 0; x < 5; x++){
                    fin >> token;
                    tempMaze[x][y][z] = token;
                }
            }
        }
    }

    if (tempMaze[4][4][4] == "0" || tempMaze[0][0][0] == "0"){ //if start and end are 1
        return false;
    }

    for (int z = 0; z < 5; z++){
        for (int y = 0; y < 5; y++){
            for (int x = 0; x < 5; x++){
                currentMaze[x][y][z] = tempMaze[x][y][z];
            }
        }
    }
    mazeAvailable = true;
    return true;
}

vector<string> Pathfinder::solveMaze(){
    solution.clear();

    if (!mazeAvailable){
        return solution;
    }
    for (int z = 0; z < 5; z++){ //resets all the "was heres"
        for (int y = 0; y < 5; y++){
            for (int x = 0; x < 5; x++){
                this ->wasHere[x][y][z] = false;
            }
        }
    }

    bool b = findPath(0,0,0); //call recursive function

    if(!b){ //not solvable
        solution.clear();
        return solution;
    }

    while (stack_solution.size() != 0){
        solution.push_back(stack_solution.top());
        stack_solution.pop();
    }

    return solution;
}

bool Pathfinder::findPath(int x, int y, int z){
    if (x == 4 && y == 4 && z == 4){
        string end = "(4, 4, 4)";
        stack_solution.push(end);
        return true;
    }
    if (x < 0 || x > 4 || y < 0 || y > 4 || z < 0 || z > 4){
        return false;
    }
    if (currentMaze[x][y][z] == "0"){
        return false;
    }
    if (wasHere[x][y][z]){
        return false;
    }
    wasHere[x][y][z] = true;

    if (findPath(x - 1, y , z) ||
        findPath(x + 1, y , z) ||
        findPath(x, y - 1, z) ||
        findPath(x, y + 1 , z) ||
        findPath(x, y , z - 1) ||
        findPath(x, y , z + 1)){

        stringstream ss;
        ss << "(" << x << ", " << y << ", " << z << ")";
        stack_solution.push(ss.str());
        return true;
    }
    return false;
}
