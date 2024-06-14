#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <functional>

// Hash Table with Separate Chaining using a Linked List secondary data structure
template<typename T, typename Q>
class HashTableSC 
{
public:
    using key_type = T;
    using value_type = Q;

public:
    HashTableSC(size_t _capacity = 8) : capacity(_capacity), table(capacity) {}

    void insert(const T& key, const Q& value) {
        size_t index = _hash(key);
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

    Q* search(const T& key) {
        // return nullptr when not found
        size_t index = _hash(key);
        for (auto& item : table[index]) {
            if (item.first == key) {
                return &item.second;
            }
        }
        return nullptr;
    }

    bool remove(const T& key) {
        size_t index = _hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        
        return false;
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
    size_t capacity; // a fixed number of capacity
    std::vector<std::list<std::pair<T, Q>>> table;

    // Hash function to calculate a hash for the key
    size_t _hash(const T& key) {
        std::hash<T> hasher;
        return hasher(key) % capacity;
    }
};