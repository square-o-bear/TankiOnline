
#include "classes.h"

using namespace std;

int main () {
    Pole pole (10);
    char use[1024];
    cin >> use;
    cout << use << "\n";
    pole.movePlrServak(use);

    cout << pole.draw() << "\n";

    return 0;
}