#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;

    
    int hash(int key) {
        return key % size;
    }

   
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= std::sqrt(n); ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    
    void resize() {
    int newSize = nextPrime(size * 2);
    std::vector<int> newTable(newSize, -1);
    int oldSize = size;
    size = newSize;
    count = 0; 

    for (int i = 0; i < oldSize; ++i) {
        if (table[i] != -1) {
            
            int key = table[i];
            int index = hash(key);
            int j = 0;

            while (j < size) {
                int newIndex = (index + j * j) % size;

                if (newTable[newIndex] == -1) {
                    newTable[newIndex] = key;
                    count++;
                    break; 
                }

                j++;
            }
        }
    }

    table.swap(newTable);
}

public:
    
    HashTable(int initialSize = 7) : size(nextPrime(initialSize)), count(0) {
        table.resize(size, -1);
    }

    
    void insert(int key) {
        
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        
        if (count >= size * 0.8) {
            resize();
        }

        int index = hash(key);
        int i = 0;

        
        while (i < size) {
            int newIndex = (index + i * i) % size;

            if (table[newIndex] == -1) { 
                table[newIndex] = key;
                count++;
                return;
            }

            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl; 
    }

   
    void remove(int key) {
        int index = hash(key);
        int i = 0;

        while (i < size) {
            int newIndex = (index + i * i) % size;

            if (table[newIndex] == -1) { 
                std::cout << "Element not found" << std::endl;
                return;
            } else if (table[newIndex] == key) { 
                table[newIndex] = -1; 
                count--;
                return;
            }

            i++;
        }

        std::cout << "Element not found" << std::endl; 
    }

    
    int search(int key) {
        int index = hash(key);
        int i = 0;

        while (i < size) {
            int newIndex = (index + i * i) % size;

            if (table[newIndex] == -1) { 
                return -1;
            } else if (table[newIndex] == key) { 
                return newIndex;
            }

            i++;
        }

        return -1; 
    }

    
    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl; 
    }
};
