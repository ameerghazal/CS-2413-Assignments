//
// Created by ameer on 8/23/2023.
//

#include "tester.h"
#include "iostream"

using namespace std;

int main() {

    int x[3] = {1, 2, 3};
    int *ptr = x;

    for (int index = 0; index < 3; index++) {
        cout << *ptr++ << endl;
    }

    return 0;
}