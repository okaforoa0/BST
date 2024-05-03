//Onyinyechi Okafor 011
#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
	root = nullptr;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
	root = new BSTNode(title, author, yr, pub, isbn, rate);
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {

    Book newBook(title, author, yr, pub, isbn, rate); // create a new book object
    BSTNode* newNode = new BSTNode(); // create a new node with the book
    newNode->book = new Book(title, author, yr, pub, isbn, rate);

    //check if tree is empty, set the new node as the root
    if (root == nullptr) {
        root = newNode;
        setHeight(root); //update height of root node
        return;
    }

    BSTNode* current = root;
    BSTNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (*(newNode->book) < *(current->book)) {// compare new book with book at the current node
            current = current->left; // move to the left child
        } else {
            current = current->right; // move to the right child
        }
    }
    // parent points to the node where new node should be inserted
    // compare the new book with the book at the parent node to see whether to insert as left or right child
    if (parent != nullptr) {
        //compare new book with book at the parent node to figure out insertion direction
        //dereference pointer newNode->book and parent->book to give Book object it is pointing to
        if (*(newNode->book) < *(parent->book)) {
            parent->left = newNode; // less than or equal to, insert as left child
            newNode->parent = parent;//set parent of new node
        } else {
            parent->right = newNode; // greater than or equal to, insert as right child
            newNode->parent = parent;//set the parent of new node
        }
        setHeight(parent); //update height of inserted node's parent
    } else {
        root = newNode; //update root to newNode
        setHeight(root); //update height of root node;
    }
}

BSTNode *BST::find(string title, string author) {
    BSTNode* current = root;
    //traverse through the tree while the node is not null
    while (current != nullptr){
        //compare the wanted book's title and author with current node's book
        if(current->book->title == title && current->book->author == author){ //if input title/author matches exactly
            return current; //found book, return its node

        /*if author is less than current book author or if it equals the current book author
        and title is less than current book title*/
        } else if (author < current->book->author || (author == current->book->author && title < current->book->title)){
            current = current->left; // traverse left subtree because it is less than or  equal to
        } else {
            current = current->right; //otherwise traverse right subtree because it is greater than or equal to
        }
    }
	return nullptr; // book has not been found, return null
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
    /*very similar to previous find function, but this one starts the search from the given 'start' node
     * and can search within a specific subtree of the BST*/

    BSTNode* current = start;
    //traverse through tree while node is not null
    while (current != nullptr){
        //compare the wanted book's title and author with current node's book
        if(current->book->title == title && current->book->author == author){ //matches exactly
            return current; //found book, return its node

            /*if author is less than current book author or if it equals the current book author
            and title is less than current book title*/
        } else if (author < current->book->author || (author == current->book->author && title < current->book->title)){
            current = current->left; // traverse left subtree because it is less than or equal to
        } else {
            current = current->right; //otherwise traverse right subtree because it is greater than or equal to
        }
    }
    return nullptr; // book has not been found, return null
}
void BST::printTreeIO(bool debug) {
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing In-Order:" << endl;
		printTreeIO(root, debug);
	}
}

void BST::printTreeIO(BSTNode *node, bool debug) {
    //if node is not null
	if (node != nullptr) {
        printTreeIO(node->left, debug); //traverse left subtree recursively
        node->printNode(debug); /*change debug flags to false b4 submitting, prints current node,
        calls printNode function from BSTNode class*/
        printTreeIO(node->right, debug); // traverse right subtree recursively
    }
}

void BST::printTreePre(bool debug) {
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root, debug);
	}
}

void BST::printTreePre(BSTNode *node, bool debug) {
	if (node != nullptr){
        node->printNode(debug); //prints current node
        printTreePre(node->left, debug);// recursively traverses left subtree
        printTreePre(node->right, debug); //recursively traverses right subtree
    }
}

void BST::printTreePost(bool debug) {
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root, debug);
	}
}

void BST::printTreePost(BSTNode *node, bool debug) {
    if (node != nullptr) {
        printTreePost(node->left, debug); // recursively traverses left subtree
        printTreePost(node->right, debug); // recursively traverses right subtree
        node->printNode(debug); // prints current node
    }
}

void BST::clearTree() {
	if (root == nullptr) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = nullptr;
	}
}

void BST::clearTree(BSTNode *node) {
	if (node == nullptr) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = nullptr;
		clearTree(node->right);
		node->right = nullptr;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    BSTNode *current = root;

    //traverse tree starting from root
    while (current != nullptr) {
        //check if current node's book matches what the user inputs
        if (current->book->author == author && current->book->title == title) {
            //check if book is not checked out already
            if (!current->book->checked_out) {
                //check out the book and set the flag to true
                current->book->checked_out = true;
                return true; //book has been checked out
            }
        }
        //traverse tree based on comparison
        //compares by author first
        if (author < current->book->author) {
            current = current->left;
        } else if (author > current->book->author) {
            current = current->right;
        } else {//otherwise, authors are same, compared based on titles
            if (title < current->book->title) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return false;//no copy was found
}



bool BST::checkIn(string title, string author) {
        BSTNode *current = root;

        //traverse tree starting from root
        while (current != nullptr) {
            //check if current node's book matches what the user inputs
            if (current->book->author == author && current->book->title == title) {
                //check if book is checked out already
                if (current->book->checked_out) {
                    //check in the book and set the flag to false
                    current->book->checked_out = false;
                    return true; //book has been checked in
                }
            }
            //traverse tree based on comparison
            //compares by author first
            if (author < current->book->author) {
                current = current->left;
            } else if (author > current->book->author) {
                current = current->right;
            } else {//otherwise, authors are same, compared based on titles
                if (title < current->book->title) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
        }
        return false;//no checked_out copy was found
}


void BST::updateRating(string title, string author, float newRating) {
    BSTNode *current = root;
    //traverse tree starting from root

    while (current != nullptr) {//check if current node's book matches exactly
        if (current->book->author == author && current->book->title == title) {
            current->book->rating = newRating; //update rating of book to user's input
        }

        //traverse right or left based on comparison
        if (author < current->book->author) { //author less than current book's author
            current = current->left;
        } else if (author > current->book->author) {//author is greater than current book's author
            current = current->right;
        } else {//if authors are same, compare based on title
            if (title < current->book->title) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }

}
BSTNode *BST::removeNoKids(BSTNode *node) {
    //first, let's check if node to be removed is the root
    if (node == root){
        root = nullptr;
        return node;
    }
    //created to find parent of node that needs to be removed
    BSTNode* parent = node->parent;

    //check if node to be removed is left child of parent node
     //update parent's left pointer to null

    if (parent->left == node) {
        parent->left = nullptr; //no child on left
    } else if (parent->right == node) {
        parent->right = nullptr;
    }

    //now start with parent of removed node
    BSTNode* currentNode = parent;
    while (currentNode != nullptr){
        setHeight(currentNode); //call setHeight to update height of current node
        currentNode = currentNode->parent;
    }
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    BSTNode* child = nullptr;
    //if leftFlag = true, then the child is on the left to be removed
    if (leftFlag) {
        child = node->left;
    } else {
        //otherwise child on right to be removed
        child = node->right;
    }
    //check if parent pointer of current node is not null/ current node has a parent node
    if (node->parent != nullptr){
        //if the parent node has a left child to be removed
        if(node->parent->left == node){
            node->parent->left = child;  //update the parent's left pointer to point to child of removed node
        } else{
            //if parent node has a right child to be removed
            node->parent->right = child; //update parent's right pointer to point to child of removed node
        }
        //check if node to be removed is the root, then update the root to point to child
    } else {
        root = child;
    }
    //if child pointer is not null
    if (child != nullptr) {
        child->parent = node->parent; //  update parent pointer of child to parent pointer of node being removed
    }

    //update affected nodes heights
    BSTNode* currentNode = node->parent; //starting from parent of removed node
    while (currentNode != nullptr) {
        setHeight(currentNode);
        currentNode = currentNode->parent;
    }

	return node; //return removed node
}


BSTNode *BST::remove(string title, string author) {
    //find node to be removed
    BSTNode *remove_node = find(title, author, root);

    //check if remove_node with given parameters is nonexistent
    if (remove_node == nullptr) {
        return nullptr;
    }
    //case 1 - node to be removed has no children
    if (remove_node->left == nullptr && remove_node->right == nullptr) {
        return removeNoKids(remove_node); //calling removeNoKids helper function
    }
    //case 2 - node to be removed has 1 child
    if (remove_node->left == nullptr || remove_node->right == nullptr){
        return removeOneKid(remove_node, remove_node->left != nullptr);
        //calling removeOneKid helper function
    }
    //case 3 - node to be removed has 2 children
    //find next largest node
    BSTNode *next_largest = remove_node->right;
    //traverse through subtree while left child is not null
    while (next_largest->left != nullptr){
        next_largest = next_largest->left;
    }
    remove_node->book = next_largest->book;//remove the largest node (has one child)

    BSTNode *removed_node;
    if (next_largest->right != nullptr) {
        //has a right child
        removed_node = removeOneKid(next_largest, false);
        //removeOneKid(next_largest, false);
    } else {
        //otherwise has no children
        removed_node = removeNoKids(next_largest);
        //removeNoKids(next_largest);
    }

    BSTNode *current = remove_node->right;
    while (current != nullptr && current->book == remove_node->book) {
        remove(current->book->title, current->book->author);
        current = current->right;
    }

    //update heights of affected nodes
    BSTNode* currentNode = remove_node->parent;
    while (currentNode != nullptr) {
        setHeight(currentNode);
        currentNode = currentNode->parent;
    }
    return removed_node;
}
    /*BSTNode *remove_node = find(title, author, root);

    //check if remove_node with given parameters is nonexistent
    if (remove_node == nullptr) {
	    return nullptr;
}
    //case 1 - node to be removed has no children
    if (remove_node->left == nullptr && remove_node->right == nullptr) {
        return removeNoKids(remove_node); //calling removeNoKids helper function
    }
    //case 2 - node to be removed has 1 child
    if (remove_node->left == nullptr || remove_node->right == nullptr){
        return removeOneKid(remove_node, remove_node->left != nullptr);
        //calling removeOneKid helper function
    }
    //case 3 - node to be removed has 2 children
    //find next largest node
    BSTNode *next_largest = remove_node->right;
    //traverse through subtree while left child is not null
    while (next_largest->left != nullptr){
        next_largest = next_largest->left;
    }
    remove_node->book = next_largest->book;//remove the largest node (has one child)

    if (next_largest->right != nullptr) {
        //has a right child
        return removeOneKid(next_largest, false);
    } else {
        //otherwise has no children
        return removeNoKids(next_largest);
    }
}*/

void BST::setHeight(BSTNode *node) {
    //if node is null, return
    if (node == nullptr) {
        return;
    }
    //use these variables to account for the height for left/right
    int l_height = 0;
    int r_height = 0;

    //check if left node is not null
    if (node->left != nullptr) {
        setHeight(node->left);// recursively call setHeight to update left node's height
        l_height = node->left->height; // updated l_height with the height of the left node
    }

    //check if right node is not null
    if (node->right != nullptr) {
        setHeight(node->right); // recursively call setHeight to update right node's height
        r_height = node->right->height; // updated l_height with the height of the right node

    }
    // height is calculated by adding 1 to the max of either the left or right child, whichever is greater
    int new_height = 1 + max(l_height, r_height);
    if (node->height != new_height) {
        node->height = new_height; //update that node's height to the new one

        setHeight(node->parent);
        }
    }