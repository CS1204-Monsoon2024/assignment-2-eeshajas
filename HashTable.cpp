#include <iostream>
#include <cmath>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int capacity;
    const float loadfactor = 0.8;
    int numofelements;
    const int DELETED = -2;  // Special marker for deleted elements

    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int primeAfterNum(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    int hashFunction(int key) {
        return key % capacity;
    }

    void resizeTable() {
        int prev_capacity = capacity;
        capacity = primeAfterNum(2 * prev_capacity);
        std::vector<int> prev_table = table;
        table = std::vector<int>(capacity, -1);
        numofelements = 0;

        for (int i = 0; i < prev_capacity; i++) {
            if (prev_table[i] != -1 && prev_table[i] != DELETED) {
                insert(prev_table[i]);
            }
        }
    }

public:
    HashTable(int size) {
        capacity = primeAfterNum(size);
        table = std::vector<int>(capacity, -1);
        numofelements = 0;
    }

    void insert(int key) {
        if (numofelements >= loadfactor * capacity) {
            resizeTable();
        }

        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int pindex = (index + i * i) % capacity;
            if (table[pindex] == -1 || table[pindex] == DELETED) {
                table[pindex] = key;
                numofelements++;
                return;
            } else if (table[pindex] == key) {
                std::cout << "Duplicate key insertion not allowed" << std::endl;
                return;
            }
            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl;
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int pindex = (index + i * i) % capacity;
            if (table[pindex] == key) {
                return pindex;  // Key found
            } else if (table[pindex] == -1) {
                return -1;  // Key not found
            }
            i++;
        }

        return -1;  // Key not found
    }

    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = DELETED;  // Mark as deleted
            numofelements--;
        }
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else if (table[i] == DELETED) {
                std::cout << "D ";  // Indicate deleted
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
