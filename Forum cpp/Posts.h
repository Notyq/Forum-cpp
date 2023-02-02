#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef string ItemType;

#include "Topic.h"

class Posts : public Topic {

	private:
	struct Node
	{
		ItemType user;
		ItemType id;
		ItemType post;	// item
		ItemType title; // title
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

	public:
	// constructor
	Posts();

	// destructor
	//~List();

	// add an item to the back of the list (append)
	bool add(ItemType post, ItemType t, ItemType id, ItemType user);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType post, ItemType t, ItemType id, ItemType user);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	ItemType getPost(int index);

	ItemType getTitle(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void print();

	string getUser(int index);

	string getID(int index);
};