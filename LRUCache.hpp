#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <utility>
#include <iostream>
#include <unordered_map>

template<typename T, typename W>	class LRUCache {
	public:
		struct node {
			W data;
			T next_key;
			T prev_key;

			node(W data) {
				this->data = data;
			}
		};
		
		int counter = 0;
	
		LRUCache(int size);
		bool insertKeyValuePair (T key, W value);
		bool getMostRecentKey ();
		bool getValueFromKey (T key);
	
	private:
		int size;
		std::unordered_map<T, node *> cache;
		T root_key;
		T tail_key;
	};

#endif /* LRU-CACHE_H */
