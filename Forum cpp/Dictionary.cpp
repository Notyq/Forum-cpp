#include "Dictionary.h"

Dictionary::Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = NULL;
	}
	size = 0;
}

Dictionary::~Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* temp;
		temp = items[i];
		while (temp != NULL) {
			Node* current;
			current = temp;
			temp = temp->next;
			current->next = NULL;
			delete current;
		}
	}
}

int Dictionary::hash(KeyType key) {
	int code = 0;
	for (int i = 0; i < key.length(); i++) {
		int c = key[i];
		code += c;
	}
	code = code * 52 % MAX_SIZE;
	return code;
}

bool Dictionary::add(KeyType newKey, ItemType newItem) {
	int index = hash(newKey);
	if (items[index] == NULL) {
		Node* temp = new Node;
		temp->key = newKey;
		temp->item = newItem;
		temp->next = NULL;
		items[index] = temp;
		size++;
		return true;
	}
	else {
		Node* current = items[index];
		if (current->key == newKey) {
			cout << "Collision Detected" << endl;
			return false;
		}
		while (current->next != NULL) {
			current = current->next;
			if (current->key == newKey)
			{
				cout << "Collision Detected" << endl;
				return false;
			}
		}
		Node* temp = new Node;
		temp->key = newKey;
		temp->item = newItem;
		temp->next = NULL;
		current->next = temp;
		size++;
		return true;
	}
}

void Dictionary::remove(KeyType key) {
	int index = hash(key);
	Node* temp = items[index];
	Node* newNode = new Node;
	if (items[index] != NULL) {
		if (temp->key == key) {
			items[index] = temp->next;
			delete temp;
			size--;
		}
		else {
			while (temp->next != NULL) {
				if (temp->key == key) {
					break;
				}
				newNode = temp;
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = NULL;
			temp = NULL;
			delete temp;
			size--;
		}
	}
}

ItemType Dictionary::get(KeyType key) {
	int index = hash(key);
	ItemType item;
	Node* temp = new Node;
	if (items[index] != NULL) {
		temp = items[index];
		if (temp->key != key) {
			temp = temp->next;
		}
		else {
			item = temp->item;
			return item;
		}
	}
	return item;
}

bool Dictionary::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

int Dictionary::getLength() {
	return size;
}

void Dictionary::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* temp = items[i];
		while (temp != NULL) {
			cout << "Key: " << temp->key << "       Item: " << temp->item << endl;
			temp = temp->next;
		}
	}
}