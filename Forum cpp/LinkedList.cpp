// List.cpp - Implementation of List ADT using Array
#include "LinkedList.h" // header file

// constructor
List::List()
{
	firstNode = NULL;
	size = 0;
}

// add an item to the back of the list (append)
bool List::add(ItemType item)
{
	Node* newNode1 = new Node();
	newNode1->item = item;
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

bool List::add(int index, ItemType item)
{
	if (index >= 0 && index <= size)
	{
		Node* newNode1 = new Node();
		newNode1->item = item;
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

void List::remove(int index)
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

ItemType List::get(int index)
{

	if (index >= 0 && index <= size)
	{

		Node* temp = new Node();
		for (int i = 0; i <= index; i++)
		{
			temp = temp->next;
		}

		return temp->item;
	}
}

bool List::isEmpty()
{

	if (firstNode != NULL)
	{
		return false;
	}

	return true;
}

int List::getLength()
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

void List::print()
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