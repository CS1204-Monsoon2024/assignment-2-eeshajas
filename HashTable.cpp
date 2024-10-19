#include <iostream>
#include <cmath>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int capacity;
    float loadfactor = 0.8;
    int numofelements;
    int DELETED = -2;  

    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int primeafternum(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    int hashfunction(int key) {
        return key % capacity;
    }

    void resizetable() {
        int prev_capacity = capacity;
        capacity = primeafternum(2 * prev_capacity);
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
        capacity = primeafternum(size);
        table = std::vector<int>(capacity, -1);
        numofelements = 0;
    }

    void insert(int key) {
        if (numofelements >= loadfactor * capacity) {
            resizetable();
        }

        int index = hashfunction(key);
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
        int index = hashfunction(key);
        int i = 0;

        while (i < capacity) {
            int pindex = (index + i * i) % capacity;
            if (table[pindex] == key) {
                return pindex;
            } else if (table[pindex] == -1) {
                return -1;  
            }
            i++;
        }

        return -1;  
    }

    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found" << std::endl;
        } else {
            table[index] = DELETED;  
            numofelements--;
        }
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else if (table[i] == DELETED) {
                std::cout << "D ";  
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
