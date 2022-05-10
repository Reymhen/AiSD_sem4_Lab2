#pragma once
#include <iostream>
#include "List.h"
//#include "Ñoding.h"
using namespace  std;

template <typename key_typename, typename value_typename>

class RBtree {
private:

	class Node
	{
	public:
		bool color; // true (1) - red, false(0) - black
		key_typename key;
		value_typename value;
		Node* parents;
		Node* left;
		Node* right;
	};

	Node* root;  // pointer to the root of RBTree
	Node* nil;
	size_t size;
	// left turn knots of RBTree
	void leftRotate(Node* node_x) { 
		Node* node_y = node_x->right;
		node_x->right = node_y->left;
		if (node_y->left != NULL)
			node_y->left->parents = node_x;

		node_y->parents = node_x->parents;
		if (node_x->parents == NULL)
			root = node_y;
		else {
			if (node_x == node_x->parents->left)
				node_x->parents->left = node_y;
			else
				node_x->parents->right = node_y;
		}
		node_y->left = node_x;
		node_x->parents = node_y;
	}; 
	// right turn knots of RBTree
	void rightRotate(Node* node_y) { 
		Node* node_x = node_y->left;
		node_y->left = node_x->right;
		if (node_x->right != NULL)
			node_x->right->parents = node_y;

		node_x->parents = node_y->parents;
		if (node_y->parents == NULL)
			root = node_x;
		else {
			if (node_y == node_y->parents->right)
				node_y->parents->right = node_x;
			else
				node_y->parents->left = node_x;
		}
		node_x->right = node_y;
		node_y->parents = node_x;
	};

	// RBtree property return functions
	void InsertFixUp(Node* node)
	{
		Node* parent;
		parent = node->parents;
		while (node != root && parent->color == true)
		{
			Node* gparent = parent->parents;
			if (gparent->left == parent)
			{
				Node* uncle = gparent->right;
				if (uncle != NULL && uncle->color == true)
				{
					parent->color = false;
					uncle->color = false;
					gparent->color = true;
					node = gparent;
					parent = node->parents;
				}
				else
				{
					if (parent->right == node)
					{
						leftRotate(parent);
						swap(node, parent);
					}
					rightRotate(gparent);
					gparent->color = true;
					parent->color = false;
					break;
				}
			}
			else
			{
				Node* uncle = gparent->left;
				if (uncle != NULL && uncle->color == true)
				{
					gparent->color = true;
					parent->color = false;
					uncle->color = false;

					node = gparent;
					parent = node->parents;
				}
				else
				{
					if (parent->left == node)
					{
						rightRotate(parent);
						swap(parent, node);
					}
					leftRotate(gparent);
					parent->color = false;
					gparent->color = true;
					break;
				}
			}
		}
		root->color = false;
	};
	void removeFixUp(Node* node)
	{
		Node* otherNode;
		Node* parent;
		parent = node->parents;
		while ((!node) || node->color == false && node != root)
		{
			if (parent->left == node)
			{
				otherNode = parent->right;
				if (otherNode->color == true)
				{
					otherNode->color = false;
					parent->color = true;
					leftRotate(parent);
					otherNode = parent->right;
				}
				else
				{
					if (!(otherNode->right) || otherNode->right->color == false)
					{
						otherNode->left->color = false;
						otherNode->color = true;
						rightRotate(otherNode);
						otherNode = parent->right;
					}
					otherNode->color = parent->color;
					parent->color = false;
					otherNode->right->color = false;
					leftRotate(parent);
					node = root;
					break;
				}
			}
			else
			{
				otherNode = parent->left;
				if (otherNode->color == true)
				{
					otherNode->color = false;
					parent->color = true;
					rightRotate(parent);
					otherNode = parent->left;
				}
				if ((!otherNode->left || otherNode->left->color == false) && (!otherNode->right || otherNode->right->color == false))
				{
					otherNode->color = true;
					node = parent;
					parent = node->parents;
				}
				else
				{
					if (!(otherNode->left) || otherNode->left->color == false)
					{
						otherNode->right->color = false;
						otherNode->color = true;
						leftRotate(otherNode);
						otherNode = parent->left;
					}
					otherNode->color = parent->color;
					parent->color = false;
					otherNode->left->color = false;
					rightRotate(parent);
					node = root;
					break;
				}
			}
		}
		if (node)
			node->color = false;
	};
	//helper print function that implements pre-order traversal tree
	void printHelp(Node* node) {
		if (node != nil) {
			cout << node->key << " : " << node->value << endl;
			if (node->left != NULL && node->left != nil)
				printHelp(node->left);
			if (node->right != NULL && node->right != nil)
				printHelp(node->right);
		}
	};
	//knot sweeping function
	void movingNodes(Node* current, Node* newNode)
	{
		if (current->parents == NULL) { 
			current = newNode; 
		}
		else if (current == current->parents->left) {
			current->parents->left = newNode;
		}
		else { current->parents->right = newNode; }
		newNode->parents = current->parents;

	};
	//helper function that implements pre-order traversal tree
	List<key_typename> getHelpKey(List<key_typename> list, Node* node) {
		if (node != nil) {
			list.push_back(node->key);
			if (node->left != NULL && node->left != nil)
				list = getHelpKey(list, node->left);
			if (node->right != NULL && node->right != nil)
				list = getHelpKey(list, node->right);
			return list;
		}
	};

	List<value_typename> getHelpValue(List<value_typename> list, Node* node) {
		if (node != nil) {
			list.push_back(node->value);
			if (node->left != NULL && node->left != nil)
				list = getHelpValue(list, node->left);
			if (node->right != NULL && node->right != nil)
				list = getHelpValue(list, node->right);
			return list;
		}
	};

	
public:

	RBtree() {
		nil = new Node;
		nil->color = 0;
		nil->left = nullptr;
		nil->right = nullptr;
		root = nil;
		size = 0;
	};
	~RBtree() {
		clear();
	};

	bool isEmpty() {
		if (root == nil) { return true; }
		else return false;
	}
	bool at(key_typename key){
		Node* newNode = root;
		bool flag = 0;
		//if the desired node is the root 
		if (newNode->key == key) {
			return true;
			flag = 1;
		}
		else {
			while (newNode != nil) {
				if (newNode->key == key) {
					return true;
					flag = 1;
				}
				else
					if (key > newNode->key) { newNode = newNode->right; }
					else
						if (key < newNode->key) { newNode = newNode->left; }
			}
		}
		if (flag == 0) return false;
	};
	size_t get_size() {
		return size;
	}
	// adding element with key and value
	void insert(key_typename key, value_typename value) 
	{
		Node* newNode = new Node;
		newNode->color = true;
		newNode->key = key;
		newNode->value = value;
		newNode->right = nil;
		newNode->left = nil;
		newNode->parents = NULL;
		size++;
		//if tree is empty -> newNode is root
		if (root == nil) {
			newNode->color = false;
			root = newNode;
			return;
		}
		else {
			Node* currentRoot = root;
			Node* parNewNode = NULL;
			//find in which part of the tree, according to the rule, a new node should be inserted
			while (currentRoot != nil) {
				parNewNode = currentRoot;
				if (newNode->key < currentRoot->key) {
					currentRoot = currentRoot->left;
				}
				else {
					currentRoot = currentRoot->right;
				}
			}
			newNode->parents = parNewNode;
			
			if (newNode->key < parNewNode->key)
				parNewNode->left = newNode;
			else
				parNewNode->right = newNode;
		}
		InsertFixUp(newNode);
	};
	// deleting an element by key
	void remove(key_typename key) 
	{
		Node* nodeToBeDeleted = find(key);
		bool colorDeleted = nodeToBeDeleted->color;
		Node* temp = nodeToBeDeleted;
		Node* y;
		//if the left leaf of the tree is nil
		if (nodeToBeDeleted->left == nil) {
			temp = nodeToBeDeleted->right;
			movingNodes(nodeToBeDeleted, temp);
			if (root == nodeToBeDeleted) root = temp;
			delete nodeToBeDeleted;
		}
		//if the right leaf of the tree is nil
		else if (nodeToBeDeleted->right == nil) {
			temp = nodeToBeDeleted->left;
			movingNodes(nodeToBeDeleted, temp);
			if (root == nodeToBeDeleted) root = temp;
			delete nodeToBeDeleted;
		}
		//if the right and left leaf of the tree is not nil
		else {
			y = nodeToBeDeleted->right;
			while (y->left != nil) {
				y = y->left;
			}
			colorDeleted = y->color;
			temp = y->right;
			if (y->parents == nodeToBeDeleted) {
				temp->parents = y;
			}
			else {
				movingNodes(y, y->right);
				y->right = nodeToBeDeleted->right;
				y->right->parents = y;
			}
			movingNodes(nodeToBeDeleted, y);
			y->left = nodeToBeDeleted->left;
			y->left->parents = y;
			y->color = nodeToBeDeleted->color;

			if (root == nodeToBeDeleted) { 
				y->parents = NULL;
				root = y; 
			}
			delete nodeToBeDeleted;
			if (colorDeleted == 0) {
				removeFixUp(temp);
			}
		}
		size--;

	};
	//find element by key
	Node* find(key_typename key) 
	{
		Node* newNode = root;
		bool flag = 0;
		//if the desired node is the root 
		if (newNode->key == key) {
			return newNode;
			flag = 1;
		}
		else {
			while (newNode != nil) {
				if (newNode->key == key) {
					return newNode;
					flag = 1;
				}
				else
					if (key > newNode->key) { newNode = newNode->right; }
					else
						if (key < newNode->key) { newNode = newNode->left; }
			}
		}
		if (flag == 0) throw out_of_range("There is no element with this key in the map\n");
	};
	//clearing an associative array
	void clear() 
	{
		while ((root != nil) && (root != NULL))
			remove(root->key);
		root = nil;
		size = 0;
	};
	//returns a list of keys
	List <key_typename> get_keys()
	{
		List <key_typename> listKey;
		if (root == NULL || root == nil) {
			throw out_of_range("Map is empty\n");
		}
		else {
			listKey = getHelpKey(listKey, root);
			return listKey;
			/*listKey.printList();*/
		}
	}
	//returns a list of values
	List <value_typename> get_values()
	{
		List <value_typename> listValue;
		if (root == NULL || root == nil) {
			throw out_of_range("Map is empty\n");
		}
		else {
			listValue = getHelpValue(listValue, root);
			return listValue;
			/*listValue.printList();*/
		}
	}
	//prints map
	void print() {
		if (root == nil)
			cout << "Map is empty\n" << endl;
		else 
			printHelp(root);
	};	
	
};