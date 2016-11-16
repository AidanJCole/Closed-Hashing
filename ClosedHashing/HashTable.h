// Made by Aidan Cole

#pragma once
#include "Record.h"
#include <iostream>
#include <vector>
#define MAXHASH 1000

template <class T> class HashTable
{
public:
	HashTable();
	~HashTable();
	bool HashTable<T>::insert(int key, T value, int& collisions);
	bool HashTable<T>::remove(int key);
	bool HashTable<T>::find(int key, T& value);
	float HashTable<T>::alpha();
private:
	Record<T> hashTable [MAXHASH];
	int load = 0;
	int HashTable<T>::gcd(int a, int b);
	int HashTable<T>::probe(int key, int i);
	int HashTable<T>::hash2(int key);
	int HashTable<T>::hash(int key);
	bool HashTable<T>::secretFind(int key, Record<T>*& node);
	friend ostream& operator<<(ostream& os, const HashTable<T>& me) {
		for (int i = 0; i < MAXHASH; i++) {
			if (me.hashTable[i].isNormal()) {
				cout << me.hashTable[i].getKey() << ", " << me.hashTable[i].getValue() << ", " << i << endl;
			}
		}
		return os;
	}
};
