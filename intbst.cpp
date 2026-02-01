// intbst.cpp
// Implements class IntBST
// Daisy Ayala, (1/30/26)

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(n == nullptr){
        return;
    }

    clear(n->left); //child nodes go down first 
    clear(n->right);
    
    delete n;

}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(root ==nullptr){
        root = new Node(value);
        return true;
    }

    if(value == root->info){
        return false;
    }

    if(root->info > value){
        return insert(value, root->left);
    }
    else if(root->info < value){
        return insert(value, root->right);
    }

    return insert(value, root); //true or false, insertion
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value == n->info){
        return false;
    }


    if(value < n->info){
        if(n->left == nullptr){
            n->left = new Node(value);
            return true;
        }
        
        insert(value, n->left);
    }

    if(value > n->info){
        if(n->right == nullptr){
            n->right = new Node(value);
            return true;
        }
        
        insert(value, n->right);
    }


    return false; 
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(n == nullptr){
        return;
    }
    cout << n->info;

    printPreOrder(n->left);
    printPreOrder(n->right);
   
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(n == nullptr){
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(n == nullptr){
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n == nullptr){
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right); 
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n == nullptr){
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(n == nullptr){
        return nullptr;
    }

    if(value == n->info){
        return n;
    }



    return (n->info > value) ? getNodeFor(value, n->left) : getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node* curr = getNodeFor(value, root);

    if(curr == nullptr){
        return false;
    }

    if(curr->info == value){
        return true;
    }

    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    if(root == nullptr){
        return nullptr;
    }

    Node* curr = getNodeFor(value, root); //if value is not found 
    if(curr == nullptr){
        return nullptr;
    }

    if(curr->left != nullptr){ //if it is check left
        Node* bst = curr->left; //start left

        while(bst->right != nullptr){ //go as right as u can 
            bst = bst->right;
        }
        return bst;
    }
    else{//if left is not available 
        Node* save = root;
        Node* p = nullptr;
        while(save != nullptr){
            if(curr->info > save->info){
                p = save;
                save = save->right;
            }
            else{
                save = save->left;

            }


        }
        return p;
    }
    }


// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
   Node* curr = getPredecessorNode(value);

   if(curr == nullptr){
    return 0;
   }

    return curr->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
     if(root == nullptr){
        return nullptr;
    }

    Node* curr = getNodeFor(value, root); //if value is not found 
    if(curr == nullptr){
        return nullptr;
    }

    if(curr->right != nullptr){ //if it is check right
        Node* bst = curr->right; //start right

        while(bst->left != nullptr){ //go as right as u can 
            bst = bst->left;
        }
        return bst;
    }

    else{//if right is not available 
        Node* save = root;
        Node* p = nullptr;
        while(save != nullptr){
            if(curr->info < save->info){
                p = save;
                save = save->left;
            }
            else{
                save = save->right;

            }


        }
        return p;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
      Node* curr = getSuccessorNode(value);

   if(curr == nullptr){
    return 0;
   }

    return curr->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* curr = getNodeFor(value, root);

    if (curr == nullptr)
    {
        return false; //if no node matches target value, return false
    }

    if(root->info == value ) //if the root has the target value, make sure to connect everything 
    { //first and then delete root, so nothing gets lost. 
        Node* n = root;
        Node* save = nullptr;
        
        if(n->left == nullptr && n->right == nullptr){ //left child case
            delete n;
            n = nullptr;
            return true;


        }

        if(n->left != nullptr && n->right ==nullptr){
            save = root;
            root = root->left;
            delete save;

            return true;
        }
        if(n->right != nullptr && n->left == nullptr){
            save = root;
            root = root->right;
            delete save;

            return true;
        }

        Node* p = getPredecessorNode(n->info);
        n->info = p->info;
        remove(p->info);
        return true;
    }

    else if((curr->left != nullptr && curr->right == nullptr) || (curr->left == nullptr && curr->right != nullptr) ){
        //check if a parent , if so do below 
        //make one of the childs the new parent
        //connect it to the parent above it
        Node* n = root;
        Node* Parent = nullptr;

        while(n != curr){
            Parent = n;
            if(curr->info < n->info){
                n = n->left; //saving node before the value node
            }
            else{
                n= n->right;
            }
        }
        
        Node* c = nullptr;
        if(curr->left != nullptr){ //curr parent
            c = curr->left;
        }
        else{
            c = curr->right;
        }

        if(Parent == nullptr){ //parent to child 
            root = c;
        }
        else if(Parent->left ==curr){
            Parent->left = c;
        }
        else{
            Parent->right = c;
        }

        delete curr;

        return true;
    }

    else if(curr->left != nullptr && curr->right != nullptr){
        //this is if curr is a parent node and has two children.
       Node* p = curr->left;
       Node* previous = curr;
       while(p->right != nullptr){
            previous = p;
            p = p->right;
       }

       curr->info = p->info;

       if(previous->left == p){
            previous->left = p->left;
       }
       else{
            previous->right = p->left;
       }
       delete p;

       return true;
    }

    return false; 
}
