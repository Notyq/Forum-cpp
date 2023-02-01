#include "Reply.h"

Reply::Reply() { };

Reply::~Reply() {
	while (topNode != NULL) {
		this->pop();
	}
}

bool Reply::push(ItemType item, ItemType id) {
	Node* n = new Node;
	n->item = item;
	n->next = NULL;
	n->id = id;

	n->next = topNode;
	topNode = n;

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
		ds.push(temp->item, temp->id);
		temp = temp->next;
	}
	ds.displayInOrder();
}
