#ifndef CLASSES_H
#define CLASSES_H
#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

class plr {
    int x, y, hp;

    public:

    plr (int _x, int _y);
    plr ();

    int getX ();
    int getY ();
    int getHp ();

    void movePlr (int x_offset, int y_offset);
    char* analize(const char* line);

    void getDamage (int damage);
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

    void movePlrClientosina(char* whatDo);

    int isContinue();
};

char* vectorCharToCString (vector<char> line);

#endif