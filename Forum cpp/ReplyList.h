// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class ReplyList
{
private:
	struct Node
	{
		ItemType user; 
		ItemType id;
		ItemType item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	ReplyList();

	// destructor
	//~ReplyList();

	// add an item to the back of the list (append)
	bool add(ItemType item, ItemType user, ItemType id);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType item, ItemType user, ItemType id);

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

	// gets the id of reply at a specific index
	ItemType getID(int index);

	// gets the user of reply at a specific index
	string getUser(int index);
};
