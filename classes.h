#ifndef CLASSES_H
#define CLASSES_H
#pragma once

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class plr {
    int x;
    int y;

    public:

    plr (int _x, int _y);
    plr ();

    int getX ();
    int getY ();

    void movePlr (pair<int, int> offset);
    char* analize(const char* line);
};

enum class cell: char {wall = '#', empty='.', bush='+'};

class Pole {

    int width, height;
    plr servak, clientosina;
    vector<vector<cell>> matrix;

    public:

    //Pole ();
    Pole (int _size);
    Pole (int _width, int _height);
    Pole (vector<vector<cell>> _matrix);

    bool isEmptyCell (int x, int y);
    char* draw();

    void movePlrServak(char* whatDo);
};

char* vectorCharToCString (vector<char> line);

#endif