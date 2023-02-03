#pragma once
#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef string ItemType;

class ReplyList
{
private:
	struct Node
	{
		ItemType user;
		ItemType id;
		ItemType item;
		Node* next;
	};

	int size;
	Node* topNode;

public:
	//Default constructor
	ReplyList();
	//Destructor
	~ReplyList();

	//check if the stack is empty
	bool isEmpty();

	//push item on top of the stack
	bool push(ItemType item, ItemType id, ItemType user);

	//pop item from top of stack
	bool pop();

	//retrieve and pop item from top of stack
	bool pop(ItemType& item, ItemType& id);

	//retrieve item from top of stack
	void getTop(ItemType& item, ItemType& id);

	//display items in stack in order
	void displayInOrder();

	//display items in stack in order of insertion
	void displayInOrderOfInsertion();

	ItemType getID(int index);

	ItemType get(int index);

	int getLength();
};