#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include "BST.h"

using namespace std;


BST::BST() {
	root = NULL;
}


void BST::AddLeaf(int key) {
	AddLeafPrivate(key, root);
}


void BST::AddLeafPrivate(int key, node* Ptr) {
	if (root == NULL) {
		root = CreateLeaf(key);
		cout << "Add " << key << " True" << endl;
	}
	else if (key < Ptr->key) {
		if (Ptr->left != NULL) {
			AddLeafPrivate(key, Ptr->left);
		}
		else {
			Ptr->left = CreateLeaf(key);
			cout << "Add " << key << " True" << endl;
		}
	}
	else if (key > Ptr->key) {
		if (Ptr->right != NULL) {
			AddLeafPrivate(key, Ptr->right);	
		}
		else {
			Ptr->right = CreateLeaf(key);
			cout << "Add " << key << " True" << endl;
		}
	}
	else {
		cout << "Add " << key << " False" << endl;
	}
}


void BST::PrintInOrder() {
	PrintInOrderPrivate(root);
}


void BST::PrintInOrderPrivate(node* Ptr) {
	
	if (root != NULL) {
		if (Ptr->left != NULL) {
			PrintInOrderPrivate(Ptr->left);
		}

		cout << Ptr->key << " ";


		if (Ptr->right != NULL) {
			PrintInOrderPrivate(Ptr->right);
		}
	}
	else {
		cout << " Empty" << endl;
	}
}


void BST::FoundValue(int key) {
	FoundValuePrivate(key, root);
}


void BST::FoundValuePrivate(int key, node* Ptr) {
	if (Ptr != NULL) {
		if (Ptr->key == key) {
			cout << "Found " << Ptr->key << endl;
		}
		else {
			if (key < Ptr->key) {
				FoundValuePrivate(key, Ptr->left);
			}
			else {
				FoundValuePrivate(key, Ptr->right);
			}
		}
	}
	else {
		cout << "Not Fount" << endl;
	}
}


int BST::ReturnRootKey() {
	if (root != NULL) {
		return root->key;
	}
}


void BST::PrintChildren(int key) {
	node* Ptr = ReturnNode(key);

	if (Ptr != NULL) {
		cout << Ptr->key << endl;
		

		if (Ptr->left == NULL) {
			cout << "_ ";
		}
		else {
			PrintChildren(Ptr->left->key);
		}
		if (Ptr->right == NULL) {
			cout << "_ ";
		}
		else {
			PrintChildren(Ptr->right->key);
		}
	}
	else {
		cout << "Key " << key << " is not in the tree " << endl;
	}
}


void BST::FindSmallest() {
	FindSmallestPrivate(root);
}


int BST::FindSmallestPrivate(node* Ptr) {
	if (root == NULL) {
		cout << "The tree is empty" << endl;
	}
	else {
		if (Ptr->left != NULL) {
			return FindSmallestPrivate(Ptr->left);
		}
		else {
			return Ptr->key;
		}
	}
}


bool BST::outLevel(node* root, int level) {
	if (root == NULL) return false;
	if (level == 0) {
		cout << " " << root->key;
		if ((root->left != NULL) || (root->right != NULL)) return true;
		return false;
	}
	if ((level == 1) && !root->left && root->right) cout << " _";
	bool left = outLevel(root->left, level - 1);
	bool right = outLevel(root->right, level - 1);
	if ((level == 1) && root->left && !root->right) cout << " _";
	return left || right;
}


void BST::toString() {

	int level = -1;
	if (root == NULL) {
		cout << "Empty" << endl;
	}
	else {
		do {
			cout << endl << " " << ++level << ":";
		} while (outLevel(root, level));
		cout << endl;
	}
}


void BST::RemoveNode(int key) {
	RemoveNodePrivate(key, root);
}


void BST::RemoveNodePrivate(int key, node* parent) {
	
	if (root != NULL) {	
		if (root->key == key) {
			RemoveRootMatch(); 
			cout << "Romove " << key << " True" << endl;
		}
		else {
			if ((key < parent->key)&& (parent->left != NULL)) {
				if (parent->left->key == key) {
					RemoveMatch(parent, parent->left, true);
					cout << "Romove " << key << " True" << endl;
				}
				else {
					RemoveNodePrivate(key, parent->left);
				}
			}
			else if ((key > parent->key) && (parent->right != NULL)) {
				if (parent->right->key == key) {
					RemoveMatch(parent, parent->right, false);
					cout << "Romove " << key << " True" << endl;
				}
				else {
					RemoveNodePrivate(key, parent->right);
				}
			}
			else {
				cout << "Romove " << key << " False" << endl;
			}
		}
	}
	else {
		cout << "The tree is empty" << endl;
	}
}


void BST::RemoveRootMatch() {
	if (root != NULL) {
		node* delPtr = root;
		int rootKey = root->key;
		int smallestInRightSubtree;

		//Case 0 - 0 children
		if (root->left == NULL && root->right == NULL) {
			root = NULL;
			delete delPtr;
		}

		//Case 1 - 1 child
		else if (root->left == NULL && root->right != NULL) {
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
		}
		else if (root->left != NULL && root->right == NULL) {
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
			
		}
		//Case 2 - 2 Children
		else {
			root = root->left;
			root->right = delPtr->right;
			delPtr->left = NULL;
			delPtr->right = NULL;
			delete delPtr;
		}
	}
	else {
		cout << "Can not remove root. The tree is empty" << endl;
	}
}


void BST::RemoveMatch(node* parent, node* match, bool left) {
	if (root != NULL) {
		node* delPtr;
		int matchKey = match->key;
		int smallestInRightSubtree;

		// Case 0 - 0 Children
		if (match->left == NULL && match->right == NULL) {
			delPtr = match;
			if (left == true) {
				parent->left = NULL;
				delete delPtr;
			}
			else {
				parent->right = NULL;
				delete delPtr;
			}
		}
		// Case 1 - 1 Child
		else if (match->left == NULL && match->right != NULL) {
			if (left == true) {
				
				parent->left = match->right;
				match->right = NULL;
				delPtr = match;
				delete delPtr;
			}
			else {
				
				parent->right = match->right;
				match->right = NULL;
				delPtr = match;
				delete delPtr;
			}
		}
		else if (match->left != NULL && match->right == NULL) {
			if (left == true) {
				
				parent->left = match->left;
				match->left = NULL;
				delPtr = match;
				delete delPtr;
			}
			else {
				//cout << "Romove " << match->left->key << " True" << endl;
				parent->right = match->left;
				match->left = NULL;
				delPtr = match;
				delete delPtr;
			}
		}
		//Case 2 - 2 Children
		else {
			if (left == true) {
				parent->left = match->left;
				delPtr = match;
				delete delPtr;
			}
			else {
				parent->right = match->left;
				match->left->right = match->right;
				delPtr = match;
				delete delPtr;
			}
		}
	}
	else {
		cout << "Cannot romove match. The tree is empty" << endl;
	}
}


BST::~BST() {
	RemoveSubtree(root);
	cout << "Clear True" << endl;
	root = NULL;
	delete root;
}


void BST::RemoveSubtree(node* Ptr) {

	if (Ptr != NULL) {
		if (Ptr->left != NULL) {
			RemoveSubtree(Ptr->left);
		}
		if (Ptr->right != NULL) {
			RemoveSubtree(Ptr->right);
		}
		Ptr = NULL;
		delete Ptr;
	}
}