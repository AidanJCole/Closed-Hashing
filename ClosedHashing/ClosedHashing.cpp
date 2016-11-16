
// Made by Aidan Cole
#include "stdafx.h"
#include "HashTable.h"
#include <vector>
// Number of iterations to find an average value
int iterations = 1000;
// Holds nonrepeating keys, as using rand() tended to want to insert duplicate values
vector<int> keys;
// Number of slots to record the average insertions for. A value of 9 will record from 100 - 900, with an interval of 100.
// Reccomended values include 9, 49, 499, and 999.
const int buckets = 9;

static void swap(int i, int j, vector<int>& keys) {
	int temp = keys[i];
	keys[i] = keys[j];
	keys[j] = temp;
}

static void scramble(vector<int>& keys) {
	for (int i = 0; i <  keys.size(); i++) {
		swap(i, rand()%keys.size(), keys);
	}
}

int main()
{
	srand((int)time(NULL));
	
	// Populates keys
	for (int i = 0; i < 3*MAXHASH; i++) {
		keys.push_back(i);
	}
	// Keeps track of the number of collisions at each insertion level
	int collisionTotal[buckets] = {};
	
	for (int i = 0; i < iterations; i++) {
		HashTable<int> hasher;
		bool insertable;
		int collisions;
		//cout << "Inner: " << i << endl;
		scramble(keys);
		for (int j = 0; j < MAXHASH; j++) {
			hasher.insert(keys[j], j, collisions);
			if (j % (MAXHASH / (buckets + 1)) == 0&&j!=0&&j!=MAXHASH) {
				collisionTotal[(j - (MAXHASH / (buckets + 1))) / (MAXHASH / (buckets + 1))] += collisions;
			}
		}
	}
	float avError = 0;
	for (int i = 0; i < buckets; i++) {
		int insertions = (i + 1) * (MAXHASH / (buckets + 1));
		float numerator = (float)(MAXHASH+1)*(MAXHASH - insertions);
		float denominator = (insertions - (float)(MAXHASH+1))*(insertions - MAXHASH);
		float floor = numerator / denominator;
		float delta = (collisionTotal[i] * 1.0f / iterations) - floor;
		cout << "Optimal at " << insertions << ": " << floor << endl;
		cout << "Actual insertions: " << collisionTotal[i] * 1.0f / iterations <<endl;
		cout << "Provided optimal: " << 1 / (1 - (1.0f*insertions / MAXHASH)) << endl;
		cout << "Difference: " << delta << endl;
		avError += delta;
	}
	cout << "Average difference: " << avError / buckets << endl;
	/*
	HashTable<int> hasher;
	int collision;
	scramble(keys);
	for (int i = 0; i < MAXHASH / 2; i++) {
		hasher.insert(keys[i], i, collision);
	}
	cout << hasher << endl << hasher.alpha() << endl;
	for (int i = 0; i < MAXHASH / 4; i++) {
		hasher.remove(keys[i]);
	}
	cout << hasher << endl << hasher.alpha() << endl;
	for (int i = MAXHASH / 2; i < MAXHASH / 2 + MAXHASH / 4; i++) {
		hasher.insert(keys[i], i, collision);
	}
	cout << hasher << endl << hasher.alpha() << endl;
	int dupCounter = 0;
	for (int i = 0; i < 100; i++) {
		HashTable<int> temp;
		for (int i = 0; i < MAXHASH; i++) {
			if (!temp.insert(rand() % MAXHASH, i, collision)) {
				dupCounter++;
			}
		}
	}
	cout << "There were " << dupCounter << " duplicates over " << 100 * MAXHASH << " insertions over 100 hashtables." << endl;
	*/
	cin.ignore();
    return 0;
}



