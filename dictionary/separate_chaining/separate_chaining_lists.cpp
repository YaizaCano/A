#include "separate_chaining_lists.h"


/* =================================
 *               PUBLIC
 *  =================================*/

SeparateChainingLists::SeparateChainingLists(int tableSize, HashFunction &hash) {

	m = tableSize;
	h = &hash;
	dictionary = std::vector<std::list<int> > (m);
	collisions = 0;
}

void SeparateChainingLists::insert(int value) {

	unsigned int i = hash(value);

	if (dictionary[i].size() > 0) ++collisions;

	dictionary[i].push_back(value);
}

bool SeparateChainingLists::find(int value) {

	unsigned int i = hash(value);

	for (std::list<int>::iterator it = dictionary[i].begin(); it != dictionary[i].end(); ++it)
		if (*it == value) {
			dictionary[i].erase(it);
			dictionary[i].push_front(value);
			return true;
		}

	return false;
}

unsigned int SeparateChainingLists::getCollisions() const {
	return collisions;
}


double SeparateChainingLists::getTheoricalValue(bool success, float loadFactor) const{
		return 0;
}

/* =================================
 *               PRIVATE
 *  =================================*/

unsigned int SeparateChainingLists::hash(int key) const {

	return h->operator()(key, m);
}
