#pragma once

#include <vector>
#include <stdexcept>
#include <functional>

template<typename T, typename Comparator = std::less<T>>
class BinaryHeap
{
public:
	BinaryHeap(){}
    ~BinaryHeap() = default;

	// Add key to the heap and then heapify up
	void insert(T key) {
		heap.push_back(key);
		heapify_up(heap.size() - 1);
		NrElements++;
	}

	// Remove the root element and then heapify down
	T extract() {
		if (heap.empty()) 
			throw std::runtime_error("Heap is empty");

		T root_value = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		heapify_down(0);

		NrElements--;
		return root_value;
	}

	size_t size() const {
		return NrElements;
	}
private:
	// Maintain heap property by moving the node up
	void heapify_up(int index) {
		while (index != 0 && comp(heap[parent(index)], heap[index])) {
			std::swap(heap[index], heap[parent(index)]);
			index = parent(index);
		}
	}

	// Maintain heap property by moving the node down
	void heapify_down(int index) {
		int size = heap.size();
		int left = leftChild(index);
		int right = rightChild(index);

		int extreme = index; // Use 'extreme' to generalize for min-heap or max-heap

		if (left < size && comp(heap[extreme], heap[left])) {
			extreme = left;
		}

		if (right < size && comp(heap[extreme], heap[right])) {
			extreme = right;
		}

		if (extreme != index) {
			std::swap(heap[index], heap[extreme]);
			heapify_down(extreme);
		}
	}

	int parent(int index) {
		if (index == 0) 
			throw std::out_of_range("Root element has no parent.");
		return (index - 1) / 2;
	}

	int leftChild(int index) {
		return (2 * index) + 1;
	}

	int rightChild(int index) {
		return (2 * index) + 2;
	}

private:
	size_t NrElements;
	std::vector<T> heap;
	Comparator comp;
};

template<typename T>
void heap_sort(std::vector<T>& array)
{
	BinaryHeap<T> heap;
	for (const auto& value : array) {
		heap.insert(value);
	}
	for (int i = array.size() - 1; i >= 0; i--) {
		arr[i] = heap.extract();
	}
}

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue
{
public:
	PriorityQueue(){}
	
	void push(T value) {
		heap.insert(value);
	}

	T pop() {
		if (heap.empty())
			throw std::runtime_error("Priority queue is empty");

		heap.extract();
	}

	bool empty() const{
		return heap.size() == 0;
	}

private:
	BinaryHeap<T, Comparator> heap;
};