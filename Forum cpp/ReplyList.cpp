#include "ReplyList.h"

ReplyList::ReplyList() 
{
	topNode = NULL;
	size = 0;
}

ReplyList::~ReplyList() {
	while (topNode != NULL) {
		this->pop();
	}
}

bool ReplyList::push(ItemType item, ItemType id, ItemType user) {
	Node* n = new Node;
	n->item = item;
	n->user = user;
	n->next = NULL;
	n->id = id;

	n->next = topNode;
	topNode = n;
	size++;

	return true;
}

bool ReplyList::isEmpty() {
	bool check;
	if (topNode == NULL) {
		check = true;
	}
	else {
		check = false;
	}
	return check;
}

bool ReplyList::pop() {
	if (topNode != NULL) {
		Node* temp = topNode;
		topNode = topNode->next;
		temp->next = NULL;
		delete temp;
		return true;
		size--;
	}
	return false;
}

bool ReplyList::pop(ItemType& item, ItemType& id) {
	if (topNode != NULL) {
		Node* temp = topNode;
		topNode = topNode->next;
		item = temp->item;
		id = temp->id;
		temp->next = NULL;
		delete temp;
		return true;
		size--;
	}
	return false;
}

void ReplyList::getTop(ItemType& item, ItemType& id) {
	if (topNode != NULL) {
		item = topNode->item;
		id = topNode->id;
	}
}

void ReplyList::displayInOrder() {
	Node* temp;
	temp = topNode;
	while (temp != NULL) {
		//cout << temp->item << endl;
		temp = temp->next;
	}
	cout << "---" << endl;
}

void ReplyList::displayInOrderOfInsertion() {
	Node* temp;
	temp = topNode;
	ReplyList ds = ReplyList();
	while (temp != NULL) {
		ds.push(temp->item, temp->id, temp->user);
		temp = temp->next;
	}
	ds.displayInOrder();
}

ItemType ReplyList::getID(int index) {
	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = topNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.id;
	}
}

ItemType ReplyList::get(int index) {
	if (index >= 0 && index <= size - 1) {

		Node* ptr;
		ptr = topNode;

		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		Node n = *ptr;
		return n.item;
	}
}

int ReplyList::getLength()
{
	int i = 0;
	Node* temp = new Node();
	temp = topNode;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}

	return i;
}