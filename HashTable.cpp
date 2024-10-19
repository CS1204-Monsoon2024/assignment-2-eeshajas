#include <iostream>
#include <vector>
#include <list>

class HashTable {
public:
    HashTable(int size);
    void insert(int key);
    bool search(int key);
    void remove(int key);
    void display();

private:
    static const float loadfactor; // Constant load factor
    static const int DELETED;       // Special value for deleted entries
    int size;                       // Size of the hash table
    std::vector<std::list<int>> table; // Hash table using separate chaining
    int currentSize;               // Current number of elements

    int hashFunction(int key);
    void resize();
};

// Initialize static constants
const float HashTable::loadfactor = 0.75;
const int HashTable::DELETED = -1;

HashTable::HashTable(int size) : size(size), currentSize(0) {
    table.resize(size);
}

int HashTable::hashFunction(int key) {
    return key % size;
}

void HashTable::insert(int key) {
    if (currentSize >= size * loadfactor) {
        resize();
    }
    int index = hashFunction(key);
    table[index].push_back(key);
    currentSize++;
}

bool HashTable::search(int key) {
    int index = hashFunction(key);
    for (int item : table[index]) {
        if (item == key) {
            return true;
        }
    }
    return false;
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    table[index].remove(key);
    currentSize--;
}

void HashTable::display() {
    for (int i = 0; i < size; i++) {
        std::cout << i << ": ";
        for (int item : table[i]) {
            std::cout << item << " -> ";
        }
        std::cout << "nullptr" << std::endl;
    }
}

void HashTable::resize() {
    int newSize = size * 2;
    std::vector<std::list<int>> newTable(newSize);
    
    for (const auto& bucket : table) {
        for (int key : bucket) {
            int newIndex = key % newSize;
            newTable[newIndex].push_back(key);
        }
    }

    size = newSize;
    table = std::move(newTable);
    currentSize = 0; // Reset current size, will be recalculated during insert
}
