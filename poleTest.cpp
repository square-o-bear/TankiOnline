
#include "classes.h"

using namespace std;

int main () {
    Pole pole (15);
    char use[1024];

    while (true)
    {
        cin >> use;
        pole.movePlrClientosina(use);

        cout << pole.draw() << "\n";
    }
    

    return 0;
}