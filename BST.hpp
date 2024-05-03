

#ifndef BST_HPP_
#define BST_HPP_

#include "BSTNode.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

class BST {
	friend class Library;
	BSTNode *root;

public:
	BST(); // creates an empty tree
	BST(string title, string author, int yr, string pub, long long isbn, float rate); // initializes a tree with a root
	~BST(); // destructor
	void insert(string title, string author, int yr, string pub, long long isbn, float rate); // inserts a node with the
																							// given information
	BSTNode *find(string title, string author); // finds and returns the first book that matches the title and author
												// returns null if the book does not exist
	BSTNode *find(string title, string author, BSTNode* start); // finds and returnsthe first book in the tree (starting
																// from the given subtree) that matches the title and
																// author. Returns null if the book does not exist in
																// the subtree we are searching.
	// Note: for the printing functions, each of them passes on the debug flag that was given in the function call.  It
	// is used in the printNode function to determine whether the height and parent/child information should be printed.
	void printTreeIO(bool debug); // starts the in-order print traversal at the root. Passes a debug flag for printing.
	void printTreeIO(BSTNode *node, bool debug); // recursive in-order traversal call. Passes a debug flag for printing.
	void printTreePre(bool debug); // starts the pre-order print traversal at the root. Passes a debug flag for printing.
	void printTreePre(BSTNode *node, bool debug); // recursive pre-order traversal call. Passes a debug flag for printing.
	void printTreePost(bool debug); // starts the post-order traversal call. Passes a debug flag for printing.
	void printTreePost(BSTNode *node, bool debug); // recursive post-order traversal call. Passes a debug flag for printing.
	void clearTree(); // clears the tree
	void clearTree(BSTNode *node); // recursively deletes nodes in the tree
	bool checkOut(string title, string author); // checks out a book with the title and author (and sets the book's
												// checked_out flag).  If the first book isn't available, it searches
												// the tree until it finds one that isn't. Returns a boolean
												// representing whether it was able to successfully check out a book.
	bool checkIn(string title, string author); // returns (checks in) a book with the title and author (and sets the
												// book's checked_out flag appropriately).  If the first book is already
												// returned, it searches until it finds one that isn't. Returns a
												// boolean representing whether it was able to successfully check in the
												// book.
	void updateRating(string title, string author, float newRating); // updates the rating of ALL the books that match
	BSTNode *removeNoKids(BSTNode *node); // helper function for removing a node with no children. Returns a pointer to
										// the removed node.
	BSTNode *removeOneKid(BSTNode *node, bool leftFlag); // helper function for removing a node with 1 child. The
														// leftFlag boolean indicates whether the child is the left or
														// right child of the node to be removed. Returns a pointer to
														// the removed node.
	BSTNode *remove(string title, string author); // removes the first node found with the given title/author. Returns a
												// pointer to the removed node.
	void setHeight(BSTNode *node); // helper function that updates the heights of nodes, starting from the given node.
									// Stops when the root is reached, or the height no longer updates.
};






#endif /* BST_HPP_ */
