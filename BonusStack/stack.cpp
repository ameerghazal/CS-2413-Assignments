#include <iostream>
using namespace std;

class MyStack {
private:
    int* stack;
    int itop;
    int capacity;
public:
// This function pushes x into the stack.
// Push should always be successful even
// if the stack array is currently "full".
    void push(int x);
// This function removes the top element
// in the stack. It does nothing if the
// stack is empty.
    void pop();
// This function returns the top element
// in the stack. It returns -1 if the stack
// is empty.
    int top();
// This function returns number of elements
// in the stack. Note this means it should
// return 0 if the stack is empty.
    int Ssize();
// This function is given to you.
// It initializes a small array.
// Do not modify it.
    MyStack();
};

/**
 * Constructor function which initializes the stack capacity and the top counter.
 */
MyStack::MyStack() {
    stack = new int[2];
    itop = -1;
    capacity = 2;
};

/**
 * Push function that will push a value 'x' into a array-implemented stack, with a last in, first out structure.
 * @param x the value to be pushed into the stack.
 */
void MyStack::push(int x) {


    if (itop > capacity) {

        // Increase the capacity by 5, create a new array, and update the old capacity size.
        int newCap = capacity + 5;
        capacity = newCap;
        int* stackNew = new int[capacity];

        // Copy over the elements from the old stack
        for (int index = 0; index < Ssize(); ++index) {
            stackNew[index] = this->stack[index];
        }

        // Free up old space
        delete[] stack;

        // Reassign the stack pointer to the new stack with a higher capacity.
        this->stack = stackNew;
    }

    // Assign the last value using the updated stack size to the value passed in, while updating the itop tracker.
    this->stack[++itop] = x;

};

/**
 * Removes the top element in the stack if not-empty; otherwise, nothing happens.
 */
void MyStack::pop() {

    // Only runs the statement if the stack is not-empty.
    if (Ssize() != 0) {

        // Create a new copy with the same capacity.
        int* stackNew = new int[capacity];

        // Copy over the elements at the size - 1, leaving off the popped element.
        for (int index = 0; index < Ssize() - 1; ++index) {
            stackNew[index] = this->stack[index];
        }

        // Free up old space
        delete[] stack;

        // Update the stack pointer
        this->stack = stackNew;

        // Decrement the head index "counter".
        --itop;
    }
}

/**
 * Returns the top element from the stack, and it follows the last-in, first-out principle, but does not remove it.
 * If the last element inserted was 'c', then the top element output would be 'c'.
 * @return the top element from the stack, which would be the last one inserted; however, if empty, -1 is returned.
 */
int MyStack::top() {

    // Base case: if the stack is empty, return -1.
    if (Ssize() == 0) return -1;

    // Otherwise, return the top element, which is the element that had just been inserted.
    return this->stack[this->itop];

}

/**
 * Returns the size of the stack, not the capacity!
 * @return size of the stack utilizing the index of the last-in element.
 */
int MyStack::Ssize() {
    // Base case if the stack is empty.
    if (this->itop == -1) return 0;

    // Otherwise return the current index of the last stack element, to make up for the 0-indexed first element.
    return (this->itop + 1);
}


int main()
{
    MyStack x;
    int temp;
    while (cin >> temp) {
        x.push(temp);
    }

    // Bug update from the template canvas.
    int inputSize = x.Ssize();
    for (int i = 0; i < inputSize; i++) {
        cout << x.top() << '\n';
        x.pop();
    }
    return 0;
}