#pragma once
#include "Pathfinder.h"

Pathfinder1::Pathfinder1() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0;k < 5; ++k) {
                maze[i][j][k] = 1;
            }
        }
    }
}

Pathfinder1::~Pathfinder1() {}

string Pathfinder1::toString() {
    stringstream ss;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0;k < 5; ++k) {
                ss << maze[i][j][k] << " ";
            }
            ss << endl;
        }
        ss << endl << endl;
    }
    string mazeMap;
    ss >> mazeMap;
}

void Pathfinder1::createRandomMaze() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0;k < 5; ++k) {
                maze[i][j][k] = rand() % 2;
            }
        }
    }
    maze[0][0][0] = 1;
    maze[4][4][4] = 1;
}

bool Pathfinder1::importMaze(string file_name) {
    fstream fin;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0;k < 5; ++k) {
                if(!fin.eof && fin >> maze[i][j][k]){
                    if(maze[i][j][k] != 0 && maze[i][j][k] != 1){
                        return false;
                    }
                } else{
                    return false;
                }
            }
        }
    }
    if(!fin.empty() || maze[0][0][0] != 1 || maze[4][4][4] != 1){
        return false;
    }
    return true;
}

bool Pathfinder1::findPath() {
    
}

vector<string> Pathfinder1::solveMaze() {
    
}

