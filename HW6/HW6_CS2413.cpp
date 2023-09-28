#include <iostream>
using namespace std;

// ========================================
// HW6: Implement Recursive Functions of
// Binary Search and Merge Sort
// ========================================
//
// In this assignment, we will implement
// a recursive function for binary search
// based on array, and another recursive
// function for merge sort based on singly
// linked list.
//
// The Node class (used to construct list)
// has been defined to you. Do not modify it.
//
// Do not define a linked list class for
// this assignment. In the main function,
// write a while loop to take inputs and
// use them to construct a linked list.
// Then, input this list (its head pointer)
// into the merge sort function. See the
// main function for detailed instructions.
//
// You cannot use any existing binary search
// or merge sort related functions or libraries.
//
// Here are two extra rules you need to follow:
//
// 1. The merge sort function should always
// sort input list in ascending order.
//
// 2. For binary search, if there are even number
// of elements in the list, always pick the mid-1
// element for comparison (with the search key).
// Note that there are five tasks in this template.


class Node{
public:
    void Set_SID(int x);
    int Get_SID();
    void Set_Pnext(Node *p);
    Node * Get_Pnext();
    Node();
private:
    int SID;
    Node* p_next;
};
void Node::Set_SID(int x) {
    SID = x;
}
int Node::Get_SID() {
    return SID;
}
void Node::Set_Pnext(Node* p) {
    p_next = p;
}
Node* Node::Get_Pnext() {
    return p_next;
}
Node::Node() {
    SID = -1;
    p_next = NULL;
}


// ----------------------------
// ---------- Task 1 ----------
// ----------------------------
//
// Complete the following recursive
// binary search function.
//
// The function takes a list as input,
// and outputs index of the search key
// in the list. It returns -1 if the
// key is not in the list.
//
// Input: you can design the input arguments
// in any way you like. Just don't forget to
// include a search key which is the key we
// aim to find. Also keep in mind that, at
// the end of all recursive calls, function
// should return the index of a matching key
// in the input array. For example, if the
// input array is x = {1, 3, 5, 7, 9} and
// the search key is 7, this BSearch function
// should return "3" in the main program
// because x[3] = 7. Also don't forget to
// design conditions for a failed search
// (return -1 in the main program).
//
// Important!!
// In every recursion, print out the number
// that is being compared with the search key.
// (Do not add any space.) For example, if the
// list is {1,2,3,4,5,6,7,8,9,10,11} and the
// search key is 2, then your function should
// print "6" in the first recursive call,
// print "3" in the second recursive call,
// print "1" in the third recursive call
// and print "2" in the last recursive call.
// So after BSearch is excuted in the main
// program, we should have "6312" printed out.
//
// Do not confuse the above print-out with
// the function's returned index. In the main
// program (mode 0), we will also print the
// returned index -- so printing "63121",
// where the last "1" is index of 2 in the list.
//

/**
   * Prior conditions: if there are an even number of elements in the list, always pick the midpoint-1 element for comparison with the search key; otherwise, just choose the midpoint.
   * First, find the midpoint of the list and determine if midpoint-1 is needed.
   * Second, compare with the key and find the midpoint of the shortend list.
   * Repeat this process until the search key is within range.
   * If found, return the index of the search key within the list.
   * If not found, return -1.
   * @param list the list to be searched.
   * @param key the search key to find in the list.
   * @param: from index to start searching the list from.
   * @param to index to stop searching from the list or sublist (boudary)
   * @return -1 if not found; the index of the search key if found.
   * @example if the list is x = {1,2,3,4,5,6,7,8,9,10,11}, the first call should print "6", the next recursive call should print "3", next "1", next "2", and finally return index = 1, since x[1] = 2.
 */
int BSearchN(int* list, int key, int from, int to) {

    // {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} 2
    // from = 0, to = 11, mid = 5
    // 6 > 2, 0, 5, 2,
    // 3 > 2, 0, 2, 0,
    // 1 < 2, 1, 2, 1,
    // 2 = 2, return middle p = 1

    // If it fails this, it is not found, return -1.
    if (from > to) return -1;

    // 1) Using the size of the list passed in, compute the midpoint; if even, use midpoint - 1.
    int middleP = from + (to - from) / 2;

//    if ((to - from) % 2 == 0) middleP--;

    // Print the value searched for the test order.
    cout << list[middleP];

    // 2a) If the key is found, return the index found at.
    if (list[middleP] == key) return middleP;

    // 2b) If the value is less than the key, search the right side of the list, assuming sorted.
    if (list[middleP] < key) {

        // Call the recursive function.
        return BSearchN(list, key, middleP + 1, to);
    }

    // 2c) If the value is greater than the key, search the left side of the list, assuming sorted.
    if (list[middleP] > key) {
        // Call the recursive function.
        return BSearchN(list, key, from, middleP-1);
    }

}



// ----------------------------
// ---------- Task 2 ----------
// ----------------------------
// Complete the following recursive merge
// sort function. The function takes a list
// as input, and outputs address of the
// head node of the sorted list.
// Input: you can design the input arguments
// in any way you like.

/**
 * Helper function for the merge part of the loop.
 * @param left: left sublist.
 * @param right: right sublist.
 * @return returns the new list.
 */
Node* Merge(Node* left, Node* right) {
    // If the left list is empty, or the right list is empty, return the opposite list.
    if (!left) return right;
    if (!right) return left;

    // Compare the left value with the right value; if the left is less than or equal, continue to merge.
    if (left->Get_SID() <= right->Get_SID()) {
        // Continue to merge by setting the next pointer to the right element, but check for each point.
        left->Set_Pnext(Merge(left->Get_Pnext(), right));
        return left;
    } else {
        // If the left side is greater, use the right side and connect the pointers.
        right->Set_Pnext(Merge(left, right->Get_Pnext()));
        return right;
    }
}

/**
 * Logic: takes in a linked list, say [11, 9, 1, 2, 0, 5], and puts it in order. Splits the list in half, in which it splits that list in half ... all
 * the way down to 2 elements, which it compares and boils back up.
 * @param head: head of the linked list.
 * @param size: size of the linked list.
 * @return address of the new head.
 */
Node* MSort(Node* head, int size) {

    // If the size is very small, meaning it is already sorted.
    if (!head || !head->Get_Pnext()) return head;

    // First, determine how to split the list; for now set like this, but even and odd sizes will be determined later.
    int split = size / 2;

    // Temp variables that will traverse through the linked list.
    Node* left = head;
    Node* right = NULL;

    // Split the list into two halves
    for (int i = 0; i < split - 1; i++) {
        head = head->Get_Pnext();
    }

    // Update the pointer at the half-way mark for the right-side
    right = head->Get_Pnext();
    head->Set_Pnext(NULL);

    // Left list recursive formula
    left = MSort(left, split);

    // Right list recursive, where size-split represents the right side of the list.
    right = MSort(right, size - split);

    // Merge the two lists given.
    return Merge(left, right);

}


int main() {

    // This array holds the list for binary search.
    int L1[11];

    // This is the head pointer which holds the list for merge sort.
    Node *L2 = NULL;

    // Read in data from the user.
    int mode, temp, key;
    cin >> mode >> key;

    // The first loop takes input for binary search. For simplicity, we assume there
    // are always 11 input integers that are unique and sorted in ascending order.
    // You can definitely write additional code in the binary search function
    // to check the validity of these assumptions, but the test cases on Canvas will satisfy the assumptions.
    for (int i = 0; i < 11; i++) {
        cin >> L1[i];
    }


// ----------------------------
// ---------- Task 3 ----------
// ----------------------------

// The second loop takes input for merge
// sort. This task is the same as the task in hw4.
// The head pointer "L2" has been declared above for you. Use it
// to store head of the constructed list. You can also declare extra pointers
// or nodes as necessary.

    // Pointer used to point to the head.
    Node *tempPointer = NULL;
    int size = 0;
    while (cin >> temp) {

        // Declare a new node.
        tempPointer = new Node;

        // Assign the value attached to it, given "temp" as the SID.
        tempPointer->Set_SID(temp);

        // Insert the data into the head and update the head in order to create the links.
        tempPointer->Set_Pnext(L2);
        L2 = tempPointer;

        // Update the size that will be passed in.
        size++;

    }


// -----------------------------------
// Start testing your implementation.
// -----------------------------------

   // Mode 0: test BSearch()
   if (mode == 0) {
        // Task 4: apply binary search, where input should be "L1" (search list), "key" (search key), and the size.
        int val = BSearchN(L1, key, 0, 10);
        cout << val;
    }


// Mode 1: test MSort()
    if (mode == 1) {
// Task 5: apply merge sort.
// One input should be "L2" (input list)
        L2 = MSort(L2, size);
        Node *temp = L2;
        while (temp != NULL) {
            cout << temp->Get_SID();
            temp = temp->Get_Pnext();
        }
    }
    return 0;

}