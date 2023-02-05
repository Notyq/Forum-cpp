#include <iostream>
#include "TopicList.h"
#include <vector>
using namespace std;

// constructor
TopicList::TopicList()
{
	firstNode = NULL;
	size = 0;
}


// add an item to the back of the TopicList (append)
bool TopicList::add(ItemType title)
{
	Node* newNode1 = new Node();
	newNode1->title = title;
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

bool TopicList::add(int index, ItemType title)
{
	if (index >= 0 && index <= size)
	{
		Node* newNode1 = new Node();
		newNode1->title = title;
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

void TopicList::remove(int index)
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

ItemType TopicList::get(int index) {

	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.title;
	}
}

bool TopicList::isEmpty()
{

	if (firstNode != NULL)
	{
		return false;
	}

	return true;
}

int TopicList::getLength()
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

void TopicList::print()
{
	Node* temp = new Node();
	temp = firstNode;

	while (temp != NULL)
	{
		cout << temp->title << endl;
		temp = temp->next;
	}
	cout << "----------" << endl;
}

void TopicList::swap(int index) {
	if (index == 0) return; // No need to swap the first node with itself

	Node* prev = NULL;
	Node* node = firstNode;

	// Find the node at the given index
	for (int i = 0; i < index; i++) {
		prev = node;
		node = node->next;
	}

	// Swap the node with the first node
	if (prev != NULL) {
		prev->next = firstNode;
		node->next = firstNode->next;
		firstNode->next = node->next;
		firstNode = node;
	}
}