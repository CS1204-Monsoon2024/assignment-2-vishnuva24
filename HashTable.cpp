#include <vector>
#include <cmath>
#include <iostream>

class HashTable {
private:
    std::vector<int> table;
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
        std::vector<int> newTable(newcapacity, -1);
        
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1 && table[i] != -2) {
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
        table = std::vector<int>(capacity, -1);
        size = 0;
        loadFactor = 0.8;
    }

    void insert(int key) {
        if (size >= loadFactor * capacity) {
            recapacity();
        }
        int index = hash(key);
        int j = 0;

        while (j < capacity) {
            int index2 = (index + (j * j)) % capacity;
            if (table[index2] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
            if (table[index2] == -1 || table[index2] == -2) {
                table[index2] = key;
                size++;
                return;
            }
            j++;
        }
        std::cout << "Max probing limit reached!\n";
    }

    void remove(int key) {
        int index = hash(key);
        int j = 0;

        while (j < capacity) {
            int index2 = (index + (j * j)) % capacity;
            if (table[index2] == key) {
                table[index2] = -2;
                size--;
                return;
            } else if (table[index2] == -1) {
                std::cout << "Element not found\n";
                return;
            }
            j++;
        }
        std::cout << "Element not found\n";
    }

    int search(int key) {
        int index = hash(key);
        int j = 0;

        while (j < capacity) {
            int index2 = (index + (j * j)) % capacity;
            if (table[index2] == key) {
                return index2;
            } else if (table[index2] == -1) {
                return -1;
            }
            j++;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1 || table[i] == -2) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << "\n";
    }
};