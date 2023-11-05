#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional> // For std::hash<T>

// Hash Table with Separate Chaining using a Linked List secondary data structure
template<typename T, typename Q>
class HashTableSC 
{
public:
    HashTableSC(size_t cap = 8) : capacity(cap), table(cap) {}

    void insert(const T& key, const Q& value) {
        size_t index = hashFunction(key);
        // Search for the key in the list at the index
        for (auto& item : table[index]) {
            // If key found, update the value and return
            if (item.first == key) {
                item.second = value;
                return;
            }
        }
        // If not found, insert the new key-value pair
        table[index].emplace_back(key, value);
    }

    Q search(const T& key) {
        size_t index = hashFunction(key);
        for (const auto& item : table[index]) {
            if (item.first == key) {
                return item.second;
            }
        }
        throw std::invalid_argument("Key not found");
    }

    void remove(const T& key) {
        size_t index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return;
            }
        }
        throw std::invalid_argument("Key not found");
    }

    void print() {
        for (const auto& list : table) {
            for (const auto& item : list) {
                std::cout << "{" << item.first << ": " << item.second << "} ";
            }
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::list<std::pair<T, Q>>> table;
    size_t capacity;

    // Hash function to calculate a hash for the key
    size_t hashFunction(const T& key) {
        std::hash<T> hasher;
        return hasher(key) % capacity;
    }
};