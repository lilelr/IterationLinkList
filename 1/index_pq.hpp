#ifndef INDEX_PRIORITY_QUEUE_HPP_
#define INDEX_PRIORITY_QUEUE_HPP_

#include <vector>
#include <algorithm>

template <typename T>
class IndexPriorityQueue {
 private:
  // vector to hold priorities.  
  // priorities.at(i) is the priority associated to index i
  // the heap will only contain indices, we look up priorities
  // in this vector as needed
  std::vector<T> priorities {};
  // priorityQueue stores indices: priorityQueue.at(i) is an index
  // priorityQueue functions as the heap and is heap ordered: 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i)) 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i) + 1) 
  std::vector<int> priorityQueue {};
  // indexToPosition.at(i) is the position in priorityQueue of index i
  // priorityQueue.at(indexToPosition.at(i)) = i
  // indexToPosition.at(priorityQueue.at(j)) = j
  std::vector<int> indexToPosition {};
  int size_ = 0;

 public:
  explicit IndexPriorityQueue(int);
  void push(const T&, int);
  void pop();
  void erase(int);
  bool contains(int) const;
  void changeKey(const T&, int);
  std::pair<T, int> top() const;
  bool empty() const;
  int size() const;

 private:
  // TODO: you may want to add your own member functions. swim? sink?

    void swap(int i, int j) {
        std::swap(priorityQueue[i], priorityQueue[j]);
        indexToPosition[priorityQueue[i]] = i;
        indexToPosition[priorityQueue[j]] = j;
    }

  void swim(int i) {
      while (i > 0 && priorities[priorityQueue[i]] < priorities[priorityQueue[i / 2]]) {
          swap(i, i / 2);
          i /= 2;
      }
  }

    void sink(int i) {
        while (2 * i <= size_) {
            int j = 2 * i;
            if (j < size_ && priorities[priorityQueue[j]] > priorities[priorityQueue[j + 1]]) {
                j++;  // choose the smaller one
            }
            if (priorities[priorityQueue[i]] <= priorities[priorityQueue[j]]) {
                break;
            }
            swap(i, j);
            i = j;
        }
    }
};

// Useful helper functions
int leftChild(int i) {
  return 2*i;
}

int rightChild(int i) {
  return 2*i + 1;
}

int parent(int i) {
  return i/2;
}

// IndexPriorityQueue member functions
template <typename T>
IndexPriorityQueue<T>::IndexPriorityQueue(int N) {
    for(int i=0;i<N;i++){
        this->priorities.push_back({});
        this->indexToPosition.push_back(-1);
    }
    this->size_=0;
//    this->priorities= {N,-1};
////    this->priorityQueue(N,-1);
//    this->indexToPositionN,-1);
}

template <typename T>
bool IndexPriorityQueue<T>::empty() const {
    if(this->size_<=0){
        return true;
    }
  return false;
}

template <typename T>
int IndexPriorityQueue<T>::size() const {
  return this->priorityQueue.size();
}

template <typename T>
void IndexPriorityQueue<T>::push(const T& priority, int index) {
    if(indexToPosition[index]==-1){ // the target index does not exist
        priorities[index] = priority;
        indexToPosition[index] = size_;
        priorityQueue.push_back(index);
        swim(size_);
        size_++;
    }
}

template <typename T>
void IndexPriorityQueue<T>::pop() {
    if (size_ <=0) {
        std::cerr << "Heap underflow!" << std::endl;

    }
    int minIndex = priorityQueue[0];
    swap(0, size_-1); // exchange the top one with the last one
    sink(0);
    indexToPosition[minIndex] = -1; // Mark as invalid
//    priorityQueue[minIndex] = -1; // Optional: Clear data
//    return minIndex;
    size_--;
}

template <typename T>
void IndexPriorityQueue<T>::erase(int index) {
    if(indexToPosition[index]!=-1){ // the target index  exists
        int target_position = indexToPosition[index];
        swap(target_position, size_--);
        sink(target_position);
        indexToPosition[index]=-1;
    }
}

template <typename T>
std::pair<T, int> IndexPriorityQueue<T>::top() const {
    int top_index = priorityQueue[0];
    T a(priorities[top_index]);

  return {a, top_index};
}

// if vertex i is not present, insert it with key
// otherwise change the associated key value of i to key
template <typename T>
void IndexPriorityQueue<T>::changeKey(const T& key, int index) {
    if(contains(index)){
        T oldPriority = priorities[index];
        priorities[index] = key;
        if (key < oldPriority) {// less than , go up
            swim(indexToPosition[index]);
        } else {
            sink(indexToPosition[index]);
        }
    }else{
        push(key, index);
    }
}

template <typename T>
bool IndexPriorityQueue<T>::contains(int index) const {
    if(indexToPosition[index]!=-1) { // the target index  exists
        return true;
    }
    return false;
}


#endif      // INDEX_PRIORITY_QUEUE_HPP_
