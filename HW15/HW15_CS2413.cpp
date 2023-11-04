// ========================================
// HW15: Implement Min Heap
// ========================================
//
// In this assignment, we will implement
// a Min Heap. You can choose to implement
// it based on linked-list or array.
//
// The provided template assumes array-based
// implementation, but feel free to modify
// it as needed. Just make sure to keep the
// in/output (format) of all functions that
// are tested in the main function.
//
// Your major task is to implement the heap
// class. In addition, in the main function,
// test mode 3, you need to implement an
// application of your heap to sort an array
// of nodes based on their keys.

// Additional Context: the min-heap class is a complete binary tree with
// the property that any node is smaller than its descendent nodes.
// It is not necessarily a BST, as there is no relation between two child nodes.


#include <iostream>
#include <queue>
using namespace std;

// Array Implementation Chosen.
class Node {
private:
    int key;
    Node* left;
    Node* right;
    Node* parent;
public:
    void Set_key(int x);
    void Set_left(Node* p);
    void Set_right(Node* p);
    void Set_parent(Node* p);
    Node* Get_left();
    Node* Get_right();
    Node* Get_parent();
    int Get_key();
    Node();
};
Node::Node() {
    key = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
}
void Node::Set_key(int x) {
    key = x;
}
int Node::Get_key() {
    return key;
}
void Node::Set_left(Node* p) {
    left = p;
}
void Node::Set_right(Node* p) {
    right = p;
}
void Node::Set_parent(Node* p) {
    parent = p;
}
Node* Node::Get_left() {
    return left;
}
Node* Node::Get_right() {
    return right;
}
Node* Node::Get_parent() {
    return parent;
}

// The MinHeap class has been structured for you.
// Please complete the functions and feel free
// to add variables or functions to facilitate
// your own designs and implementations.
//
// However, Add, Remove and Root functions must
// be implemented based on the given definitions
// (because we test them in the main function).

/**
 * A min heap is a complete binary tree with the property that any node is smaller than is descendant.
 */
class MinHeap {
private:
    Node* root;
    Node** arr;
    int ArraySize;
    int HeapSize;
    void BSTraverseHelper(Node* root);
public:
// This function prints keys in the
// heap based on breadth-first traverse
// (do not add space between keys;
// do not change line at any time).
// You may use a modified version of
// the BS traverse function in HW10.
    void BSTraverse();
// This function adds a node
// at address p to the heap.
    void Add(Node* p);
// This function removes root.
    void Remove();
// This function returns root.
    Node* Root();
// This function resizes the array for an array-based min heap.
    void ArrayResize(int n);
// You can design the constructor
// in any way you like e.g., you
// may initialize heap size to
// zero or to some large enough
// In the latter case, you should
// properly mark unused array cells.
    MinHeap();
};

/**
 * ONLY USED FOR LINKED LIST IMPLEMENTATION, WHICH WAS NOT USED.
 * Helper function for the breadth-first traverse function: left, root, right.
 * @param root root passed in to compute the traverse.
 */
void MinHeap::BSTraverseHelper(Node *root) {

    // 0): Define the queue and add the head "root" to the queue.
    queue<Node*> q;
    q.push(root);

    // 1): Loop over the queue until it is empty.
    while (!q.empty()) {

        // a): Store the queue front node.
        Node *temp = q.front();
        q.pop();

        // b): Visit the root, left, and right.
        cout << temp->Get_key();

        // c): Remove the root and add in the children.
        if (temp->Get_left() != nullptr) q.push(temp->Get_left());
        if (temp->Get_right() != nullptr) q.push(temp->Get_right());

    }

}

/**
 * Prints the keys in the heap based on breadth-first traverse.
 * Similar function from HW10, but this one will utilize a helper function.
 */
void MinHeap::BSTraverse() {
    // Simply pass in the root to the helper.
    // BSTraverseHelper(this->root);

    // Array version, simply loop.
    for (int i = 1; i < ArraySize; ++i) {
        cout << this->arr[i]->Get_key();
    }
}

/**
 * Adds a node at address p to the heap.
 * @param p the node to be added.
 */
void MinHeap::Add(Node *p) {
    // 1): Begin by checking if the array must be resized.
    if (this->ArraySize == this->HeapSize) ArrayResize(this->ArraySize * 2);

    // 1.5): If the root it null, then this will be the first element,
    if (this->root == nullptr) this->root = p;

    // 2): If not, simply add the "p" to the end of the array.
    this->arr[this->ArraySize] = p;

    // 3): Now, check for any violations of the min-heap tree and fix them.
    // Begin by checking the parent x[i/2], where x is an array and i is the current index.
    // From there, continue checking up the chain until there is no break (loop).

    // a): Hold the current position for the loop.
    int currentPosition = this->ArraySize;

    // b): Loop until the root or the property breaks.
    while (true) {

        // Only need one pointer, since the current is "p", where we store the parent.
        int newPos = (currentPosition / 2);
        Node* parent = this->arr[newPos];

        // Guard clause to break out.
        if (parent == nullptr || newPos == 0 || parent->Get_key() <= p->Get_key()) break;

        // Swap the parent and the child (upwards) & check if the parent is the root.
        this->arr[newPos] = this->arr[currentPosition];

        if (parent == this->root) this->root = this->arr[newPos];

        // Swap the child and the parent (downwards)
        this->arr[currentPosition] = parent;

        // Update current position.
        currentPosition /= 2;
    }

    // 4): Increment the array size.
    ++this->ArraySize;

}

/**
 * Removes the root node and updates the heap.
 */
void MinHeap::Remove() {
    // 1): If the heap is empty, return.
    if (ArraySize <= 1) {
        root = nullptr;
        return;
    }

    // 2): Replace the root with the last node in the array.
    arr[1] = arr[ArraySize - 1];

    // 3): Update heap size.
    --ArraySize;

    // 4): Restore the min-heap property starting from the root.
    int currentPos = 1;
    while (true) {
        int leftChildPos = currentPos * 2;
        int rightChildPos = currentPos * 2 + 1;
        int smallest = currentPos;

        // Compare with left child.
        if (leftChildPos < ArraySize && arr[leftChildPos]->Get_key() < arr[smallest]->Get_key()) {
            smallest = leftChildPos;
        }

        // Compare with right child.
        if (rightChildPos < ArraySize && arr[rightChildPos]->Get_key() < arr[smallest]->Get_key()) {
            smallest = rightChildPos;
        }

        // If the current node is smaller than or equal to its children, stop.
        if (smallest == currentPos) {
            break;
        }

        // Swap current node with the smallest child.
        Node* temp = arr[currentPos];
        arr[currentPos] = arr[smallest];
        arr[smallest] = temp;

        // Move down the tree.
        currentPos = smallest;
    }

    // Update the root.
    root = arr[1];
}

/**
 * Double the size of the heap, based on the value passed in.
 * Copy over all the elements to another dynamically allocated memory slot and delete the previous.
 * @param n the new heapsize.
 */
void MinHeap::ArrayResize(int n) {

    // 1): Begin by defining new memory allocation with the given size.
    this->HeapSize = n;
    Node** res = new Node*[this->HeapSize];

    // 2): Copy over all the elements (unit indexed).
    for (int i = 1; i < this->ArraySize; ++i) {
        res[i] = this->arr[i];
    }

    // 3): Free up memory by deleting the old array and reassign it.
    delete [] this->arr;
    this->arr = res;
}

/**
 * Returns the root of the min-heap tree.
 * @return the root.
 */
Node *MinHeap::Root() {
    return this->root;
}

/**
 * Constructor that initializes the root and private data.
 */
MinHeap::MinHeap() {
    this->root = nullptr;
    this->HeapSize = 10;

    // Unit-indexed.
    this->ArraySize = 1;
    this->arr = new Node*[this->HeapSize];
}

int main()
{
// mode:test mode
// key: keys of nodes to be added to heap
    int mode, key;
    cin >> mode;
// Adding nodes to heap.
    MinHeap heap;
    Node* temp;
    while (cin >> key) {
        temp = new Node;
        temp->Set_key(key);
        heap.Add(temp);
    }
// Mode 0: test Add()
    if (mode == 0) {
        heap.BSTraverse();
    }
// Mode 1: test Root()
    else if (mode == 1) {
        temp = heap.Root();
        cout << temp->Get_key();
    }
// Mode 2: test Remove()
    else if (mode == 2) {
        heap.Remove();
        heap.BSTraverse();
    }
// Mode 3: implement heap sort.
    else if (mode == 3) {
// First construct an array of nodes.
// The keys are 5, 4, 3, 2, 1 in "arr".
// Do not modify this part.
        Node arr[5];
        for (int i = 0; i <= 4; i++) {
            arr[i].Set_key(5-i);
        }

        // Now, write codes that apply your
        // heap to sort the nodes in "arr"
        // in ascending order (and place them
        // back in "arr").

        for (int i = 4; i >= 0; i--) {
            // a): Create a new node, set the key to the array key, and add it to the minheap..
            Node* var = new Node;
            var->Set_key(arr[i].Get_key());
            heap.Add(var);
        }

        // Reset the array elements with the sorted values.
        for (int i = 0; i < 5; i++) {
            arr[i].Set_key(heap.Root()->Get_key());
            heap.Remove(); // Remove the root element from the heap.
        }

// At last, we print keys in arr.
// They should be 1, 2, 3, 4, 5.
// Do not modify this part.
        for (int i = 0; i < 5; i++) {
            cout << arr[i].Get_key();
        }
    }
    return 0;
}