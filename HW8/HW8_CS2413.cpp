#include <iostream>
using namespace std;

// ========================================
// HW8: Implement Hash Table with the
// Coalesced Chaining Technique
// ========================================

// In this assignment, we will implement a
// hash table which uses coalesced chaining
// to deal with conllisions. The chains should
// be implemented using singly linked list.

// The Node class (used to construct chain)
// has been defined to you. Do not modify it.

// *********************************************
// Note this Node class is slightly different
// from the ones we have been working with.

// When constructing a chain, instead of using
// a pointer "p_next" to hold address of the
// next node, it uses an integer "idx_next" to
// hold position of the next node in the table.
// For example, if an object's idx_next = 2,
// it means the next node on the chain is
// stored at table[2]. If idx_next = -1,
// it means the object is tail of the chain.
// *********************************************

// Your task is to implement a HashTable class
// based on the following template and instructions.

// ------------------------------------
// The Node class is given to you.
// Do not modify it, except that you
// can create a "copy" function
// to facilitate implementation.
// (See more explanations in the Add
// function of the HashTable class.)
// ------------------------------------
class Node {
private:
    int key;
    int idx_next;
//    // Personal helper function to copy node data into a table.
//    void copy(Node &from, Node &to);
public:
    void Set_key(int x);
    int Get_key();
    void Set_index(int x);
    int Get_index();
    Node();
};
Node::Node() {
    key = -1;
    idx_next = -1;
}
void Node::Set_key(int x) {
    key = x;
}
int Node::Get_key() {
    return key;
}
void Node::Set_index(int x) {
    idx_next = x;
}
int Node::Get_index() {
    return idx_next;
}

// -----------------------------------------------
// ----------------- Your Task -----------------
// -----------------------------------------------
// We will implement a hash table which addresses
// collisions using coalesced chaining.
//
// We will construct the table as an array of
// Node objects. Objects colliding at a cell
// are placed on a chain, connected one after
// another through the "idx_next" variable.
// (See how it is used in the above instructions.)
//
// In this hw, let us always add a new collided
// object to the tail of a chain. For example, if
// table[5] is the current tail and the new object
// (which collide at the same cell as table[5])
// is to be stored at table [7], then table[5]'s
// "idx_next" should equal to 7.
//
// When the table is full, you should resize it
// (by doubling its size) and rehash objects
// from the existing table to the new table.
// You need to rehash objects based on the order
// of their indices in the table i.e., first
// rehash table[0], then table[1], then table[2]...
//
// This template does not specify how you should
// resize the table. There are many options e.g.,
// design a resize function and call it, or
// embed a resize-rehash process inside the Add()
// function. Make your own choice, but do not
// alert the input/output of defined functions.
//
// Finally, we will use a special "Empty" Object
// with SID = -1 to indicate a cell is empty.
// For example, if table[2].Get_key() returns -1,
// it means table[2] is empty.
//
// The HashTable class is structured as follows.
// Do not modify the structure but you can add
// functions in two places:
// (1) a "copy" function for the Node class.
// (2) some function(s) for resizing and rehashing
//
// Please complete the class implementation.
// -----------------------------------------------

class HashTable {
private:
// This is size of the hash table.
    int size;

// This is the divisor for the remove function.
    int divisor1;

// This is the hash function "h". It takes "key" as input and returns a hash code h(key) = key % divisor.
    int hash(int key);

    // Personal resize function to resize the table if full.
    void Resize();

// This is a pointer to the hash table. Note it is a pointer of objects.
    Node* table;
public:
// This function creates a hash table
// (through dynamic memory allocation)
// and initializes all cells to NULL.
//
// It should create a table of the
// smallest necessary size N, which
// depends on the input divisor
// (of the modulo hash function).
//
// This function should also update
// the private variable "size" to N.
    void CreateTable(int divisor);
// This function searchs for a student
// whose SID = key. If a student is found,
// return index of the student in the table.
// Otherwise, return -1.
    int Search(int key);
// This function adds a student to the hash
// table. Note the input is an object instead
// of a pointer. We cannot directly assign
// an object to another, but have to assign
// the member variables one by one.
// (You can create a "copy" function for the
// Node class to facilitate object assignment,
// but the essential process should be the same.)
//
// In addition, the add function should apply
// linear probing to look for an empty cell
// for a collided object with key = t. Probing
// should start from table[h(t)].(Not the
// tail of the chain.)
    void Add(Node temp);
// This function removes a student whose
// SID = key from the table. If the student
// is not in the table, it does nothing.
    void Remove(int key);

// This function returns table size.
// Specifically, it returns value of
// the private variable "size".
    int Get_Size();

// This is the constructor. It is defined
// for you. No need to modify it.
    HashTable();
// This is the 1st print function.
// It will print all SID's in the table
// from table[0] to table[N-1].
// It is defined for you and will be
// used to examine the correctness of
// your created/updated hash table.
// Do not modify it.
    void PrintTable();
// This is the 2nd print function.
// It will print all SID's on the chain
// starting at table[h(key)].
// It is defined for you and will be
// used to examine the correctness of
// your created/updated chains.
// Do not modify it.
    void PrintChain(int key);
};

/**
 * Hash the key passed in to determine the objects place in the table.
 * h(key) = key % divisor
 * @param key key passed in to be hashed.
 * @return returns the hashed key.
 */
int HashTable::hash(int key) {
    // Typical hash function since we don't know every specific element to stop collisions
    return key % this->divisor1;
}

/**
 * Create a hash-table that through dynamic memory allocation and initializes all cells to NULL (-1).
 * Create a table of the smallest necessary size N, which depends on input divisor.
 * Update the size to N.
 * @param divisor
 */
void HashTable::CreateTable(int divisor) {

    // New size given the divisor.
    this->size = divisor;

    // Set the correct divisor.
    this->divisor1 = divisor;

    // Create the dynamic memory to be allocated. All cells should be initialized to -1.
    this->table = new Node[this->divisor1];

}

/**
 * When the table is full, resize it by doubling its size.
 * Rehash objects from the existing table to the new table.
 * The objects must be rehashed based on the order of their indices in the table.
 * First rehash table[0], table[1], ... table[n-1], for the size n.
 */
void HashTable::Resize() {

    // Update the existing size of the table by doubling it.
    int newSize = this->size * 2;

    // Create the new memory allocation.
    Node* newTable = new Node[newSize];

    // Rehash all the values till the point.
    for (int i = 0; i < this->size; ++i) {
        newTable[i] = table[i];
    }

    // Delete the previous table memory and update it and the size.
    delete[] table;
    this->table = newTable;
    this->size = newSize;

}

/**
 * Searches for a student whose SID = key, and if found, return the index of the student in the table.
 * @param key SID value of the student to be searched for.
 * @return returns the index of the student in the table, if found. Otherwise, returns -1.
 */
int HashTable::Search(int key) {
    // Loop over the table, searching every index. If the key is ever found, break out and return it.
    int i;
    for (i = 0; i < this->size; ++i) {
        if (table[i].Get_key() == key) {
            break;
        }
    }

    // If i is found within the loop / table limits, return the index.
    if (i != this->size) return i;

    // If the statement above fails.
    return -1;

}

/**
 * Function adds a student to the hash table, and note that the input it an object instead of a pointer.
 * We cannot directly assign an object to another, but we have to assign the member variables one by one.
 * We can create a "copy" function for the Node class to facilitate object assignment.
 * The add function should apply linear probing to look for an empty cell for a collided object with key = t.
 * Probing should start from table[h(t)], not from the tail.
 * @param temp The node value to be inserted in to the table.
 */
void HashTable::Add(Node temp) {

    // 0): Check if full and needs to be resized.
    bool resize = true;
    for (int i = 0; i < this->size; ++ i) {
        if (table[i].Get_key() == -1) resize = false;
    }

    // If true, resize. Otherwise, use the normal.
    if (resize) Resize();

    // 1): Hash the node passed in.
    int hashedKey = hash(temp.Get_key());

    // 2) Base Case: No collisions, simply add the node to the table.
    if (table[hashedKey].Get_key() == -1) {

        // Copy over the values.
        table[hashedKey].Set_key(temp.Get_key());
        table[hashedKey].Set_index(-1);

    }

    // 3): Collision Occurs: using linear probing, find an empty cell starting from table[h(t)]. When found, create the link from the original index and attach the object to the empty index.
    else {
        int index = 1;
        bool found = true;
        while (found) {

            // Get the new hash. We do the size mod to keep it within the range of the table. HashTable[(h(key) + 1) % size]
            int newHash = (hashedKey + index) % this->size;

            // Check the index of the table. If empty, link the indices from the current table[h(t)] and update the index to contain the new node by copying over values.
            if(table[newHash].Get_key() == -1) {

                // First, find the last index of the "next" node of the original hashed key.
                int value = hashedKey;
                while (table[value].Get_index() != -1) {
                    value = table[value].Get_index();
                }


                // Access the original h(t) collided object and set the next index to the current index.
                table[value].Set_index(newHash);

                // Set the key of the current index in the table.
                table[newHash].Set_key(temp.Get_key());

                // Copy over the next index.
                table[newHash].Set_index(-1);

                // Update the loop tracker.
                found = false;
            }

            // Increment the index for the next run, if needed.
            index++;
        }

    }

}

/**
 * This function removes a student whose SID = key from the table.
 * If the student is not in the table, it does nothing.
 * @param key SID value to search for.
 */
void HashTable::Remove(int key) {

    // Loop through, and if found, reset the key and the chain to empty.
    for (int i = 0; i < this->size; i++) {
        // If found in the table, reset the key to -1.
        if (this->table[i].Get_key() == key) {
            this->table[i].Set_key(-1);
        }

        // Also, if found on a chain, remove it from the chain.
        if (this->table[this->table[i].Get_index()].Get_key() == key) {
            this->table[i].Set_index(-1);
        }
    }
}

/**
 * Returns the table size.
 * @return returns the table size.
 */
int HashTable::Get_Size() {
    return this->size;
}

/**
 * Predefined constructor, initializing the table to NULL and the size to 0.
 */
HashTable::HashTable() {
    table = NULL;
    divisor1 = 0;
    size = 0;
}

/**
 * Predefined print function to print all the SID's in the table from table[0] to table[N-1].
 */
void HashTable::PrintTable() {
    for (int i = 0; i < this->size; i++) {
        cout << table[i].Get_key() << '\n';
    }
}

/**
 * Predefined 2nd print function. It will print all SID's on the chain starting at table[h(key)].
 * @param key key passed in to print content.
 *
 */
void HashTable::PrintChain(int key) {
    int temp = hash(key);
    while (temp != -1) {
        cout << this->table[temp].Get_key() << '\n';
        temp = this->table[temp].Get_index();
    }
}

// --------------
// Main Function
// --------------
int main()
{
    int mode, temp;
// This key is used as a search key to
// test the search and remove functions.
    int key;
// This key is used by the 2nd print function.
    int key_chain;
// This divisor is used by the hash function.
// It is also used by the CreateTable() function
// to automatically determine the table size.
    int divisor;
// We don't need dynamically memory allocation
// for taking input students. Do you know why?
    Node Student;
    HashTable x;
    cin >> mode >> key >> key_chain >> divisor;
    x.CreateTable(divisor);
    while (cin >> temp) {
        Student.Set_key(temp);
        x.Add(Student);
    }
// Mode 0: test the "Add" function and
// the resizing and rehashing processes.
// Keep in mind we will test two scenarios:
// (i) table is not full after the above adding
// (ii) table becomes full during adding (need resizing)
    if (mode == 0) {
        x.PrintTable();
    }
// Mode 1: test if your chains are correct
    else if (mode == 1) {
        x.PrintChain(key_chain);
    }
// Mode 2: test the "Search" function
    else if (mode == 2) {
        cout << x.Search(key);
    }
// Mode 3: test the "Remove" function
// We will test both the updated table
// and the updated chain.
    else if (mode == 3) {
        x.Remove(key);
        x.PrintTable();
        x.PrintChain(key);
    }
    return 0;
}

