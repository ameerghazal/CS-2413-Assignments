#include <iostream>
using namespace std;

// ========================================
// HW4: Implement a Singly List Class
// ========================================
//
// In this assignment, we will implement
// a singly linked list class based on
// a node class.
//
// The Node class has been defined to you.
// Do not modify it.
//
// The List class has been partly defined
// for you. It has one private variable
// "head" and several public functions.
// The constructor and Print function have been
// defined for you (do not modify them), and
// your task is to implement other functions.
//
// You can add new member functions to the
// List class but not new member variables.
// In addition, you cannot use any existing
// list-related library or function.


class Node {
private:
    int SID;
    float GPA;
    Node* p_next;
public:
    void Set_SID(int x);
    void Set_GPA(float y);
    int Get_SID();
    float Get_GPA();
    void Set_Pnext(Node* p);
    Node* Get_Pnext();
    Node();
};
void Node::Set_SID(int x) {
    SID = x;
}
void Node::Set_GPA(float y) {
    GPA = y;
}
int Node::Get_SID() {
    return SID;
}
float Node::Get_GPA() {
    return GPA;
}
void Node::Set_Pnext(Node* p) {
    p_next = p;
}
Node* Node::Get_Pnext() {
    return p_next;
}
Node::Node() {
    SID = -1;
    GPA = -1;
    p_next = NULL;
}


// The List class has been partly defined for you.
// Complete its undefined member functions.
class List {
private:
    Node* head;
public:
// List function is defined for you.
    List();
// Print function is defined for you.
    void PrtSID();


// Create function creates a singly linked
// list based on our inputs and assigns its
// head node's address to the "head" pointer.
//
// To be specific, when we run Create(),
// the program should wait for us to input
// the SID and GPA of an arbitrary number
// of students. After Create() is done,
// the linked list should have been created
// and accessible through "head".
//
// The format of input should be as follows:
// sid_1 gpa_1 sid_2 gpa_2 sid_3 gpa_3 ......
//
// Here, sid_i and gpa_i are SID and GPA of
// the i_th input student. A new node is always
// added to the head of the list.
//
// Note that this hw does not require you to
// check duplication of the input/inserted SID's
// for simplicity. But we should always assume
// SID is unique for each student.
//
// Finally, the process should terminate when
// an invalid input is given. Note that it is
// assumed we always input a pair of valid
// sid and gpa for a new student, so there is
// no need to deal with the case of a valid sid
// followed by an invalid gpa.
//
// If you are still confused about this function,
// check how it is used in the main program.
    void Create();
// Lsize function returns the number
// of nodes in the list. Return 0 if
// the list is empty.
    int Lsize();
// Find function returns address of
// the node in the list whose SID = key.
// Return NULL if no match is found.
    Node* Find(int key);
// Insert function inserts a new node
// (whose address is stored at "p")
// as the idx_th node in the list.
// Return 1 if insertion is successful
// and return -1 if idx is out of range.
// A valid range is [1, Lsize+1],
// where "1" means adding to head
// and "Lsize+1" means adding to tail.
    int Insert(Node* p, int idx);
// Remove function removes the idx_th
// node from the list. Return 1 if
// removal is successful and -1 if
// idx is out of range.
// A valid range is [1, Lsize],
// where "1" means removing head
// and "Lsize" means removing tail.
    int Remove(int idx);
// Reverse function reserves the list.
// For example, if the current list has
// three nodes A->B->C, after running
// Reverse the order should be C->B->A.
// As another example, if we call the
// print function and get 246, after
// running Reverse we should get 642.
    void Reverse();
// Clear function removes all nodes from
// the list (so it becomes an empty list).
    void Clear();
};

/**
 * Constructor, which initializes the head to null.
 */
List::List() {
    head = NULL;
}

/**
 * Prints the SID contents of the node.
 */
void List::PrtSID() {
    Node* temp = head;
    while (temp != NULL)
    {
        cout << temp->Get_SID();
        temp = temp->Get_Pnext();
    }
}

/**
 * Prompts the user to input an arbitrary number of students, in which the user will define the SID and GPA for the students.
 */
void List::Create() {

    // Declare the head, temp, and previous nodes
    Node* temp = NULL; // will be updated throughout the loop.
    Node* prev = NULL; // used for connecting links between temp and the previous link.


    // Declare the gpa and sid to be read in, and keep track of the size.
    int SID;
    float GPA;
    int size = 0;

    // Loop over until the GPA or SID inputs are not int's or floats (respectivley).
    while (cin >> SID >> GPA) {

        // Create a new node by using the temp pointer.
        temp = new Node;

        // Initialize the node data (gpa and sid) with the given inputs.
        temp->Set_SID(SID);
        temp->Set_GPA(GPA);

        // According to the prompt, insert the data into the head, meaning we need to create the links and update the head.
        temp->Set_Pnext(head);
        head = temp;




        /**
         * Adding to the tail


        // At this point, the new node is created; therefore, we must create the links.

        // First, check if it is the head (first element).
        if (size == 0) {
            head = temp; // set the head to node
           // head->Set_Pnext(NULL); // set the next pointer to null, until it is reassigned later.
            prev = temp;
        } else {
            // If it is not the head element, connect the current node to the previous node link
            // and reassign the previous link for the next iteration.

            // Set the previous node's next pointer to the current node address.
            prev->Set_Pnext(temp);

            // Now, assign the previous node to the current one to prepare for the next iteration.
            // If no other iteration occurs, the prev (current, technically) next ptr will be null.
            prev = temp;
        }

        // Increment the size for the next iteration.
        size++;

          */

    }

}

/**
 * Returns the size of the node.
 * @return: returns the size of the linked list.
 */
int List::Lsize() {

    // Set the initial size to 0
    int size = 0;

    // Temp pointer to the head.
    Node* temp = head;

    while (temp != NULL) {
        temp = temp->Get_Pnext();
        size++;
    }

    // Return the size.
    return size;


}

/**
 * Find the address of the node in the list whose SID = key.
 * @param key
 * @return returns the address if the SID = key, or null if nothing is found.
 */
Node* List::Find(int key) {

    // Start the pointer at the head.
    Node* temp = head;

    while (temp != NULL) {
        // If the node value's sid equals the key, break out and return the temp.
        if (temp->Get_SID() == key)
        {
            break;
        }

        temp = temp->Get_Pnext();
    }

    return temp; // return the address of the node, or it will return null.
}

/**
 * Inserts a node at a specific index into the list.
 * @param p: Node to be inserted into the list.
 * @param idx: Index at where to insert the node.
 * @return: returns -1 if the insert did not go through, and 1 if it went through.
 */
int List::Insert(Node *p, int idx) {

    // Traverse to the correct index. Say 3>4>5 is the node and we want to insert at index 1.
    // Traverse to index 1 (element 4), connect the node to the "4" node as the first link,
    // Then link the node to the previous node (3).

    // First, check if the index is in bounds; if not, return -1, indicating a fail.
    if (idx < 0 || idx > Lsize() + 1) return -1;

    // Create a temp pointer for traversing, starting at the head of the list. Also, a previous pointer for the previous node.
    Node* temp = head;
    Node* prev = NULL;
    int index = 1; // checks the index to see if matching.

    /*
     *
     * We want to insert the node given at the index, meaning we iterate in order to set the temp and previous pointer properly.
     * Once the correct index is found, the nodes should be pointer to their respective data nodes. From there, attach the links.
     * Example: 1->3->4->8, where *p points to Node w/ SID = 19, idx = 2. Should insert after node 3 before node 4.
        1st iteration: temp = head, prev = null, index = 0 (0<=2)
        2nd iteration: prev = 1, temp = 3, index = 1 (1<=2)
        3rd Iteration: prev = 3, temp = 4, index = 2 (2<=2)

    Stop after the third iteration as the prev. pointer is set and the temp is set. Connect the link to the next node
    and the previous node.

    */

    // First case, inserting to the head.
    if (idx == 0) {
        // Attach the link to the current head.
        p->Set_Pnext(temp);

        // Update the head.
        head = p;
    } else {

        // Iterate until the pointers point to the proper pre-idx and post-idx nodes.
        while (index < idx) {

            // Reassign the prev node, to the current temp node
            prev = temp;

            // Reassign the temp pointer to the next node.
            temp = temp->Get_Pnext();

            // Increment the index
            ++index;

        }

        // Attach the "B" link to the given node first.
        p->Set_Pnext(temp);

        // Attach the "A" link to the given node last.
        prev->Set_Pnext(p);

    }


    // Return 1, to indicate the node has been inserted
    return 1;

}

/**
 * Remove function removes the index from the list. Return 1 if successful and -1 if out of range.
 * A valid range is [1, Lsize], where 1 means removing the head and Lsize means removing the tail.
 * @param idx: a valid range is [1, Lsize].
 * @return:1 if successful, -1 is unsuccessful.
 */
int List::Remove(int idx) {

    // If the index is out of bounds, return -1 for failure.
    if (idx < 0 || idx > Lsize()) return -1;

    // Pointers to track previous and next nodes for traverse.
    Node* temp = head;
    Node* prev = NULL;
    int index = 1;

    // Case 1: Deletion from the head.
    if (idx == 0) {
        // Update the head
        head = temp->Get_Pnext();

        // Free up the previous space.
        delete temp;
    } else if (idx == Lsize()) {
        // Case 2: Removing from the tail

        // Iterate until the next next pointer is null. For example, 1>4>5>6 where temp would get to 5 and stop reassigning.
        // Only problem with this is it does not free up the "removed" index space. For this, we could utlilze another pointer.
        while (temp->Get_Pnext()->Get_Pnext() != NULL) {
            // Assign previous pointer to the prev., value
           // prev = temp;

            // Update temp for next iteration.
            temp = temp->Get_Pnext();
        }

        temp->Set_Pnext(NULL); // set the next pointer to null, indicating the stop.
    } else {

        // Iterate until the pointer are set properly
        while (index < idx) {

            // 1-> 2 -> 3 rem. 1; 1 2

            // Reassign the prev node, to the current temp node
            prev = temp;

            // Reassign the temp pointer to the next node.
            temp = temp->Get_Pnext();

            // Increment the index
            ++index;

        }

        // Now, the previous pointer points to the node before idx_th node. And the temp pointer points
        //  to the node we want to remove.

        // First, update the link of the prev. to the pointer after the current temp.
        prev->Set_Pnext(temp->Get_Pnext());

        // Then, free up the temp space.
        delete temp;


    }






    // Return 1 indicating the insertion went through.
    return 1;



}

/**
 * Reverses the list.
 * If the current list has three nodes A->B->C, after running, the reverse order should be C->B->A.
 */
void List::Reverse() {

    // Temp pointers
    Node *temp = head; // starts at first index
    Node *next = NULL; // starts at 2nd index.
    Node *prev = NULL; // starts at "negative" index.

    /*
     * Logic: Start with 3 pointers. One starting out as Null (previous), one as the next element (one after the head to start) and one pointing to the head (temp).
     * Have (temp) the starting element point to the (prev) element (which would be null from the start, as it is now the tail). From the next iteration, shift everything down one.
     * So the prev will now point to the temp. The temp will now point to the "next". And next will now point to the next node.
     * Ex: 1->2->3->4
     * Process, prev = NULL, temp = Node "1", next = Node "2".
     * After one iteration, NULL<-1 2->3->4, where prev = "1", temp = "2", next = "3"
     * After 2nd iteration, NULL<-1<-2 3->4, where prev = "2", temp = "3", next = "4"
     * After 3rd iteration, NULL<-1<-2<-3 4, where prev = "3", temp = "4", next = "NULL"
     * After 4th iteration, NULL<-1<-2<-3<-4, where prev = "4", temp = "NULL", next = "NULL"
     * Iterations are done, so we update the head to the positon of "prev"; furthermore, reversing the list, as the output would be 4->3->2->1
     */
    while (temp != NULL) {

        // Update the value of next
        next = temp->Get_Pnext();

        // Set the temp (head at the start)'s next pointer to the previous value, which would be NULL to start as it is now the tail.
        temp->Set_Pnext(prev);

        // More all the pointer to their next nodes: prev to temp, temp to next, next to (the next value).
        prev = temp; // moves from "Null" to previous head.
        temp = next; // moves from previous head to the "2nd" index.

    }

    // Update the head
    head = prev;
}

/**
 * Removes all the nodes, making it an empty list, size = 0.
 */
void List::Clear() {

    // Loop until the head is null, meaning the linked list has been cleared.
    while (head != NULL) {
        // Temp pointer, pointing to the head of the list.
        Node *temp = head;

        // Reassign the head to the next node, which is checked in the next iteration.
        head = head->Get_Pnext();

        // Free up the memory taken by the temp pointer, which internally removes the node.
        delete temp;
    }
}



int main()
{
    int mode, key, sid, idx;
    float gpa;
// The first five inputs are for testing.
// "mode" determines which function to test.
// "key" is used to evaluate Find().
// "sid" and "gpa" are used to evaluate Insert().
// "idx" is used to evaluate Insert() and Remove().
//
// After these inputs, the rest inputs are used
// to create the initial singly linked list.
    cin >> mode >> key >> sid >> gpa >> idx;
// declare a singly linked list named "x"
    List x;
// input data to x.
// After this, a list should be created
// and stored at address "head".
    x.Create();
// Mode 0: test Create()
    if (mode == 0) {
        x.PrtSID();
    }
// Mode 1: test Lsize()
    else if (mode == 1) {
        cout << x.Lsize();
    }
// Mode 2: test Find()
    else if (mode == 2) {
        Node* temp = x.Find(key);
        if (temp == NULL) {
            cout << -1;
        }
        else {
            cout << temp->Get_GPA();
        }
    }
// Mode 3: test Insert()
    else if (mode == 3) {
        Node* temp = new Node;
        temp->Set_SID(key);
        temp->Set_GPA(3.5);
        x.Insert(temp, idx);
        x.PrtSID();
    }
// Mode 4: test Remove()
    else if (mode == 4) {
        x.Remove(idx);
        x.PrtSID();
    }
// Mode 5: test Reverse()
    else if (mode == 5) {
        x.Reverse();
        x.PrtSID();
    }
// Mode 6: test Clear()
    else if (mode == 6) {
        x.Clear();
        cout << x.Lsize();
    }
    return 0;
}