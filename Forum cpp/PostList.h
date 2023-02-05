#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef string ItemType;

#include "TopicList.h"

class PostList : public TopicList {

	private:
	struct Node
	{
		ItemType likes;
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
	PostList();

	// destructor
	//~PostList();

	// add an item to the back of the list (append)
	bool add(ItemType post, ItemType t, ItemType id, ItemType user, ItemType likes);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType post, ItemType t, ItemType id, ItemType user, ItemType likes);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	ItemType getPost(int index);

	// get the title at a specified position of the list (retrieve)
	ItemType getTitle(int index);

	// returns true if title is in list of post
	bool compareTitle(string title);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void print();

	// get the user at a specified position of the list (retrieve)
	string getUser(int index);

	// get the ID at a specified position of the list (retrieve)
	ItemType getID(int index);

	// returns true if id is in list of post
	bool compareID(string id);

	// get the amount of likes of a specific post at the specified position of the list (retrieve)
	string getLikes(int index);

	// returns true if like attribute is increased
	bool giveLike(int index);

	// swaps node at index with firstNode
	void swap(string id);
};