#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional> 
#include <optional>

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
    size_t capacity;
    std::vector<std::list<std::pair<T, Q>>> table;

    // Hash function to calculate a hash for the key
    size_t _hash(const T& key) {
        std::hash<T> hasher;
        return hasher(key) % capacity;
    }
};

template<typename TKey, typename TValue>
class HashTableOA {
public:
    struct Entry {
        TKey key;
        TValue value;
        bool occupied = false;
        bool deleted = false;
    };

public:
    HashTableOA(size_t initialCapacity = 8)
        : capacity(initialCapacity), numElements(0), maxLoadFactor(static_cast<size_t>(0.7 * initialCapacity)) {
        array.resize(capacity);
    }

    void insert(const TKey& key, const TValue& value) {
        if (numElements >= maxLoadFactor) {
            rehash();
        }

        size_t index = hash(key);
        size_t probeIndex = 0;

        while (probeIndex < capacity) {
            auto& entry = array[(index + probeIndex * probingConstant) % capacity];

            if (!entry.occupied || entry.deleted) {
                entry = Entry{ key, value, true, false };
                ++numElements;
                return;
            }
            else if (entry.key == key) {
                entry.value = value;
                return;
            }

            probeIndex += 1;
        }

        std::cerr << "Insertion failed. Table is full after probing." << std::endl;
    }

    std::optional<TValue> search(const TKey& key) const {
        size_t index = hash(key);
        size_t probeIndex = 0;

        while (probeIndex < capacity) {
            const auto& entry = array[(index + probeIndex * probingConstant) % capacity];

            if (!entry.occupied) {
                return {}; // Equivalent to std::nullopt
            }
            else if (!entry.deleted && entry.key == key) {
                return entry.value;
            }

            probeIndex += 1;
        }

        return {}; // Key not found after full probing
    }

    void remove(const TKey& key) {
        size_t index = hash(key);
        size_t probeIndex = 0;

        while (probeIndex < capacity) {
            auto& entry = array[(index + probeIndex * probingConstant) % capacity];

            if (!entry.occupied) {
                return; // Element not found
            }
            else if (!entry.deleted && entry.key == key) {
                entry.deleted = true;
                --numElements;
                return;
            }

            probeIndex += 1;
        }
    }

private:
    size_t hash(const TKey& key) const {
        return std::hash<TKey>{}(key) % capacity;
    }

    void rehash() {
        auto oldArray = std::move(array);
        capacity = (capacity < 10000) ? capacity * 4 : capacity * 2;
        array = std::vector<std::optional<Entry>>(capacity);
        numElements = 0; // Reset count
        maxLoadFactor = static_cast<size_t>(0.7 * capacity);

        for (const auto& optEntry : oldArray) {
            if (optEntry.occupied && !optEntry.deleted) {
                insert(optEntry.key, optEntry.value);
            }
        }
    }

private:
    std::vector<std::optional<Entry>> array;
    size_t capacity;
    size_t numElements; // Number of elements currently in the table
    size_t maxLoadFactor;

    // Linear probing constant
    static constexpr size_t probingConstant = 1;
};