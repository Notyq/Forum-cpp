#pragma once
#pragma once
#include <iostream>
#include <string>

using namespace std;

//typedef int ItemType;
//typedef string ItemType;
typedef string ItemType;

class Reply
{
private:
	struct Node
	{
		ItemType id;
		ItemType item;
		Node* next;
	};


	Node* topNode;

public:
	//Default constructor
	Reply();
	//Destructor
	~Reply();

	//check if the stack is empty
	bool isEmpty();

	//push item on top of the stack
	bool push(ItemType item, ItemType id);

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
};