#include <iostream>
#include "LRUCache.cpp"

int main () {
	LRUCache<char, int> a = LRUCache<char, int>(3);

	a.insertKeyValuePair ('b', 2);
	a.insertKeyValuePair ('a', 1);
	a.insertKeyValuePair ('c', 3);

	a.getMostRecentKey();

	a.getValueFromKey('a');
	a.getMostRecentKey();

	a.insertKeyValuePair('d', 4);
	a.getValueFromKey('b');

	a.insertKeyValuePair('a', 5);
	a.getValueFromKey('a');
	return 0;
}
