
#include "classes.h"

using namespace std;

int main () {
    Pole pole (10);

    cout << pole.draw() << "\n\n";

    pole.movePlrClientosina(1, 1);

    cout << pole.draw();

    return 0;
}