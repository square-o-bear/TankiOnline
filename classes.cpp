
#include "classes.h"





// plr

plr::plr (int _x, int _y) {
    x = _x;
    y = _y;
    hp = 10;
}
plr::plr () { x = 0; y = 0; hp = 10; }

int plr::getX () { return x; }
int plr::getY () { return y; }
int plr::getHp () { return hp; }

void plr::movePlr (int x_offset, int y_offset) { x += x_offset; y += y_offset; }

char* plr::analize(const char* line) {
    vector<char> message = {' ', ' ', ' ', '\0'};
    //                       w    a   attack

    for (int i = 0; i < strlen(line); ++i) {
        switch(line[i]) {
            case 'w': {
                message[0] = '-';
            } break;
            case 'a': {
                message[1] = '-';
            } break;
            case 's': {
                message[0] = '+';
            } break;
            case 'd': {
                message[1] = '+';
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

void plr::getDamage (int damage) {
    hp = max(0, hp-damage);
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
    _size = max(9, _size);
    width = _size;
    height = _size;
    
    servak      = plr(1, 1);
    clientosina = plr(height-2, width-2);

    matrix = vector<vector<cell>> (height, vector<cell>(width, cell::empty));
}

Pole::Pole (int _width, int _height) {
    width = max(9, _width);
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
    if (y < 0 || height <= y) return false;
    if (x < 0 || width <= x) return false;

    return !(( matrix[y][x] == cell::wall                          ) or 
             ( servak.getX() == x and servak.getY() == y           ) or 
             ( clientosina.getX() == x and clientosina.getY() == y ) );
}

char* Pole::draw() {
    vector<char> stringSeePole((height+1)*(width*2+1), ' ');
    
    // 1: __/10 | 2: __/10
    stringSeePole[0] = '1';
    stringSeePole[1] = ':';
    stringSeePole[2] = ' ';
    stringSeePole[3] = (char)('0'+(int)(servak.getHp()/10));
    stringSeePole[4] = (char)('0'+(int)(servak.getHp()%10));
    stringSeePole[5] = '/';
    stringSeePole[6] = '1';
    stringSeePole[7] = '0';
    
    stringSeePole[width*2-9] = '2';
    stringSeePole[width*2-8] = ':';
    stringSeePole[width*2-7] = ' ';
    stringSeePole[width*2-6] = (char)('0'+(int)(clientosina.getHp()/10));
    stringSeePole[width*2-5] = (char)('0'+(int)(clientosina.getHp()%10));
    stringSeePole[width*2-4] = '/';
    stringSeePole[width*2-3] = '1';
    stringSeePole[width*2-2] = '0';

    stringSeePole[width*2] = '\n';
    
    
    for (int _y = 1; _y <= height; ++_y) {
        for (int _x = 0; _x < width; ++_x) {
            stringSeePole[_y*(width*2+1)+_x*2] = static_cast<char>(matrix[_y-1][_x]);
            stringSeePole[_y*(width*2+1)+_x*2+1] = ' ';

            if (matrix[_y-1][_x] == cell::wall && _x != width-1) {
                stringSeePole[_y*(width*2+1)+_x*2+1] = static_cast<char>(cell::wall);
            } else {
                stringSeePole[_y*(width*2+1)+_x*2+1] = ' ';
            }
        }
        stringSeePole[_y*(width*2+1)+width*2] = '\n';
    }

    stringSeePole[(servak.getY()+1)*(width*2+1)+servak.getX()*2] = '1';
    stringSeePole[(clientosina.getY()+1)*(width*2+1)+clientosina.getX()*2] = '2';

    return vectorCharToCString(stringSeePole);
}

void Pole::movePlrServak(char* whatDo) {
    whatDo = servak.analize(whatDo);
    int x_offset = 0, y_offset = 0;

    if (whatDo[0] == '+') {
        y_offset = 1;
    }
    else if (whatDo[0] == '-') {
        y_offset = -1;
    }

    if (whatDo[1] == '+') {
        x_offset = 1;
    }
    else if (whatDo[1] == '-') {
        x_offset = -1;
    }

    if (whatDo[2] == ' ' && isEmptyCell(servak.getX()+x_offset, servak.getY()+y_offset)) {
        servak.movePlr(x_offset, y_offset);
    }
    else {
        int bulletX = servak.getX(), bulletY = servak.getY();

        do {
            bulletX += x_offset;
            bulletY += y_offset;
        } while (isEmptyCell(bulletX, bulletY));

        if (bulletX == clientosina.getX() && bulletY == clientosina.getY()) {
            clientosina.getDamage(1);
        }
    }
}

void Pole::movePlrClientosina(char* whatDo) {
    whatDo = servak.analize(whatDo);
    int x_offset = 0, y_offset = 0;

    if (whatDo[0] == '+') {
        y_offset = 1;
    }
    else if (whatDo[0] == '-') {
        y_offset = -1;
    }

    if (whatDo[1] == '+') {
        x_offset = 1;
    }
    else if (whatDo[1] == '-') {
        x_offset = -1;
    }

    if (whatDo[2] == ' ' && isEmptyCell(clientosina.getX()+x_offset, clientosina.getY()+y_offset)) {
        clientosina.movePlr(x_offset, y_offset);
    }
    else {
        int bulletX = clientosina.getX(), bulletY = clientosina.getY();

        do {
            bulletX += x_offset;
            bulletY += y_offset;
        } while (isEmptyCell(bulletX, bulletY));

        if (bulletX == servak.getX() && bulletY == servak.getY()) {
            servak.getDamage(1);
        }
    }
}

int Pole::isContinue() {

    if (servak.getHp() > 0) {
        if (clientosina.getHp() > 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if (clientosina.getHp() > 0) {
            return 2;
        }
        else {
            return 3;
        }
    }
    
}
