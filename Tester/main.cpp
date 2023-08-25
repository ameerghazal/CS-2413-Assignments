#include <iostream>

using namespace std;

int main() {


    int z[3] = {1, 4, 9};
    int *ptr = z;

    for (int index = 0; index < 3; index++) {
        cout << *ptr++ << endl;
    }

    for (int index = 0; index < 3; index++) {
        cout << *ptr-- << endl;
    }

    for (int index = 0; index < 3; index++) {
        cout << ++ptr << endl;
    }


    return 0;
}
