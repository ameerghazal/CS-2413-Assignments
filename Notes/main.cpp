#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {


    // Exam Working:


    int a[2] = {1,2};
    int *ap = a;
    swap(a[0], a[1]);

    for (int index = 0; index < 2; ++index) {
        cout << *ap++ << " LOLOL";
    }



//  Proper declaration and assignment of a pointer.
    int x = 5;
    int *ptr = &x; // accesses the address of 5.

//  Accessing Pointer
    cout << *ptr << endl; // this will print the value at the address of the pointer, so 5.
    cout << ptr << endl; // this will print the address of the pointer.

    *ptr = *ptr + 5; // this will update the value at the address to 10 (same with x)
    cout << x << ' ' << *ptr << endl;

    ptr = ptr + 5; // this will increment the address of the pointer, which will make it lose the pointer at x.

    cout << &x << endl; // Now if we log the two addresses to compare, they are differet.
    cout << ptr << endl; // this means that *ptr will point to a garbage collected value now.


//  INCREMENTING DATA

    int y = 10;
    int *p = &y;

    (*p)++; // This is the proper way to increment, first allocate the value at the address, then increment.
    cout << *p << ' ' << y;

     *p++; // This would NOT work as it increments than pointer, which would mess up the address
     cout << endl << *p <<  ' ' << y << endl;

//  ARRAYS WITH POINTERS

    int z[3] = {1, 4, 9};
    int *pArray = z; // for array pointers, we do not need to use the '&'

    cout << *pArray << endl; // This will print out the first index.

    pArray++; // this will increment to the next index; however, when trying to access parrray[0], it will point to z[1].
    cout << *pArray << endl; // this will point to index 1 (4)

    for (int index = 0; index < 3; ++index) {
        cout << pArray[index] << endl; // this will access at the indices.
    }

//    SWAP FUNCTION WITH POINTERS

    int first = 3, second = 5;
    swap(&first, &second);

    cout << endl << first << ' ' << second;


    return 0;
}


