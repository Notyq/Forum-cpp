#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef string ItemType;

class TopicList {

protected:

	struct Node
	{
		ItemType title;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

	//string title;	
	//string desc;

public:
	//constructor
	TopicList();

	// destructor
	//~List();

	// add an item to the back of the list (append)
	bool add(ItemType title);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType title);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	ItemType get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void print();
};