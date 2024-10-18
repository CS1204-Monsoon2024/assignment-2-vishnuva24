#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int capacity;
    int size;
    double loadFactor;

    int hash(int key) {
        return key % capacity;
    }

    int nextPrime(int n) {
        while (true) {
            bool isPrime = true;
            for (int i = 2; i*i <= n; i++) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return n;
            n++;
        }
    }

    void recapacity() {
        int newcapacity = nextPrime(capacity * 2);
        vector<int> newTable(newcapacity, -1);
        
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1) {
                int key = table[i];
                int index = key % newcapacity;
                int j = 0;
                while (newTable[(index + j * j) % newcapacity] != -1) {
                    j++;
                }
                newTable[(index + j * j) % newcapacity] = key;
            }
        }
        table = newTable;
        capacity = newcapacity;
    }

public:
    HashTable(int initcapacity = 5) {
        capacity = nextPrime(initcapacity);
        table = vector<int>(capacity, -1);
        size = 0;
        loadFactor = 0.8;
    }

    void insert(int key) {
        if (size >= loadFactor * capacity) {
            recapacity();
        }
        int index = hash(key);
        int j = 0;

        while (j <= capacity/2 + 1) {
            int index2 = (index + (j * j)) % capacity;
            if (table[index2] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            if (table[index2] == -1) {
                table[index2] = key;
                size++;
                return;
            }
            j++;
        }
        cout << "Max probing limit reached!" << endl;
    }

    void remove(int key) {
        int index = hash(key);
        int j = 0;

        while (j <= capacity/2 + 1) {
            int index2 = (index + (j * j)) % capacity;
            if (table[index2] == key) {
                table[index2] = -1;
                size--;
                return;
            }
            j++;
        }
        cout << "Element not found"<< endl;
    }

    int search(int key) {
        int index = hash(key);
        int j = 0;

        while (j <= capacity/2 + 1) {
            int index2 = (index + (j * j)) % capacity;
            if (table[index2] == key) {
                return index2;
            } 
            j++;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};