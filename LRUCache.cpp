#include <iostream>
#include "LRUCache.hpp"

template <typename T, typename W>
LRUCache<T, W>::LRUCache(int size) {
	this->size = size;
	root_key = tail_key = NULL;
}

template <typename T, typename W>
bool LRUCache<T, W>::insertKeyValuePair (T key, W value) {
	auto root = cache.find(root_key);
	auto tail = cache.find(tail_key);

	if (!root_key) {
		node *new_node = new node(value);
		cache.insert({key, new_node});
		root_key = tail_key = key;

		counter ++;
		return true;
	}

	else {
		if (cache.find(key) != cache.end()) {
			cache.find(key)->second->data = value;

			return true;
		}

		if (counter >= size) {
			auto tmp = cache.find(root->second->next_key);
			tmp->second->prev_key = NULL;
			cache.erase(root);
			root_key = key;

			counter = size;
		}

		node *new_node = new node(value);
		cache.insert({key, new_node});
		
		auto aux = cache.find(key);
		
		aux->second->prev_key = tail->first;
		tail->second->next_key = key;

		tail_key = key;

		counter ++;
		return true;
	}

	return false;
}

template <typename T, typename W>
bool LRUCache<T, W>::getMostRecentKey() {
	auto tail = cache.find(tail_key);
	std::cout << tail->first << std::endl;
	return true;
}

template <typename T, typename W>
bool LRUCache<T, W>::getValueFromKey (T key) {
	auto tail = cache.find(tail_key);
	auto found = cache.find(key);

	if (found == cache.end()) {
		std::cout << "not found" << std::endl;
		return false;		
	}

	std::cout << found->second->data << std::endl;

	auto aux_p = cache.find(found->second->prev_key);
	auto aux_n = cache.find(found->second->next_key);

	aux_p->second->next_key = aux_n->first;
	aux_n->second->prev_key = aux_p->first;

	tail->second->next_key = found->first;
	found->second->prev_key = tail->first;
	tail_key = key;

	return false;
}

