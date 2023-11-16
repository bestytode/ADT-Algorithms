#pragma once

#include <optional>
#include <functional>
#include <vector>
#include <iostream>

template<typename TKey, typename TValue>
class HashTableOA
{
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

        // if probe_index is larger than the capacity, insertion fail
        while (probeIndex < capacity) {
            auto& entry = this->array[(index + probeIndex * probingConstant) % capacity];

            // if this entry block is not occupied or has been deleted for new insertion
            if (!entry->occupied || entry->deleted) {
                entry = Entry{ key, value, true, false }; // create a new block entry with occupied = true, delete = false
                ++numElements;
                return;
            }
            // update value if already has key
            else if (entry->key == key) {
                entry->value = value;
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

            if (!entry->occupied) {
                return std::nullopt; // this block has not been inserted, no search result will be found
            }
            else if (!entry->deleted && entry->key == key) {
                return entry->value;
            }

            probeIndex += 1;
        }

        return std::nullopt; // Key not found after full probing
    }

    void remove(const TKey& key) {
        size_t index = hash(key);
        size_t probeIndex = 0;

        while (probeIndex < capacity) {
            auto& entry = array[(index + probeIndex * probingConstant) % capacity];

            if (entry->occupied) {
                return; // Element not found
            }
            else if (!entry->deleted && entry->key == key) {
                entry->deleted = true; // we simply mark this Entry block as deleted 
                --numElements;
                return;
            }

            probeIndex += 1;
        }
    }

    void print() const
    {
        for (const std::optional<Entry>& entry_block : this->array) {
            if (entry_block)
                std::cout << "key: " << entry_block->key << " | value:" << entry_block->value << "\n";
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
            if (optEntry->occupied && !optEntry->deleted) {
                insert(optEntry->key, optEntry->value);
            }
        }
    }

private:
    // std::optional simplifies tracking of entries' states, optimizing memory and collision logic.
    std::vector<std::optional<Entry>> array;

    // tracking variables
    size_t capacity;
    size_t numElements; // current element number
    size_t maxLoadFactor;

    // Linear probing constant
    static constexpr size_t probingConstant = 1;
};