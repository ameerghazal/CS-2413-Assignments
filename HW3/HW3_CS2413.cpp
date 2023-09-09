
// ========================================
// HW3: Implement a Vector Class
// BY: AMEER GHAZAL
// ========================================

// In this assignment, we will implement
// a vector class based on array, pointer
// and dynamic memory allocation.
//
// The class has two private member
// variables and some member functions.
// Their designs are explained below.
//
// You can add new member functions
// but not new member variables. In
// addition, you cannot use any existing
// vector-related library or function.
//
//

#include <iostream>
using namespace std;

// ======= Task =======
// Design and implement all member
// functions of the MyVector class.

class MyVector {
public:
// The "vsize" function returns the size
// of the current vector.
    int vsize();
// The "empty" function returns 1 if the
// current vector has no element and 0 otherwise.
    int empty();
// The "at" function returns the idx_th element
// of the vector. It also returns -1 if "idx"
// is outside the range of the current vector.
    int at(int idx);
// The "resize" function resizes the current
// vector into a vector of size n. Note there
// are two scenarios (in lecture slides) which
// may need to be addressed separately.
    void resize(int n);
// The "push_back" function adds a new element
// "x" to the end of the current vector. Note
// the vector size increases after addition.
    void push_back(int x);
// The "pop_back" function removes the last
// element from the current vector, but does
// nothing if the current vector is empty.
// Note the vector size decreases after pop.
    void pop_back();
// The "insert" function inserts a new element
// "x" as the idx_th element in the current vector.
// It also does nothing if "idx" is outside the
// range of the current vector.
    void insert(int idx, int x);
// The "erase" function removes the idx_th element
// from the vector. It also does nothing if the
// current vector is empty or if "idx" is outside
// the range of the current vector.
    void erase(int idx);
// The constructor should initialize
// pointer "p" to NULL and "size" to 0.
    MyVector();
private:
    int* p; // This pointer holds the vector (or,essentially,
// address of an array that holds the vector elements.)
// Do remember to update it after some vector operations.
    int size; // This integer holds the size of the current
// vector. Do remember to update it after some
// vector operations.
};

/**
 * 1) The size function will return the size of the vector.
 * @return: the size of the vector.
 */
int MyVector::vsize() {
    return this->size; // this will access the private data and return the size of the specific vector.
}

/**
 * 2) Checks if the vector is empty.
 * @return: 1 if the vector is empty, 0 otherwise.
 */
int MyVector::empty() {
//  If it is empty, return 1.
    if (this->size == 0) return 1;

//  Otherwise, just return 0.
    return 0;
}

/**
 * 3) At function, which will return the element at the
 * specified index; if the index is out of range, it returns -1.
 * @param idx: the index to find.
 * @return: the element if found; -1 if not found.
 */
int MyVector::at(int index) {
    // Remember, p points to the address of an array that holds elements.

    // Initial case: index is larger than or equal to the size, it will not be in the vector
    if (index >= this->size) return -1;

    // Next case: assuming the case above it not true,
    // we can simply access the vector through the pointer notation with brackets, and return it.
    return p[index];

}

/**
 * Resizes the current vector into a vector of size n.
 * There are two different scenarios when it comes to resizing:
 * if the original vector is shorter than n-size, append n-0's to the tail;
 * if the original vector is longer than n-size, remove n-entries, starting from the back.
 * @param n: the new size
 */
void MyVector::resize(int n) {

// Base: If n == this->size, nothing happens, it would be a waste

// Next: if n < size
if (n < this->size) {

    // Create a copy to move over later for dynamic memory allocation.
    int *copy = new int[n];

    // Copy over one to another it wil auto stop at n.
    for (int index = 0; index < n; ++index) {
        copy[index] = this->p[index];
    }

    // Frees up the space from the current pointer.
    delete [] p;

    // Point to the same reference in heap of the newly allocated space and update the size.
    this->p = copy;
    this->size = n;

}

// Otherwise: if n > size: append 0's
else if (n > this->size) {

    // New dynamic memory allocated array.
    int *copy = new int[n];

    // Copy over the contents until the original size is reached. From there, append 0's till the loop is over.
    for (int index = 0; index < n; ++index) {

        if (index >= this->size) {
            // start appending 0's
            copy[index] = 0;
            continue;
        }

        // Typical copy over if the statement does not continue.
        copy[index] = this->p[index];

    }

    // Free up space for p.
    delete [] p;

    // Point new p to the same reference in the heap.
    this->p = copy;
    this->size = n;

    }

}

/**
 * Adds a new element 'x' to the end of the current vector, and increases the size of the vector.
 * @param x: the new element to be added.
 */
void MyVector::push_back(int x) {

    // Create a copy of allocated dynamic memory.
    int *copy = new int[this->size + 1];

    // Copy over the elements.
    for (int index = 0; index < this->size; ++index) {
        copy[index] = p[index];
    }

    // Assignment of the last element.
    copy[this->size] = x;

    // Free up space, assign the address to copy, and incrmenet the size.
    delete [] p;
    this->p = copy;
    this->size++;

}

/**
 * Removes the last element from the vector, if it is not empty and updates the current size.
 */
void MyVector::pop_back() {

    // Only operations are done if the vector is not empty.
    if (this->size > 0) {
        int *copy = new int[this->size - 1]; // creating dynamic memory with one less size.
        for (int index = 0; index < this->size - 1; index++) {
            copy[index] = this->p[index]; // copyinf over all the values up until the last one.
        }

        // Free up space, assignment, decrement the size.
        delete [] p;
        this->p = copy;
        this->size--;
    }
}

/**
 * Inserts a new element as the idx-th index of the current vector;
 * if the index is out of bounds, nothing will occur.
 * @param idx: the index at which to insert the element.
 * @param x: the element to be inserted.
 */
void MyVector::insert(int idx, int x) {

    if (idx < this->size) {

        // Create copy pointer.
        int *copy = new int[this->size + 1];

        for (int i = 0, j = 0; i < this->size && j < this->size + 1; ++i, ++j) {

            if (j == idx) {
                copy[j++] = x;
            }

            // Copy of the typical values.
            copy[j] = p[i];

        }

        // Free memory, set to reference, update size.
        delete [] p;
        this->p = copy;
        this->size++;

    }

}

/**
 * Removes the index given from the vector if it is within range and not empty.
 * @param idx: index to remove from the vector.
 */
void MyVector::erase(int idx) {

    // Only runs if the vector is not empty and the index is within the range.
    if (this->size > 0 && idx < this->size) {
        int *copy = new int[this->size - 1];

        for (int i = 0, j = 0; i < this->size; ++i, ++j) {

            // If the indicies of the value are the same, skip the iteration.
            if (i == idx) {
                ++i;
            }

            // Copy over the normal values.
            copy[j] = p[i];
        }

        // Free up space, set the address for the heap, decerment the size.
        delete [] p;
        this->p = copy;
        this->size--;

    }
}

/**
 * Constructor: Initalize the pointer to null and size to 0.
 */
MyVector::MyVector() {
    this->p = NULL;
    this->size = 0;
}


// The main function has been completed for you.
// It is used to test your implmentation.
// You should not modify it (unless there is typo).
int main()
{
    MyVector x;
    int mode;
    int new_size, idx, data;
    int temp;
    cin >> mode; // This decides which function to test.
    cin >> new_size >> idx >> data;
// Mode 0: test push_back(), vsize() and at()
    if (mode == 0) {
        while (cin >> temp) {
            x.push_back(temp);
        }
        cout << x.vsize() << '\n';
        for (int i = 0; i < x.vsize(); i++) {
            cout << x.at(i) << '\n';
        }
    }
// Mode 1: test resize()
    else if (mode == 1)
    {
        while (cin >> temp) {
            x.push_back(temp);
        }
        x.resize(new_size);
        cout << x.vsize() << '\n';
        for (int i = 0; i < x.vsize(); i++) {
            cout << x.at(i) << '\n';
        }
    }
// Mode 2: test pop_back()
    else if (mode == 2) {
        while (cin >> temp) {
            x.push_back(temp);
        }
        x.pop_back();
        cout << x.vsize() << '\n';
        for (int i = 0; i < x.vsize(); i++) {
            cout << x.at(i) << '\n';
        }
    }
// Mode 3: test insert()
    else if (mode == 3) {
        while (cin >> temp) {
            x.push_back(temp);
        }
        x.insert(idx, data);
        cout << x.vsize() << '\n';
        for (int i = 0; i < x.vsize(); i++) {
            cout << x.at(i) << '\n';
        }
    }
// Mode 4: test erase()
    else if (mode == 4) {
        while (cin >> temp) {
            x.push_back(temp);
        }
        x.erase(idx);
        cout << x.vsize() << '\n';
        for (int i = 0; i < x.vsize(); i++) {
            cout << x.at(i) << '\n';
        }
    }
    else {
        cout << "Wrong Mode Input!";
    }
    return 0;
}
