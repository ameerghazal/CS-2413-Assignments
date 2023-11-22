
#include <iostream>
using namespace std;

// ========================================
// HW13: Implement a Binary Search Tree
// which can be converted to AVL Tree
// ========================================
//
// In this assignment, we will implement
// an AVL tree which can also do standard
// Binary Search Tree adding and removal.
//
// The Node class and AVL class are both
// partly defined for you.
//
// ***************************************
// You can add new variables and functions
// in both classes. However, you should
// implement the following given functions
// because they will be called in the main
// function to test part of your implementation.
//
// (Check "main" function for more details.)
// 1. PreTraverse()
// 2. GetRoot()
// 3. Add()
// 4. Remove()
// 5. Add_AVL()
// 6. Remove_AVL()
// 7. Height()
//
// Other given functions are only recommended.
// ***************************************


class Node {
private:
    int key;
    Node* p_left;
    Node* p_right;
    Node* p_parent;
public:
    void Set_key(int x);
    int Get_key();
    void Set_left(Node *p);
    void Set_right(Node* p);
    void Set_parent(Node* p);
    Node* Get_left();
    Node* Get_right();
    Node* Get_parent();
    Node();
};

// All the methods were used created, but all compute a similar return.
void Node::Set_key(int x) {
    this->key = x;
}
int Node::Get_key() {
    return this->key;
}
void Node::Set_left(Node *p) {
    this->p_left = p;
}
void Node::Set_right(Node *p) {
    this->p_right = p;
}
void Node::Set_parent(Node *p) {
    this->p_parent = p;
}
Node* Node::Get_left() {
    return this->p_left;
}
Node* Node::Get_right() {
    return this->p_right;
}
Node* Node::Get_parent() {
    return this->p_parent;
}
Node::Node() {
    key = 0;
    p_left = NULL;
    p_right = NULL;
    p_parent = NULL;
}



class AVL {
private:
    // This is root of the AVL
    Node* root;
    // Personal private function to make the pre-order traverse easier without modifying the signature.
public:
    // This function implements pre-order
    // traverse, starting from the root,
    // and prints the traverse sequence
    // (with no space between nodes).
    // You can use the function you implemented
    // in HW10 (by slightly modifying it).
    // This function is only used to test
    // if your updated AVL/BST is correct.
    void PreTraverse();
    void PreTraverseHelper(Node* root);
    // This function returns the root node.
    // Normally we don't need it. Here we
    // just it to evaluate your Height function.
    // See main function test case 5 for details.
    Node* GetRoot();
    // This function performs search
    // on the current AVL with "key".
    // It returns address of a matching
    // node, or returns NULL if no
    // matching node is found.
    Node* Search(int key);

    // Personal function
    Node* SearchInsert(int key);
    // This function adds a new node at
    // "p" to AVL without considering
    // any violation of AVL property.
    // (So just standard BST adding.)
    // It can return a proper address.
    Node* Add(Node* p);
    // This function removes a node with
    // "key" from AVL without considering
    // any violation of AVL property.
    // (So just standard BST removal.)
    // For simplicty, to fill holes, let
    // us only use the recursive algorithm
    // that looks for the max/min node in
    // the left/right subtress of the hole.
    // It can return a proper address.
    Node* Remove(int key);
    // This function adds a new node
    // stored at "p" to AVL and performs
    // necessary rotations to restore
    // the AVL property.
    void Add_AVL(Node* p);
    // This function removes a node
    // with "key" from AVL and performs
    // necessary rotations to restore
    // the AVL property.
    void Remove_AVL(int key);
    // This function returns height
    // of a subtree rooted at "p".
    int Height(Node* p);
    // This function performs clock-wise
    // rotation at node "p". It only does
    // rotation and does not consider
    // the type of violation scenario.
    // It can return a proper address.
    Node* Rotate_cw(Node* p);
    // This function performs counter
    // clock-wise rotation at node "p".
    // It only does rotation and does
    // not consider the type of violation
    // scenario. It can return a proper address.
    Node* Rotate_cc(Node* p);
    // This function checks if there
    // is a violation at a node p, and
    // return the violation scenario.
    // It returns a string of
    // - "NO" if no violation
    // - "LL" if it is left-left violation
    // - "RR" if it is right-right violation
    // - "LR" if it is left-right violation
    // - "RL" if it is right-left violation
    string CheckViolation(Node* p);
    // This function intiailizes root = NULL.
    AVL();
};


/**
 * Personal created helper function (private).
 * Created to speed up the pre-traversal function without modifying the original signature.
 * @param root node to begin the traversal from.
 */
void AVL::PreTraverseHelper(Node* root) {

    // 0): Check if null.
    if (root == nullptr) return;

    // 1): Visit the root note.
    cout << root->Get_key();

    // 2): Visit the left subtree, recursively, by passing in the left node.
    PreTraverseHelper(root->Get_left());

    // 3): Visit the right subtree, once the left has been searched, by passing in the right node.
    PreTraverseHelper(root->Get_right());
}

/**
 * Implements pre-order traverse, starting from the root and prints the traverse sequence.
 * Use the function from HW10, in which it will test if the updated AVL/BST is correct.
 */
void AVL::PreTraverse() {
    // Call the helper function to do all the work.
    PreTraverseHelper(this->root);
}

/**
 * Returns the root node.
 * @return the root node.
 */
Node* AVL::GetRoot() {
    return this->root;
}

/**
 * Base search function. If found returns address; otherwise, null.
 * @param key the key to search for.
 * @return Address if found, else null.
 */
Node* AVL::Search(int key) {

    // 1): Save the root and test.
    Node* temp = this->root;

    // Will return null.
    if (temp == nullptr) return temp;

    // Returns the found node.
    if (key == temp->Get_key()) return temp;

    // Loop over and check.
    while (temp != nullptr) {

        // If found, return it.
        if (temp->Get_key() == key) return temp;

        // Go right if the add key is greater than the current key.
        if (temp->Get_key() < key)
            temp = temp->Get_right();
        else // Otherwise, go left.
            temp = temp->Get_left();

    }

    // Will return null since the loop will be done.
        return temp;
}

/**
 * Performs search on the current AVL with "key", and returns the address of the node if found.
 * @param key search key for the traverse.
 * @return returns the address of the matching node, if found; otherwise, NULL.
 */
Node* AVL::SearchInsert(int key) {

    // 1): Comparison to the root node with a temp node assigned.
    Node* temp = this->root;

    // 2): Loop with comparison to the root node.
    while (temp != nullptr) {

        // Store the key for the run.
        int nodeKey = temp->Get_key();

        // a): Found, break out and return the temp.
        if (nodeKey == key)
            return temp;

            // b): Search the left subtree.
        else if (key < nodeKey) {
            if (temp->Get_left() == nullptr) return temp;
            else temp = temp->Get_left();
        }

            // c): Search the right subtree.
        else if (key > nodeKey) {
            if (temp->Get_right() == nullptr) return temp;
            else temp = temp->Get_right();
        }
    }

    // 3): Return the temp node; it will either the found node, or a failed search with the last possible link (parent) to add a node.
    return temp;


}

/**
 * Returns the height of a subtree rooted at "p".
 * Similar method taken from the HW10 assignment.
 * @param p Node to check.
 * @return the height of the subtree rooted at p.
 */
int AVL::Height(Node *p) {

    // Logic: Search both sublists for the max height; compare the left sublist height with the right sublist height. Return the greater one.

    // Base Case: if the node is null, it signifies the end of the sublist.
    if (p == nullptr) { return -1; }

    // Recursive Case: Start by searching the left list fully, below will be the return case.
    int leftHeight = Height(p->Get_left());
    int rightHeight = Height(p->Get_right());

    // Increment step. For example, the run will go all the way to the of the left list and right list.
    // From there, we boil back up. So we take the current height and increment by 1, based on which is bigger.
    // This will boil up to the top, where the largest one will eveuntually be returned.
    if (leftHeight > rightHeight)
        return (leftHeight + 1);
    else
        return (rightHeight + 1);
}

/**
 * Adds a new node at "p" to AVL without considering any violation of the AVL tree properties.
 * Standard BST adding that returns the proper address.
 * @param p node to add in.
 * @return returns a proper address.
 */
Node* AVL::Add(Node *p) {

    // 1): Search the BST using the search function, which will return 1 of two things: either an address to the last parent possible or the address of a node already contained.
    int key = p->Get_key();
    Node* temp = SearchInsert(key);

    // 1.5): Check if the node is already contained within the AVL; if so, return the address.
    if (temp != nullptr) {
        int otherKey = temp->Get_key();
        if (otherKey == key) return p;
        else if (key < otherKey) temp->Set_left(p);
        else if (key > otherKey) temp->Set_right(p);
    } else {
        // Otherwise, this is the new root.
        this->root = p;
        return root;
    }

    // 2): Otherwise, now, connect the links and add the node.
    p->Set_parent(temp);
    return p;
}

/**
 * Removes a node with the key passed in.
 * Does not consider any violation of AVL property.
 * To fill holes, we use the recursive algorithm that looks for the max node in the left sublist OR the min node in the right sublist of the hole.
 * Returns a proper address.
 * @param key value of the Node to remove.
 * @return returns the new node root.
 */
Node* AVL::Remove(int key) {

    // 1): Find the target node by the search function, check, and remove it plausible.
    Node *temp = Search(key);

    // Check to see if the node can be removed or if the previous node was returned.
    if (temp == nullptr) return nullptr;
    Node *parent = temp->Get_parent();

    // 2): Find the max node in the left subtree to fill (or the min-node in the right subtree).

    // Compare the heights of the left and right subtree's to determine which node to use (max in left or min in right).
    int lHeight = Height(temp->Get_left());
    int rHeight = Height(temp->Get_right());
    Node *side = nullptr;

    // Case 1: Node has no children.
    if (lHeight == -1 && rHeight == -1) {
        // Parent is defined.
        if (parent != nullptr) {
            // The left / right is to be removed.
            if (temp == parent->Get_left()) parent->Set_left(nullptr);
            else if (temp == parent->Get_right()) parent->Set_right(nullptr);
        } else {
            // Parent is a hole.
            this->root = nullptr;
        }
    }

    // Case 2: Node has 2 children.
    else if (lHeight != -1 && rHeight != -1) {
        // Find the min node in the right subtree to fill the hole.
        side = temp->Get_right();

        if (side != nullptr) {
            // Loop until min's left is null.
            while (side->Get_left() != nullptr) {
                side = side->Get_left();
            }
        }

        // Reset the key.
        temp->Set_key(side->Get_key());

    }

        // Case 3: Node has 1 child.
    else {
        // Define a pointer for the child.
        Node *kid;

        // Find out which node is the child.
        if (temp->Get_left() != nullptr) kid = temp->Get_left();
        else kid = temp->Get_right();

        // Guard clause to ensure the parent is still defined
        if (parent != nullptr) {
            // Ternary Javascript for fun. This is the same as if else.
            temp == parent->Get_left() ? parent->Set_left(kid) : parent->Set_right(kid);
        } else {
            // Otherwise, the new root is now the kid.
            this->root = kid;
        }

        // Set the new kid's parent link. If it is the root, it will just be null, indicating head root.
        kid->Set_parent(parent);
    } // exit if-elseif-else

    // 4): Clear up space and return the new head.
    delete side;
    return temp;
}


/**
 * Adds a new node stored at "p" and performs necessary rotations to restore the AVL property.
 * @param p the new node to be added to the AVL tree.
 */
void AVL::Add_AVL(Node *p) {

    // 1): Begin by adding the node w/o any violations by using the Add function and store the .
    Node *parent = Add(p);

    // 2): Check for violations.
    //string viol = CheckViolation(parent);
    //cout << viol;

    // 3): Loop and fix the violations until there are none remaning.
    while (parent != nullptr) {

        string viol = CheckViolation(parent);

        if (viol == "LL") {
            parent=Rotate_cw(parent);
        } else if (viol == "RR") {
            parent=Rotate_cc(parent);
        } else if (viol == "LR") {
            // Counter-clockwise rotate the left child.
            Rotate_cc(parent->Get_left());

            // Clockwise rotate the parent.
            parent=Rotate_cw(parent);
        } else if (viol == "RL") {
            // Clock-wise rotate the right child.
            Rotate_cw(parent->Get_right());

            // Counter-clockwise rotate the parent.
            parent=Rotate_cc(parent);
        }

        // Re-initialize the parent and the violation for the next run-if possible.
        parent = parent->Get_parent();
    }
}

/**
 * Removes a node with "keY" from AVL and performs necessary rotations to restore the AVL property.
 * @param key key of the node to be removed.
 */
void AVL::Remove_AVL(int key) {

    // 1): Remove the node w/o avl tree worries.
    Node* parent = Remove(key);

    // 2): Check violations starting from the newHead node's parent returned after the remove function.

    // Note, we check the violation among ancestors of the modified node in bottom-up fashion.

    // 3): Loop and fix the violations until there are no violations remaining
    while (parent != nullptr) {
        string viol = CheckViolation(parent);

        if (viol == "LL") {
            parent=(parent);
        }

        else if (viol == "RR") {
            parent=Rotate_cc(parent);
        }

        else if (viol == "LR") {
            // Counter-clockwise rotate the left child.
            Rotate_cc(parent->Get_left());

            // Clockwise rotate the parent.
            parent=Rotate_cw(parent);
        }

        else if (viol == "RL") {
            // Clock-wise rotate the right child.
            Rotate_cw(parent->Get_right());

            // Counter-clockwise rotate the parent.
            parent=Rotate_cc(parent);
        }

        // Re-initialize the parent and the violation for the next run-if possible.
        parent = parent->Get_parent();
    }
}

/**
 * Function that performs clock-wise rotations at the node "p".
 * Only does rotation and does not consider the type of violation scenario.
 * Returns a proper address.
 * @param p the node root to rotate from.
 * @return returns the root of the new rotated node.
 */
Node* AVL::Rotate_cw(Node *p) {

    // 1): Begin by defining some pointers.
    Node *pa = p;
    Node *pb = p->Get_left();
    Node *pr = p->Get_parent();

    // 2): Set some links.

    // Set A's left child (B) to B's right child (D) (if it exists).
    pa->Set_left(pb->Get_right());

    // Guard clause if the left child does not exist.
    if (pb->Get_right() != nullptr) {
        pb->Get_right()->Set_parent(pa);
    }

    // Set B's right child to A.
    pb->Set_right(pa);

    // Set A's parent to B.
    pa->Set_parent(pb);

    // Set B's parent to A's parent (if it exists).
    pb->Set_parent(pr);

    // Set A's parent's child to B.
    if (pr != nullptr) {
        if (pa == pr->Get_left()) pr->Set_left(pb);
        else pr->Set_right(pb);
    }

    if (p == root) {
        root = pb;
    }

    // 3): Return the new head and update p.
    return pb;
}

/**
 * Performs counter clock-wise rotation at the node "p".
 * Does not consider the type of violation scenario.
 * Returns the new root after the rotation.
 * @param p node to rotate at.
 * @return the new root after the rotation.
 */
Node* AVL::Rotate_cc(Node *p) {

    // 1): Begin by defining some pointers.
    Node *pa = p;
    Node *pb = p->Get_right();
    Node *pr = p->Get_parent();

    // 2): Change some links:

    // Set A's right child (B) to B's left child (D) (if it exists).
    pa->Set_right(pb->Get_left());

    if (pb->Get_left() != nullptr) pb->Get_left()->Set_parent(pa);

    // Set B's left child to A.
    pb->Set_left(pa);

    // Set A's parent to B.
    pa->Set_parent(pb);

    // Set B's parent to A's parent (if it exists).
    pb->Set_parent(pr);

    // Guard clause if the right child does not exist.
    if (pr != nullptr) {
        if (pa == pr->Get_left()) pr->Set_left(pb);
        else pr->Set_right(pb);
    }

    // If the given node was the root, update the root to pb (right child).
    if (pa == this->root) this->root = pb;

    // Return the new root of the rotated subtree.
    return pb;

}

/**
 * Checks if there is a violation at a root node of p.
 * Returns the violation scenario.
 * @param p the root node to start at.
 * @return a string of "NO", "LL", "RR", "LR", or "RL".
 */
string AVL::CheckViolation(Node* p) {

    // 1): Compare the heights of the left and right trees and save a temp node.
    Node* temp = p;
    int leftHeight = Height(temp->Get_left());
    int rightHeight = Height(temp->Get_right());

    // 2): Determine the violation.

    // Case 1: Left-Left OR Left-Right Violation.
    if (leftHeight > (rightHeight+1)) {

        // Store the left child.
        Node* lChild = temp->Get_left();

        // Compute the height differences of the child.
        int lChildH = Height(lChild->Get_left());
        int rChildH = Height(lChild->Get_right());

        // Delete the node for saving purposes.
        //delete lChild;

        // Case 1a): Left-Left (the parent [temp] is left heavy and the child [lchild] is left heavy).
        if (lChildH >= rChildH) return "LL";

        // Case 1b): Left-Right (the parent is left heavy and the child is right heavy).
        if (rChildH > lChildH) return "LR";
    }

    // Case 2: Right-Right OR Right-Left Violation.
    else if (rightHeight > (leftHeight+1)) {

        // Store the right child.
        Node* rChild = temp->Get_right();

        // Compute the height differences of the child.
        int lChildH = Height(rChild->Get_left());
        int rChildH = Height(rChild->Get_right());

        // Delete the rChild node for space.
        //delete rChild;

        // Case 2a): Right (the parent [temp] is right heavy and the child [rChild] is right heavy).
        if (rChildH >= lChildH) return "RR";

        // Case 2b): Right-Left (the parent is right heavy and the child is left heavy).
        if (lChildH > rChildH) return "RL";
    }

    // Case 3: No violation. (leftHeight is equal to Right Height or Left Height is less the Right Height by 1).
    return "NO";


    //    if ((leftHeight >= rightHeight && leftHeight <= (rightHeight + 1)) || (rightHeight >= leftHeight && rightHeight <= (leftHeight+1))) {
    //        return "NO";
    //    }

}

/**
 * Constructor that initliazes the root to null.
 */
AVL::AVL() {
    this->root = nullptr;
}



// --------------
// Main Function
// --------------
int main() {
// mode_test: indicate which function to test
// model_avl: if 1, we do adding with AVL property
// if 0, we do adding without AVL property
// (so just standard bst adding)
// key_temp: keys of nodes to add to AVL initially
// key_search:key of node for search/remove
    int mode_test, mode_avl, key_temp, key_search;
    Node* temp;

// This is our AVL tree object.
    AVL tree;
    cin >> mode_test >> mode_avl >> key_search;

    while (cin >> key_temp) {
        temp = new Node;
        temp->Set_key(key_temp);
        if (mode_avl == 0)
        {
            tree.Add(temp);
        }
        else if (mode_avl == 1) {
            tree.Add_AVL(temp);
        }
    }

// Mode 0: test "Add" function.
    if (mode_test == 0) {
        tree.PreTraverse();
    }

// Mode 1: test "Add_AVL" function
    else if (mode_test == 1) {
        tree.PreTraverse();
    }

// Mode 2: test "Search" function
    else if (mode_test == 2) {
        temp = tree.Search(key_search);
        if (temp == NULL) {
            cout << -1;
        }
        else {
            cout << temp->Get_key();
        }
    }

// Mode 3: test "Remove" function
    else if (mode_test == 3) {
        tree.Remove(key_search);
        tree.PreTraverse();
    }

// Mode 4: test "Remove_AVL" function
    else if (mode_test == 4) {
        tree.Remove_AVL(key_search);
        tree.PreTraverse();
    }

// Mode 5: test "Height" function
    else if (mode_test == 5) {
        cout << tree.Height(tree.GetRoot());
    }
    return 0;
}