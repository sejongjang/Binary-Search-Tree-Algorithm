#ifndef BST_H
#define BST_H

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include "BSTInterface.h"

using namespace std;

class BST : public BSTInterface {

private:

	struct node {
		int key;
		node* left;
		node* right;
	};
	node* root;
	void AddLeafPrivate(int key, node* Ptr);
	void PrintInOrderPrivate(node* Ptr);
	void FoundValuePrivate(int key, node* Ptr);
	int FindSmallestPrivate(node* Ptr);
	void RemoveNodePrivate(int key, node* parent);
	void RemoveRootMatch();
	void RemoveMatch(node* parent, node* match, bool left);
	void RemoveSubtree(node* Ptr);
	node* ReturnNodePrivate(int key, node* Ptr) {
		if (Ptr != NULL) {
			if (Ptr->key == key) {
				return Ptr;
			}
			else {
				if (key < Ptr->key) {
					return ReturnNodePrivate(key, Ptr->left);
				}
				else {
					return ReturnNodePrivate(key, Ptr->right);
				}
			}
		}
		else {
			return NULL;
		}
	}
	node* CreateLeaf(int key) {
		node* n = new node;
		n->key = key;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	node* ReturnNode(int key) {
		return ReturnNodePrivate(key, root);
	}

public:

	BST(void);
	~BST(void);

	virtual void AddLeaf(int key);
	virtual void toString();
	virtual void RemoveNode(int key);
	void PrintInOrder();
	int ReturnRootKey();
	void PrintChildren(int key);
	void FindSmallest();
	bool outLevel(node* root, int level);
	void FoundValue(int key);

	class Iterator {
	private:
		node * n;
	
	public:
		Iterator() : n(0) {}
		~Iterator() {}
		Iterator(node* ptr) : n(ptr) {}
		bool operator ==(const Iterator& it) const { return n == it.n; }
		bool operator !=(const Iterator& it) const { return n != it.n;}
		Iterator operator++() {
			
		};
		int operator*() const { return n->key; }

	};
};

#endif