//
// ========================================
// HW10: Implement Binary Tree Traverse
// and Data Structure Conversion
// ========================================
//
// In this assignment, we will implement four
// traverse algorithms on a given list-based
// binary tree, and one function that coverts
// this tree into an array-based tree. We will
// also implement a function that measures the
// height of a list-based tree (for conversion).
//
// The binary tree has been constructed for you.
// It is almost the same as the example tree in
// lecture, except we use key=0 to indicate empty
// node. Do not modify it. (We will practice tree
// class and related operations in future hw's.)
//
// You should implement three functions.

#include <iostream>
#include <cmath>

// Used for the breadth first-implementation.
#include <queue>

using namespace std;
class Node {
private:
    int key;
    Node* left;
    Node* right;
    Node* parent;
public:
    void Set_key(int x);
    int Get_key();
    void Set_left(Node* p);
    void Set_right(Node* p);
    void Set_parent(Node* p);
    Node* Get_left();
    Node* Get_right();
    Node* Get_parent();
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


//
// -------------------------------
// ---------- Task 1 -------------
// -------------------------------
// Please implement the following Traverse
// function, which can perform pre-order,
// post-order and in-order traverse as well
// as breadth-first traverse, depending on
// the input string "s".
//
// Input "s" expects value in {"pre","post","in","bf"}
// "pre" means pre-order traverse
// "post" means post-order traverse
// "in" means in-order traverse
// "bf" means breadth-first traverse
// If any other value of "s" is input,
// just print "-1" (without recursion).
//
// Input "p" should point to the node
// being visited, but you are free to
// use it in any other way.
//
// You don't have to implement the (incomplete)
// algorithm described in lecture slides.
// You are welcome to come up with your own
// design -- as long as they are correct.
//
// Finally, after visiting every non-empty
// node, you should print its key value
// using "cout << p->Get_key();".
// Do not add space or any other character
// in the printout. Just print key.
//
void Traverse(Node* p, string s) {

    // Base case.
    if (p == nullptr) return;

    // Case 1: pre-order traverse (root -> left tree -> right tree)
    if (s == "pre") {
        // 1): Visit the root note.
        cout << p->Get_key();

        // 2): Visit the left subtree, recursively, by passing in the left node.
        Traverse(p->Get_left(), "pre");

        // 3): Visit the right subtree, once the left has been searched, by passing in the right node.
        Traverse(p->Get_right(), "pre");
    }

    // Case 2: post-order (left tree -> right -> root)
    if (s == "post") {

        // 1): Visit the left subtree, recursively, by passing in the left node (goes to the left-most tree.
        Traverse(p->Get_left(), "post");

        // 2): Visit the right subtree.
        Traverse(p->Get_right(), "post");

        // 3): Visit the root node.
        cout << p->Get_key();

    }

    // Case 3: in-order traverse (left -> root -> right)
    if (s == "in") {
        // 1): Visit the left subtree, recursively, by passing in the left node (goes to the left-most tree.
        Traverse(p->Get_left(), "in");

        // 2): Visit the root node.
        cout << p->Get_key();

        // 3): Visit the right subtree.
        Traverse(p->Get_right(), "in");
    }

    // Case 4: Breadth-first traverse. Goes in order from left to right on the subtree.
    if (s == "bf") {

        // 0): Define the queue and add the head "root" to the queue.
        queue<Node*> q;
        q.push(p);

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

}

//
// -------------------------------
// ---------- Task 2 -------------
// -------------------------------
// Please implement the following Height
// function, which measures height of a
// list-based tree.
//
// Input "root" points to the root node
// of the tree. The function returns an
// integer which is height of the tree.
//
// You are free to design any algorithm
// that measures the height (correctly).
// You are also welcome to design any
// additional (recursive) functions
// that are called by Height.
//

/**
 * Traverse through the list to the max height and return it.
 * @param root points to the root node - at the start, the head.
 * @return returns the height of the BST.
 */
int Height(Node* root) {

    // Logic: Search both sublists for the max height; compare the left sublist height with the right sublist height. Return the greater one.

    // Base Case: if the node is null, it signifies the end of the sublist.
    if (root == nullptr) {return -1;}

    // Recursive Case: Start by searching the left list fully, below will be the return case.
    int leftHeight = Height(root->Get_left());
    int rightHeight = Height(root->Get_right());

    // Increment step. For example, the run will go all the way to the of the left list and right list.
    // From there, we boil back up. So we take the current height and increment by 1, based on which is bigger.
    // This will boil up to the top, where the largest one will eveuntually be returned.
    if (leftHeight > rightHeight)
        return (leftHeight+1);
    else
        return (rightHeight+1);
}
//
// -------------------------------
// ---------- Task 3 -------------
// -------------------------------
// Please implement the following Convert
// function, which converts a list-based
// tree into an array-based tree.
//
// This function takes two inputs.
// 1."root" is a pointer to the root node
// of the given list-based tree.
// 2."height" is height of the tree
// (returned by your Height function).
//
// The function returns a pointer
// of an object array which holds
// the tree.
//
// -----------------
// --- Important ---
// -----------------
// Size of the array can be determined
// autmatically based on input height.
//
// In fact, the maximum possible number
// of nodes in a tree is determined by
// its height. (We will cover this in
// future lectures.) This means, we
// can predict the largest necessary
// size of the array needed to hold
// all possible nodes in a tree.
//
// For now, just follow this rule:
// ArraySize = 2^(height+1) - 1
//
// ("2^x" means 2 to the power of x)
// (You can use the "pow" function
// to compute power. See test mode 5
// as an example.)
//
Node* Convert2Array(Node* root, int height) {

    // 0): Deduce the size of the array based on the height.
    int arraySize = pow(2, height + 1) - 1;

    // 1): Create the array to store the data and a index for the loop..
    Node* array = new Node[arraySize];
    int index = 0;


    // 2): Fill in the array through a breadth-first approach.

    // a): Define the queue and add the head "root" to the queue.
    queue<Node*> q;
    q.push(root);

    // b): Loop over the queue until it is empty.
    while (!q.empty() && index < arraySize) {

        // c): Store the queue front node and then remove it from the queue.
        Node *temp = q.front();
        q.pop();

        // d): Add the node to the array.
        array[index].Set_key(temp->Get_key());

        // e): Add the left child then the right child into the queue for the next loop runs.
        if (temp->Get_left() != nullptr) q.push(temp->Get_left());
        if (temp->Get_right() != nullptr) q.push(temp->Get_right());

        ++index;
    }

    // 3): Return a pointer to the array, which is the head.
    return array;
}



// There is nothing you need to do
// in the main function.
int main()
{
// Constructing a binary tree.
    Node A, B, C, D, E, F, G;
    A.Set_key(5);
    B.Set_key(4);
    C.Set_key(2);
    D.Set_key(11);
    E.Set_key(9);
    F.Set_key(12);
    G.Set_key(7);
    A.Set_left(&B);
    A.Set_right(&C);
    B.Set_left(&D);
    B.Set_right(&E);
    C.Set_left(&F);
    C.Set_right(&G);
    B.Set_parent(&A);
    C.Set_parent(&A);
    D.Set_parent(&B);
    E.Set_parent(&B);
    F.Set_parent(&C);
    G.Set_parent(&C);
    Node* root = &A;
// Input test mode.
    int mode;
    cin >> mode;
// Mode 0: test pre-order traverse
    if (mode == 0) {
        Traverse(root, "pre");
    }
// Mode 1: test post-order traverse
    else if (mode == 1) {
        Traverse(root, "post");
    }
// Mode 2: test in-order traverse
    else if (mode == 2) {
        Traverse(root, "in");
    }
// Mode 3: test breadth-first traverse
    else if (mode == 3) {
        Traverse(root, "bf");
    }
// Mode 4: test Height function
    else if (mode == 4) {
        cout << Height(root);
    }
// Mode 5: test Convert2Array function
    else if (mode == 5) {
        Node *arr = Convert2Array(root, Height(root));
        for (int i = 0; i < pow(2, Height(root) + 1) - 1; i++) {
            cout << arr[i].Get_key();
        };
    }
    return 0;
}