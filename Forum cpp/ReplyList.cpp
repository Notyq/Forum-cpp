// ReplyList.cpp - Implementation of ReplyList ADT using Array
#include "ReplyList.h" // header file

// constructor
ReplyList::ReplyList()
{
	firstNode = NULL;
	size = 0;
}

// add an item to the back of the Reply (append)
bool ReplyList::add(ItemType item, ItemType user, ItemType id)
{
	Node* newNode1 = new Node();
	newNode1->item = item;
	newNode1->user = user;
	newNode1->id = id;
	newNode1->next = NULL;

	if (size == 0)
	{
		firstNode = newNode1;
	}

	else
	{
		Node* temp = firstNode;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode1;
	}
	size++;
	return true;
}

bool ReplyList::add(int index, ItemType item, ItemType user, ItemType id)
{
	if (index >= 0 && index <= size)
	{
		Node* newNode1 = new Node();
		newNode1->item = item;
		newNode1->user = user;
		newNode1->id = id;
		newNode1->next = NULL;

		if (index == 0)
		{
			newNode1->next = firstNode;
			firstNode = newNode1;
		}
		else
		{
			Node* temp = firstNode;
			for (int i = 1; i < index; i++)
			{
				temp = temp->next;
			}
			newNode1->next = temp->next;
			temp->next = newNode1;
		}

		size++;
		return true;
	}
	return false;
}

void ReplyList::remove(int index)
{
	if (index >= 0 && index <= size)
	{

		if (index == 0)
		{
			Node* del = new Node();
			del = firstNode;
			firstNode = firstNode->next;
			delete del;
			del = NULL;
		}
		else
		{

			Node* temp = firstNode;

			for (int i = 1; i < index; i++)
			{
				temp = temp->next;
			}
			Node* del = new Node();
			del = temp->next;
			temp->next = temp->next->next;
			delete del;
			del = NULL;
		}

		size--;
	}
}

ItemType ReplyList::get(int index) {

	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.item;
	}
}

bool ReplyList::isEmpty()
{

	if (firstNode != NULL)
	{
		return false;
	}

	return true;
}

int ReplyList::getLength()
{

	int i = 0;
	Node* temp = new Node();
	temp = firstNode;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}

	return i;
}

void ReplyList::print()
{
	Node* temp = new Node();
	temp = firstNode;

	while (temp != NULL)
	{
		cout << temp->item << endl;
		temp = temp->next;
	}
	cout << "----------" << endl;
}

string ReplyList::getID(int index) {
	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.id;
	}
}

string ReplyList::getUser(int index) {
	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.user;
	}
}