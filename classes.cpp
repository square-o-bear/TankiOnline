
#include "classes.h"





// plr

plr::plr (int _x, int _y) {
    x = _x;
    y = _y;
}
plr::plr () { x = 0; y = 0; }

int plr::getX () { return x; }
int plr::getY () { return y; }

void plr::movePlr (pair<int, int> offset) { x += offset.first; y += offset.second; }

char* plr::analize(const char* line) {
    vector<char> message = {' ', ' ', ' '};
    //                       w    a   attack

    for (int i = 0; i < strlen(line); ++i) {
        switch(line[i]) {
            case 'w': {
                message[0] = '*';
            } break;
            case 'a': {
                message[1] = '*';
            } break;
            case 's': {
                message[0] = ' ';
            } break;
            case 'd': {
                message[1] = ' ';
            } break;
            case 'e': {
                message[2] = '*';
            } break;
            case 'q': {
                message[2] = ' ';
            } break;
        }
    }

    return vectorCharToCString(message);
}










// vector char to CString

char* vectorCharToCString (vector<char> line) {
    char* cString = new char[line.size() + 1];
    std::memcpy(cString, line.data(), line.size());

    // Add the null terminator
    cString[line.size()] = '\0';

    return cString;
}










// Pole construct

Pole::Pole (int _size) {
    width = _size;
    height = _size;
    
    servak      = plr(1, 1);
    clientosina = plr(height-2, width-2);

    matrix = vector<vector<cell>> (height, vector<cell>(width, cell::empty));
}

Pole::Pole (int _width, int _height) {
    width = _width;
    height = _height;

    servak      = plr(1, 1);
    clientosina = plr(height-2, width-2);

    matrix = vector<vector<cell>> (height, vector<cell>(width, cell::empty));
}

Pole::Pole (vector<vector<cell>> _matrix) {
    matrix = _matrix;
    width = _matrix.size();
    height = _matrix[0].size();

    servak      = plr(1, 1);
    clientosina = plr(height-2, width-2);
}










// Pole methods

bool Pole::isEmptyCell (int x, int y) {
    if (y < 0 && height <= y) return true;
    if (x < 0 && width <= x) return true;

    return !(( matrix[y][x] == cell::wall                          ) or 
             ( servak.getX() == x and servak.getY() == y           ) or 
             ( clientosina.getX() == x and clientosina.getY() == y ) );
}

char* Pole::draw() {
    vector<char> stringSeePole(height*(width*2+1), 0);

    for (int _y = 0; _y < height; ++_y) {
        for (int _x = 0; _x < width; ++_x) {
            stringSeePole[_y*(width*2+1)+_x*2] = static_cast<char>(matrix[_y][_x]);
            stringSeePole[_y*(width*2+1)+_x*2+1] = ' ';

            if (matrix[_y][_x] == cell::wall && _x != width-1) {
                stringSeePole[_y*(width*2+1)+_x*2+1] = static_cast<char>(cell::wall);
            } else {
                stringSeePole[_y*(width*2+1)+_x*2+1] = ' ';
            }
        }
        stringSeePole[_y*(width*2+1)+width*2] = '\n';
    }

    stringSeePole[servak.getY()*(width*2+1)+servak.getX()*2] = '1';
    stringSeePole[clientosina.getY()*(width*2+1)+clientosina.getX()*2] = '2';

    return vectorCharToCString(stringSeePole);
}

void Pole::movePlrServak(char* whatDo) {
    whatDo = servak.analize(whatDo);
    if (whatDo[2] == ' ') {
        servak.movePlr(pair<int, int>(((whatDo[0] == ' ') ? 1 : -1), 
                                      ((whatDo[1] == ' ') ? 1 : -1)));
    }
    else {

    }
}