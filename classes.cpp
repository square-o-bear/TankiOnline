
#include "classes.h"

// plr

plr::plr (int _x, int _y) {
    x = _x;
    y = _y;
}
plr::plr () { x = 0; y = 0; }

int plr::getX () { return x; }
int plr::getY () { return y; }

void plr::movePlr (int x_offset, int y_offset) { x += x_offset; y += y_offset; }





// vector char to CString

char* vectorCharToCString (vector<char> line) {
    char* cString = new char[line.size() + 1];
    std::memcpy(cString, line.data(), line.size());

    // Add the null terminator
    cString[line.size()] = '\0';

    return cString;
}





// sPole

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
        }
        stringSeePole[_y*(width*2+1)+width*2] = '\n';
    }

    stringSeePole[servak.getY()*(width*2+1)+servak.getX()*2] = '1';
    stringSeePole[clientosina.getY()*(width*2+1)+clientosina.getX()*2] = '2';

    return vectorCharToCString(stringSeePole);
}

void Pole::movePlrServak(int x_offset, int y_offset) {
    
    if (isEmptyCell(servak.getX()+x_offset, servak.getY()+y_offset)) {
        servak.movePlr(x_offset, y_offset);
    }

}

void Pole::movePlrClientosina(int x_offset, int y_offset) {

    if (isEmptyCell(clientosina.getX()+x_offset, clientosina.getY()+y_offset)) {
        clientosina.movePlr(x_offset, y_offset);
    }

}