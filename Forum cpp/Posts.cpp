#include <iostream>
#include "Posts.h"
#include <vector>
using namespace std;

// constructor
Posts::Posts()
{
	firstNode = NULL;
	size = 0;
}

// add an item to the back of the Posts (append)
bool Posts::add(ItemType post, ItemType t, ItemType id, ItemType user)
{
	Node* newNode1 = new Node();
	newNode1->post = post;
	newNode1->title = t;
	newNode1->id = id;
	newNode1->user = user;
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

bool Posts::add(int index, ItemType post, ItemType t, ItemType id, ItemType user)
{
	if (index >= 0 && index <= size)
	{
		Node* newNode1 = new Node();
		newNode1->post = post;
		newNode1->title = t;
		newNode1->id = id;
		newNode1->user = user;
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

void Posts::remove(int index)
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

ItemType Posts::getPost(int index) {

	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.post;
	}
}

ItemType Posts::getTitle(int index) {

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

bool Posts::isEmpty()
{

	if (firstNode != NULL)
	{
		return false;
	}

	return true;
}

int Posts::getLength()
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

void Posts::print()
{
	Node* temp = new Node();
	temp = firstNode;

	while (temp != NULL)
	{
		cout << temp->post << " " << temp->title << " " << temp->id << " " << temp->user << endl;
		temp = temp->next;
	}
	cout << "----------" << endl;
}

bool Posts::getUser(string user) {

	Node* temp = new Node();
	temp = firstNode;

	while (temp != NULL) {
		if (temp->user != user) {
			return false;
			temp = temp->next;
		}
		else
		{
			return true;
			temp = temp->next;
		}
	}
	return true;
}