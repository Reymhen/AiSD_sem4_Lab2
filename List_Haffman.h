#pragma once
#pragma once
#include <iostream>
#include <stdexcept> 
using namespace std;

template <typename T_1, typename T_2>

class ListHuffman {

private:

	class Node {
	public:
		T_1 key; // key of element
		T_2 value;
		Node* next; // pointer to the next element
	};
	Node* head; // pointer to the begin of List
	Node* tail; // pointer to the end of List

public:
	// Constructor with key and value
	ListHuffman(T_1 key, T_2 value) {

		Node* temp = new Node; // Create temporary node
		temp->key = key;
		temp->value = value;
		temp->next = tail;
		head = temp;
		tail = temp;
	}

	// Constructor without key and value
	ListHuffman() {
		head = tail = NULL;
		Node* temp = new Node; // Create temporary node
		temp->next = NULL;
		temp->key = NULL;
		temp->value = NULL;
	}

	//// Destructor
	//~List() {
	//	clearList();
	//}

	// getting list size
	int get_size() {
		int list_size = 0;
		Node* temp = head;
		while (temp != NULL) {
			list_size++;
			temp = temp->next;
		}
		return list_size;
	}

	// getting an element by index
	Node* at(size_t index) {
		if (index < get_size()) // If index is in List range
		{
			Node* temp = head; // Create temporary node
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			return temp;
		}
		else {
			throw out_of_range("The position of the element is out of range List index\n"); // Error message
		}
	}

	// checking if the list is empty
	bool isEmpty() {
		return head == NULL;
	}

	// removing all list items
	void clearList() {
		Node* temp = head; // Create temporary node
		while (head != NULL) {
			temp = head->next;
			delete head;
			head = temp;
		}
		tail = NULL;
	}

	// adding to the end of the list
	void push_back(T_1 key, T_2 value) {
		Node* temp = new Node;
		if (isEmpty() == 1) { // If List is empty  
			temp->key = key;
			temp->value = value;
			temp->next = NULL;
			head = temp;
			tail = temp;
		}
		else { // If List isn't empty
			temp->key = key;
			temp->value = value;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}

	}

	// deleting the first element deleting an element
	void pop_front() {

		if (isEmpty() == 0) // If List isn't empty
		{
			Node* temp = head; // Create temporary node
			head = head->next;
			delete temp;
			if (head == NULL) tail = head;
		}
		else {
			throw invalid_argument("List is empty. First element cannot be deleted"); // Error message 
		}
	}

	void printList() {
		Node* temp = head;
		while (temp != NULL)
		{
			cout << temp->key << " - " << temp->value << "; ";
			temp = temp->next;
		}
	}

	void sort() {
		Node* index = NULL;
		Node* current = head;
		T_1 tempKey; 
		T_2 tempValue;
		if (head == NULL) {
			return;
		}
		else {
			while (current != NULL) {
				index = current->next;
				while (index != NULL) {
					if (current->value > index->value) {
						tempKey = current->key;
						tempValue = current->value;
						current->key = index->key;
						current->value = index->value;
						index->key = tempKey;
						index->value = tempValue;
					}
					index = index->next;
				}
				current = current->next;
			}
		}
	}
	
};
