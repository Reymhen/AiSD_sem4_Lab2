#pragma once
#include <iostream>
#include "Red-Black tree.h"
#include "List_Haffman.h"

using namespace std;

class CodeHuffman {
private:
	class Element {

	public:

		char symbol;
		size_t frequency;
		string cod;
		Element* parents;
		Element* left;
		Element* right;
		Element* next;
	};
	size_t sizeTree;
	Element* root;
	Element* tail;
	Element* head;


	// checking if the list is empty
	bool isEmpty() {
		return head == NULL;
	}

	size_t get_size() {
		return sizeTree;
	}

	RBtree<char, int> map;
	string oridginalString;
	string codingString;
	string decodingString;

	//helper print function that implements pre-order traversal tree
	void printHelp(Element* node) {
		if (node->frequency != NULL){
			cout << node->frequency << " : " << node->cod << endl;
			if (node->left != NULL)
				printHelp(node->left);
			if (node->right != NULL)
				printHelp(node->right);
		}
	};
	float memory(string inputString) {
		int memory = inputString.length() * 8;
		return memory;
	};
	void sorting() {
		Element* index = NULL;
		Element* current = head;
		Element* tempLeft = NULL;
		Element* tempRight = NULL;
		char tempSymb;
		size_t tempFreq;
		if (head == NULL) {
			return;
		}
		else {
			while (current != NULL) {
				index = current->next;
				while (index != NULL) {
					if (current->frequency > index->frequency) {
						tempSymb = current->symbol;
						tempFreq = current->frequency;
						tempLeft = current->left;
						tempRight = current->right;
						current->symbol = index->symbol;
						current->frequency = index->frequency;
						current->left = index->left;
						current->right = index->right;
						index->symbol = tempSymb;
						index->frequency = tempFreq;
						index->left = tempLeft;
						index->right = tempRight;
					}
					index = index->next;
				}
				current = current->next;
			}
		}
	}
	void cod(Element* help) {
		if (help->frequency != NULL) /*return;*/ {
			if (help->left != NULL) {
				help->left->cod = help->cod + '0';
				cod(help->left);
			}
			if (help->right != NULL){
				help->right->cod = help->cod + '1';
				cod(help->right);
			}
		}
		
	}	
	void Table(Element* node, RBtree<char, string>& tab) {
		if (node->frequency != NULL) /*return;*/ {
			if (map.at(node->symbol)) { 
				tab.insert(node->symbol, node->cod);
			}			
			if (node->right != NULL)
				Table(node->right, tab);
			if (node->left != NULL)
				Table(node->left, tab);
		}
	};
	Element* at(size_t index) {
		if (index < get_size()) // If index is in List range
		{
			Element* temp = head; // Create temporary node
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			return temp;
		}
		else {
			throw out_of_range("The position of the element is out of range List index\n"); // Error message
		}
	}	
	//Inserting an item at the beginning of a list
	void push_front(Element* value) {
		Element* current = new Element;
		if (head == NULL) {
			current = value;
			head = current;
			tail = head;
			sizeTree++;
		}
		else {
			current = value;
			current->next = head;
			tail = head;
			head = current;
			sizeTree++;
		}
	}
public:
	CodeHuffman(string str) {
		sizeTree = 0;
		root = NULL;
		tail = NULL;
		head = NULL;
		oridginalString = str;
		creatingAnEncodingTable(oridginalString, map);
	};	
	float compressionRatio(string inputString, string outputString) {
		float compression =/* input / output;*/ memory(inputString) / memory(outputString);
		return compression;
	};
	void creatingAnEncodingTable(string inputString, RBtree<char, int>& map) {
		if (inputString.length() == 0) {
			throw invalid_argument("Input string is empty\n");
		}
		else {
			for (int i = 0; inputString[i] != '\0'; i++) {
				if (map.isEmpty()) {
					map.insert(inputString[i], 1);
				}
				else {
					if (map.at(inputString[i])) {
						map.find(inputString[i])->value++;
					}
					else {
						map.insert(inputString[i], 1);
					}
				}
			}
		}

	};
	void creatingHuffmanTree(RBtree<char, int>& map) {
		ListHuffman <char, int> leaf;
		Element* current_head = new Element;
		Element* help1 = new Element;
		Element* help2 = new Element;
		List <char> key = map.get_keys();
		List <int> value = map.get_values();
		for (int i = 0; i < map.get_size(); i++) {
			leaf.push_back(key.get_head()->date, value.get_head()->date);
			key.pop_front();
			value.pop_front();
		}
		leaf.sort();
		int index = 0;
		//Внесли в дерево листы 
		while (leaf.get_size() != index) {
			Element* current = new Element;
			if (head == NULL) {
				current->frequency = leaf.at(index)->value;
				current->symbol = leaf.at(index)->key;
				current->left = NULL;
				current->right = NULL;
				head = current;
				tail = head;
				sizeTree++;
				index++;
			}
			else {
				current->frequency = leaf.at(index)->value;
				current->symbol = leaf.at(index)->key;
				current->left = NULL;
				current->right = NULL;
				tail->next = current;
				tail = current;
				sizeTree++;
				index++;
			}
		}
		while (leaf.get_size() != 1) {
			Element* current = new Element;
			current->frequency = leaf.at(0)->value + leaf.at(1)->value;
			current->symbol = '\0';
			current->left = at(0);
			current->left->parents = current;
			current->right = at(1);
			current->right->parents = current;
			if (leaf.get_size() >= 3) {
				push_front(current);
				current->next = at(3);
				current->left->next = NULL;
				current->right->next = NULL;
				sorting();
			}
			leaf.pop_front();
			leaf.pop_front();
			leaf.push_back(current->symbol, current->frequency);
			leaf.sort();
			root = current;
		}
	}
	
	void coding() {
		RBtree<char, string> tab;
		Table(root,tab);
		cout << "Code table:" << endl;
		tab.print();
		for (int i = 0; i < oridginalString.length(); i++) {
			codingString = codingString + tab.find(oridginalString[i])->value;
		}
		cout <<"Ecoded string:\n"<< codingString << endl;
	}
	void decoding() {
		int index = 0;
		Element* current = root;
		while (index != codingString.length()) {
			if (current->left != NULL) {
				if (codingString[index] == '0') {
					current = current->left;
					index++;
				}
				else {
					current = current->right;
					index++;
				}
			}
			if (current->left == NULL) {
				decodingString = decodingString + current->symbol;
				current = root;
			}

		}
		cout << "Decoded string:\n"<< decodingString << endl ;
	}
	void printTree() {
		if (root == NULL)
			cout << "Map is empty\n" << endl;
		else
			printHelp(root);
	}
	void create() {
		cout << "\nFrequency table:" << endl;
		map.print();
		creatingHuffmanTree(map);
		cod(root);
		coding();
		decoding();
		cout << "Compression ratio:\n" << compressionRatio(codingString, decodingString) << endl;
	}

};
