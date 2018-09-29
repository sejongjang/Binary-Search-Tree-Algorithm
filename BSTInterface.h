//YOU MAY NOT MODIFY THIS DOCUMENT
#ifndef BST_INTERFACE_H
#define BST_INTERFACE_H
#include <string>
using std::string;

/** A binary tree node with data, left and right child pointers */

class BSTInterface
{
public:
	BSTInterface(void) {}
	~BSTInterface(void) {}

	/** Return true if node added to BST, else false */
	virtual void AddLeaf(int data) = 0;

	/** Return true if node removed from BST, else false */
	virtual void RemoveNode(int data) = 0;

	/** Return a level order traversal of a BST as a string */
	virtual void toString() = 0;
};
#endif	// BST_INTERFACE_H