#pragma once
#include <iostream>
#include <stdexcept> 
using namespace std;

template <typename is_typename>

class List {

private:

	class Node {
	public:
		is_typename date; // date of element
		Node* next; // pointer to the next element
	};
	Node* head; // pointer to the begin of List
	Node* tail; // pointer to the end of List

public:
	// Constructor with date
	List(is_typename date) {

		Node* temp = new Node; // Create temporary node
		temp->date = date;
		temp->next = tail;
		head = temp;
		tail = temp;
	}

	// Constructor without date
	List() {
		head = tail = NULL;
		Node* temp = new Node; // Create temporary node
		temp->next = NULL;
		temp->date = NULL;
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
	Node* get_head() {
		return head;
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
	void push_back(is_typename date) {
		Node* temp = new Node;
		if (isEmpty() == 1) { // If List is empty  
			temp->date = date;
			temp->next = NULL;
			head = temp;
			tail = temp;
		}
		else { // If List isn't empty
			temp->date = date;
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
		while (/*head */temp!= NULL)
		{
			cout << temp->date << " ";
			temp = temp->next;
			/*pop_front();*/
		}
	}
	
};
