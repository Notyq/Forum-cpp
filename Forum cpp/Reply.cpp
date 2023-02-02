#include "Reply.h"

Reply::Reply() 
{
	topNode = NULL;
	size = 0;
}

Reply::~Reply() {
	while (topNode != NULL) {
		this->pop();
	}
}

bool Reply::push(ItemType item, ItemType id, ItemType user) {
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

bool Reply::isEmpty() {
	bool check;
	if (topNode == NULL) {
		check = true;
	}
	else {
		check = false;
	}
	return check;
}

bool Reply::pop() {
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

bool Reply::pop(ItemType& item, ItemType& id) {
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

void Reply::getTop(ItemType& item, ItemType& id) {
	if (topNode != NULL) {
		item = topNode->item;
		id = topNode->id;
	}
}

void Reply::displayInOrder() {
	Node* temp;
	temp = topNode;
	while (temp != NULL) {
		//cout << temp->item << endl;
		temp = temp->next;
	}
	cout << "---" << endl;
}

void Reply::displayInOrderOfInsertion() {
	Node* temp;
	temp = topNode;
	Reply ds = Reply();
	while (temp != NULL) {
		ds.push(temp->item, temp->id, temp->user);
		temp = temp->next;
	}
	ds.displayInOrder();
}

ItemType Reply::getID(int index) {
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

ItemType Reply::get(int index) {
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

int Reply::getLength()
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