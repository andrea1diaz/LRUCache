#include <iostream>
#include "LRUCache.hpp"

LRUCache::LRUCache(int size) {
	this->size = size;
	root = new node;
	tail = new node;
	root->next_node = tail; 
}

bool LRUCache::insertKeyValuePair (char key, int value) {
	if (!root->data.first) {
		root->data.first = key;
		root->data.second = value;

		counter ++;
		return true;
	}

	else {
		if (LRUCache::getValueFromKey (key)) return false;

		if (counter >= size) {
			node *tmp = root->next_node;
			root = tmp;
		}

		node *new_node = new node;
		new_node->data.first = key;
		new_node->data.second = value;
		
		node *tmp = root;
		while (tmp->next_node != nullptr) {
			tmp = tmp->next_node;
		}

		tmp->next_node = new_node;
		tail = new_node;

		counter ++;
		return true;
	}

	return false;
}

void LRUCache::getMostRecentKey() {
	std::cout << tail->data.first << std::endl;
}

bool LRUCache::getValueFromKey (char key) {
	node *tmp = root;

	while (tmp != nullptr) {
		if (tmp->data.first == key) {
			std::cout << tmp->data.second << std::endl;
	
			if (tmp->next_node == nullptr) return true;
			else tail = tmp;

			return true;
		}

		tmp = tmp->next_node;
	}

	return false;
}

