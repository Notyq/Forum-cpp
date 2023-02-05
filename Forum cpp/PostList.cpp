#include <iostream>
#include "PostList.h"
#include <vector>
using namespace std;

// constructor
PostList::PostList()
{
	firstNode = NULL;
	size = 0;
}

// destructor
//PostList::~PostList() {
//	for (int i = 0; i < size; i++) {
//		this->remove(i);
//	}
//}

// add an item to the back of the PostList (append)
bool PostList::add(ItemType post, ItemType t, ItemType id, ItemType user, ItemType likes)
{
	Node* newNode1 = new Node();
	newNode1->likes = likes;
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

// add an item at a specified position in the list (insert)
bool PostList::add(int index, ItemType post, ItemType t, ItemType id, ItemType user, ItemType likes)
{
	if (index >= 0 && index <= size)
	{
		Node* newNode1 = new Node();
		newNode1->likes = likes;
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

// remove an item at a specified position in the list
void PostList::remove(int index)
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

// deletes nodes if node.id = id
void PostList::remove(string id)
{
	Node* current = firstNode;
	Node* previous = nullptr;
	while (current != nullptr) {
		if (current->id == id) {
			if (previous == nullptr) {
				firstNode = current->next;
			}
			else {
				previous->next = current->next;
			}
			delete current;
			size--;
			break;
		}
		previous = current;
		current = current->next;
	}
}

// get an item at a specified position of the list (retrieve)
ItemType PostList::getPost(int index) {

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

// get the title at a specified position of the list (retrieve)
ItemType PostList::getTitle(int index) {

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

// returns true if title is in list of post
bool PostList::compareTitle(string title) {

	Node* temp = firstNode;

	while (temp != NULL) {
		if (temp->title != title) {
			temp = temp->next;
		}
		else
		{
			return true;
		}
	}

	return false;
}

// check if the list is empty
bool PostList::isEmpty()
{

	if (firstNode != NULL)
	{
		return false;
	}

	return true;
}

// check the size of the list
int PostList::getLength()
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

// display all the items in the list
void PostList::print()
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

// get the user at a specified position of the list (retrieve)
string PostList::getUser(int index) {

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

// get the ID at a specified position of the list (retrieve)
ItemType PostList::getID(int index) {
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

// returns true if id is in list of post
bool PostList::compareID(string id) {
	Node* temp = firstNode;

	while (temp != NULL) {
		if (temp->id != id) {
			temp = temp->next;
		}
		else
		{
			return true;
		}
	}

	return false;
}

// get the amount of likes of a specific post at the specified position of the list (retrieve)
string PostList::getLikes(int index) {
	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.likes;
	}
}

// returns true if like attribute is increased
bool PostList::giveLike(int index) {
	index = index - 1;
	if (index >= 0 && index <= size - 1) {
		Node* ptr;
		ptr = firstNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		int likes = stoi(ptr->likes) + 1;
		ptr->likes = to_string(likes);
		return true;
	}
	return false;
}

// swaps node at index with firstNode
void PostList::swap(string id) {
	if (size < 1) return; // No need to swap the first node with itself

	Node* prev = NULL;
	Node* node = firstNode;

	while (node != NULL && node->id != id) {
		prev = node;
		node = node->next; // traverse to the next node
	}

	if (prev != NULL) {
		// Swap the node with the first node
		prev->next = node->next;
		node->next = firstNode;
		firstNode = node;
	}
}