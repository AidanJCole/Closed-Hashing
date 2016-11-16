#include "stdafx.h"
#include "HashTable.h"
#include "Record.h"
// Made by Aidan Cole
#include <cmath>
#include <vector>

//template <typename T> Record<T> hashTable [MAXHASH];
template class HashTable<int>;
static vector<int> relativePrimes;
static bool constructed = false;

// Constructs the static list of numbers coprime to MAXHASH the first time a hash table is constructed
template <class T>HashTable<T>::HashTable()
{
	if (!constructed) {
		for (int i = 2; i < MAXHASH * 2; i++) {
			if (gcd(i, MAXHASH) == 1) {
				relativePrimes.push_back(i);
			}
		}
		int i = 0;
		constructed = true;
	}
}

// Helps find coprime numbers
template <class T> int HashTable<T>::gcd(int a, int b) {
	
		int c;
		while (a != 0) {
			c = a; a = b%a;  b = c;
		}
		return b;
	
}

template <class T>
HashTable<T>::~HashTable()
{
	//delete relativePrimes;
}

// Inserts a value into the hash table
template <class T>
bool HashTable<T>::insert(int key, T value, int& collisions) {
	if (load == MAXHASH) {
		return false;
	}
	int home = hash(key);
	bool found = false;
	Record<T> temp = Record<T>(key, value);
	int i = 0;
	while (!found) {
		int homePrime = abs((home + probe(key, i))) % MAXHASH;
		if (hashTable[homePrime].isEmpty() || hashTable[homePrime].isTombstone()) {
			hashTable[homePrime] = temp;
			collisions = i + 1;
			load++;
			return true;
		}
		if (hashTable[homePrime].isNormal() && hashTable[homePrime].getKey() == key) {
			return false;
		}
		if (homePrime == home && i != 0) {
			return false;
		}
		i++;
		
	}
	return false;
}

// Removes a value
template <class T>
bool HashTable<T>::remove(int key) {
	Record<T>* temp;
	bool truth = secretFind(key, temp);
	if (truth) {
		temp->kill();
		load--;
	}
	return truth;
}

// finds a value
template <class T>
bool HashTable<T>::find(int key, T& value) {
	Record<T>* temp;
	bool truth = secretFind(key, temp);
	if (truth) {
		value = temp->getValue();
	}
	return truth;
}

// A helper function that was used both for finding records and deleting records
template <class T> bool HashTable<T>::secretFind(int key, Record<T>*& node) {
	bool found = false;
	int home = hash(key);
	int i = 0;
	while (!found) {
		int homePrime = (home + probe(key, i)) % MAXHASH;
		if (hashTable[homePrime].isNormal() && hashTable[homePrime].getKey() == key) {
			node = &hashTable[homePrime];
			return true;
		}
		if (hashTable[homePrime].isTombstone() && hashTable[homePrime].getKey() == key || hashTable[homePrime].isEmpty()) {
			return false;
		}
		
		if (homePrime == home && i != 0) {
			return false;
		}
		i++;
	}
}

// Returns load factor of the Hash Table
template <class T>
float HashTable<T>::alpha() {
	return 1.0f * load / MAXHASH;
}

// First hash of the hash table.
// Didn't spend too much time on it, just mashed a couple of ideas together from different hashes i've seen.
template <class T> int HashTable<T>::hash(int key) {
	int temp = (key >> 1) ^ 0xF70C8BA0;
	temp = key * key + temp * temp;
	temp = (key >> 2) ^ 0x6B4F13E7;
	temp = abs(key * temp);
	return temp % MAXHASH;
}

// Same as the first hash, except changed the constants that give the primary hash value
// Also, uses the primary hash value to look up a number coprime to MAXHASH, which will guarentee that
// probing will visit every slot
template <class T> int HashTable<T>::hash2(int key) {
	int temp = (key >> 1) ^ 0xF70C8BA0;
	temp = key * key + temp * temp;
	temp = (key >> 2) ^ 0xB854CE40;
	temp = abs((key * temp));
	return relativePrimes[temp % relativePrimes.size()];
}

// Probe function to find next value to check.
template <class T> int HashTable<T>::probe(int key, int i) {
	return i*hash2(key);
}

