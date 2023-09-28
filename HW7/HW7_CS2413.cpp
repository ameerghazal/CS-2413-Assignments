#include <iostream>
using namespace std;

// ========================================
// HW7: Implement Hash Table with the
// Separate Chaining Technique
// ========================================

// In this assignment, we will implement a
// hash table which uses separate chaining
// to deal with collisions. The chains should
// be implemented using singly linked list.

// The Node class (used to construct linked list)
// has been defined to you. Do not modify it.

// Your task is to develop a HashTable class
// based on the following template.
// You should complete six member functions.

// ------------------------------------
// The Node class is given to you.
// Do not modify it.
// Just use it to construct lists.
// ------------------------------------
class Node {
private:
int key;
Node* p_next;
// there could be other satellite data
// here we omit them for simplicity
public:
void Set_key(int x);
int Get_key();
void Set_p(Node* p);
Node* Get_p();
Node();
};
Node::Node() {
key = -1;
p_next = NULL;
}
void Node::Set_key(int x) {
key = x;
}
int Node::Get_key() {
return key;
}
void Node::Set_p(Node* p) {
p_next = p;
}
Node* Node::Get_p() {
return p_next;
}

// -----------------------------------------------
// We will implement a hash table whose elements
// are pointers. Each pointer points to a linked
// list that holds the (collided) students.
//
// The HashTable class is structured as follows.
// Do not modify the structure.
// Your task is to complete the member functions.
// -----------------------------------------------

class HashTable {
private:
// This is the size of the hash table.
    int size;
// This is the hash function "h". It takes "key" as input and returns
// a hash code h(key) = key % divisor.
    int hash(int key);
// This is a pointer to the hash table. Note it is a pointer of pointer.
    Node** table;
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
// return address of the student node.
// Otherwise, return NULL.
    Node* Search(int key);
// This function adds a student (address
// stored at "temp") to the hash table.
    void Add(Node* temp);
// This function removes a student whose
// SID = key from the table. If the student
// is not in the table, it does nothing.
    void Remove(int key);


// This function returns the table size.
// Specifically, it returns value of the
// private variable "size". (DONE)
    int Get_Size();


// This is the constructor. It is given
// to you. No need to modify it. (DONE)
    HashTable();

// This is the print function. It is given
// to you and used to examine the correctness
// your created/updated hash table.
// Do not modify it. (DONE)
    void PrintTable();
};




/**
 * Creates a hash table through dynamic memory allocation and initializes all cells to NULL.
 * Create a table of the smallest necessary size N, which depends on the input divisor of the modulo hash function.
 * The function should also update the private variable "size" to N.
 * @param divisor
 */
void HashTable::CreateTable(int divisor) {

    // Remove existing table for better space efficency, if defined.
    if (table != nullptr) {
        
    }

    // New size given the divisor.
    this->size = divisor;

    // Create the dynamic memory to be allocated
    this->table = new Node*[this->size];

    // Initalize all cells to null "lists".
    for (int i = 0; i < this->size; ++i) {
        table[i] = nullptr;
    }



}



/**
 * Searches for a student whose SID = key.
 * If a student is found, the function will return the address of the student node. Otherwise, NULL will be returned.
 * @param key SID value to check.
 * @return address of the node matching the sid value passed in.
 */
Node* HashTable::Search(int key) {

    // Pointer to search.
    Node* search = NULL;

    // Loop over the table indices.
    for (int i = 0; i < this->size; ++i) {

        // Reassign the search pointer of the table index.
        search = this->table[i];

        // Search the list at the index; if no list, simply search the node. If nothing, keep going.
        while (search != NULL) {

            // If the value is found, we break out of the loop.
            if (search->Get_key() == key) return search;

            // Reassign for the next iteration of the linked list.
            search = search->Get_p();
        }

        // If not found in at the certain table index & searching the collisons, move to the next table index.
    }

    // Return the search address, which will either match will the key - if found - or return NULL.
    return search;

}


/**
 * Adds a student (address stored in the pointer) to the hash table by hashing the value and passing it into the table.
 * @param temp Address of the student node.
 */
void HashTable::Add(Node *temp) {

    // Start by hashing the SID value in the node.
    int hashedKey = hash(temp->Get_key());

    // Update the key of the pointer
//    temp->Set_key(hashedKey);

    // Store the temp pointer.
    Node* temp2 = this->table[hashedKey];

    // If the index is not null, meaning a collision has occurred, attach the new node to the tail of the list.
    if (this->table[hashedKey] != NULL) {

        // Add the node to the 'head' of the 'linked list'.
        temp->Set_p(temp2);
    }

    // Otherwise, set the index of the table to the new pointer.
    // Reassign the "head" of the linked list.
    this->table[hashedKey] = temp;

    // Free up the temp2
    delete temp2;

}

/**
 * Removes a student whose SID = key from the table.
 * If the student is not in the table, nothing happens.
 * @param key SID key of the node to remove.
 */
void HashTable::Remove(int key) {

    // Temp pointer to access the table.
    Node* prev = NULL;

    // Search each table index, and from there, search the linked list, if necessary.
    for (int i = 0; i < this->size; ++i) {

        // Assign the loop pointer to the table index, which points to the linked list to search.
        prev = this->table[i];
        int position = 0;

        // Loop over the linked list.
        while (prev != NULL) {

            // Case 1: Remove from the head
            if (prev->Get_key() == key && position == 0) {
                // Reassign the head to the next link - if possible.
                this->table[i] = prev->Get_p();

                // Free up the space at the point in memory.
                delete prev;

                // Break out
                break;
            } else if (prev->Get_p() != NULL && prev->Get_p()->Get_key() == key) {

                // Case 2: Removal at a random index.

                // Temp to hold the current place.
                Node* placement = prev->Get_p();

                // Set the next pointer to the node after the one to be deleted.
                prev->Set_p(prev->Get_p()->Get_p());

                // Remove the node.
                placement->Set_p(NULL);
                delete placement;

            } else if (prev->Get_p() != NULL && prev->Get_p()->Get_p() == NULL && prev->Get_p()->Get_key() == key) {
                // Case 3: Removal from the tail
                // 2->4->5, in this case we are we pointing to "4" in the linked list. Check to make sure the next element
                // is not null (5) and the element after is null. If so - and the key is the same - remove from the tail.

                // Free up space at the tail
                delete prev->Get_p();

                // Reassign the next pointer to null
                prev->Set_p(NULL);

            }

            // Otherwise, reset for the next run.
            prev = prev->Get_p();
            position++;
        }

    }

}

/**
 * Hash the key passed in to avoid collisions in the table.
 * Function of the form h(key) = key % divisor.
 * @param key key value passed in to create a hash code.
 * @return returns the hashed code.
 */
int HashTable::hash(int key) {
    // We know the divisor to be the size of the table,
    // so hash based on the size (need to review this to make sure).
    return key % this->size;
}

/**
 * Returns the table size.
 * @return size of the table.
 */
int HashTable::Get_Size() {
    return this->size;
}

/**
 * Pre-defined constructor given to us to use. Sets the table to null and size to 0 off creation.
 */
HashTable::HashTable() {
table = NULL;
size = 0;
}

/**
 * This is the print function. It is defined for you. Do not modify it.
 * Basically, this function will screen the table line by line, and print all SIDS in the linked list from head to tail.
 * This function will be used to test if your constructed/updated table is correct or not.
 */
void HashTable::PrintTable() {

    // Null pointer to loop over.
    Node* temp = NULL;
    for (int i = 0; i < size; i++) {

        // Access the linked list at the table index.
        temp = table[i];

        // Loop over all the values inisde of the linked list.
        while (temp != NULL) {
            cout << temp->Get_key() << '\n';
            temp = temp->Get_p();
        }
    }
}



// --------------
// Main Function
// --------------
int main() {

    // Mode chosen and number of nodes added until done.
    int mode, temp;

    // Search key used to test and remove functions.
    int key;

    // This divisor is used by the hash function.
    // It is also used by the CreateTable() function to automatically determine the table size.
    int divisor;

    // Node pointer used to create nodes for the lists, and a new hashtable to add elements into.
    Node* Student;
    HashTable x;

    // Read in data from the user.
    cin >> mode >> key >> divisor;

    // Create the table, passing in the divisor for the hash function.
    x.CreateTable(divisor);

    // Read in the number of values.
    while (cin >> temp) {
        Student = new Node;
        Student->Set_key(temp);
        x.Add(Student);
    }


    // Mode 0: test if your table size is correct
    if (mode == 0) {
        cout << x.Get_Size();
    }
        // Mode 1: test the "Add" function
    else if (mode == 1) {
        x.PrintTable();
    }
        // Mode 2: test the "Search" function
    else if (mode == 2) {
        Student = x.Search(key);
        if (Student == NULL) {
            cout << -1;
        }
        else {
            cout << Student->Get_key();
        }
    }
        // Mode 3: test the "Remove" function
    else if (mode == 3) {
        x.Remove(key);
        x.PrintTable();
    }
    return 0;
}