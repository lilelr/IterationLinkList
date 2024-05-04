//
// Created by lilele on 2024/5/4.
//
#include <iostream>
#include <vector>
#include <algorithm>

class IndexedPriorityQueueMin {
public:
    // Constructor initializing vectors
    IndexedPriorityQueueMin(size_t size) : data(size + 1, INT_MAX), indices(size + 1, 0), heapSize(0) {}

    // Function to change the priority of an element and heapify
    void changePriority(int index, int newPriority) {
        if (index < 1 || index > static_cast<int>(data.size()) - 1) {
            std::cerr << "Index out of range!" << std::endl;
            return;
        }
        int oldPriority = data[index];
        data[index] = newPriority;
        if (newPriority < oldPriority) {
            swim(indices[index]);
        } else {
            sink(indices[index]);
        }
    }

    // Function to insert a new element (assuming index starts from 1)
    void insert(int index, int priority) {
        if (index < 1 || index > static_cast<int>(data.size()) - 1) {
            std::cerr << "Index out of range!" << std::endl;
            return;
        }
        data[index] = priority;
        indices[index] = ++heapSize;
        heap[heapSize] = index;
        swim(heapSize);
    }

    // Function to extract the minimum priority element
    int extractMin() {
        if (heapSize < 1) {
            std::cerr << "Heap underflow!" << std::endl;
            return -1; // Or throw an exception
        }
        int minIndex = heap[1];
        swap(1, heapSize--);
        sink(1);
        indices[minIndex] = 0; // Mark as invalid
        data[minIndex] = INT_MAX; // Optional: Clear data
        return minIndex;
    }

private:
    std::vector<int> data; // Store priorities (now using INT_MAX as default/max value)
    std::vector<int> indices; // Map from index to its position in the heap
    std::vector<int> heap; // Actual heap storage
    int heapSize;

    void swim(int i) {
        while (i > 1 && data[heap[i]] < data[heap[i / 2]]) {
            swap(i, i / 2);
            i /= 2;
        }
    }

    void sink(int i) {
        while (2 * i <= heapSize) {
            int j = 2 * i;
            if (j < heapSize && data[heap[j]] > data[heap[j + 1]]) {
                j++;
            }
            if (data[heap[i]] <= data[heap[j]]) {
                break;
            }
            swap(i, j);
            i = j;
        }
    }

    void swap(int i, int j) {
        std::swap(heap[i], heap[j]);
        indices[heap[i]] = i;
        indices[heap[j]] = j;
    }
};

int main() {
    IndexedPriorityQueueMin ipq(5);
    ipq.insert(1, 5);
    ipq.insert(2, 3);
    ipq.insert(3, 8);
    ipq.changePriority(1, 1); // Change priority of index 1 to make it the new min
    std::cout << "Min priority index extracted: " << ipq.extractMin() << std::endl;
    return 0;
}