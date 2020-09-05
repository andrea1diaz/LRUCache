#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <utility>
#include <iostream>

	class LRUCache {
	private:
		int size;	

	public:
		struct node {
			std::pair <char, int> data;
			node *next_node;
		};
	
		node *root;
		node *tail;
		int counter = 0;
	
		LRUCache(int size);
		bool insertKeyValuePair (char key, int value);
		void getMostRecentKey ();
		bool getValueFromKey (char key);

	};

#endif /* LRU-CACHE_H */
