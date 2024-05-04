
#ifndef MY_LIST_HPP_
#define MY_LIST_HPP_

#include <initializer_list>

template <typename T>
class MyList {
public:
    struct Node {
        T data{};
        Node* prev{ nullptr };
        Node* next{ nullptr };
        Node(T input_data = T{}, Node* prevNode = nullptr, Node* nextNode = nullptr)
            : data{ input_data }, prev{ prevNode }, next{ nextNode } {}
    };

    class Iterator {
    private:


    public:
        Node* current_;
        Iterator(Node* node) : current_(node) {}

        Iterator& operator++() {
            current_ = current_->next;
            return *this;
        }

        Iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }

        T& operator*() const {
            return current_->data;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.current_ == b.current_;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return !(a == b);
        }
    };

private:
    Node* head;
    Node* tail;
    Node* endnode;

    int size_;

public:
    MyList();
    MyList(std::initializer_list<T> vals);
    MyList(const MyList& other);
    MyList& operator=(MyList other);
    ~MyList();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void push_front(const T& value);
    void pop_front();
    void push_back(const T& value);
    void pop_back();

    void insert(const Iterator& position, const T& value);
    void erase(const Iterator& position);

    bool empty() const;
    int size() const;

    Iterator begin();
    Iterator end();

private:
    void initialize();
    void clear();
};

template <typename T>
MyList<T>::MyList() {
    initialize();
}

template <typename T>
MyList<T>::MyList(std::initializer_list<T> vals) {
    initialize();
    for (const auto& val : vals) {
        push_back(val);
    }

}

template <typename T>
MyList<T>::MyList(const MyList& other) {
    initialize();
    for (auto current = other.head; current != nullptr; current = current->next) {
        push_back(current->data);
    }
}

template <typename T>
MyList<T>& MyList<T>::operator=(MyList other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size_, other.size_);
    return *this;
}

template <typename T>
MyList<T>::~MyList() {
    clear();
}

template <typename T>
T& MyList<T>::front() {
    return head->data;
}

template <typename T>
const T& MyList<T>::front() const {
    return head->data;
}

template <typename T>
T& MyList<T>::back() {
    return tail->data;
}

template <typename T>
const T& MyList<T>::back() const {
    return tail->data;
}

template <typename T>
void MyList<T>::push_front(const T& value) {
    Node* newNode = new Node(value, nullptr, head);
    if (head != nullptr) {
        head->prev = newNode;
    }
    else {
        tail = newNode; // if the list was empty, set tail to newNode
    }
    head = newNode;
    size_++;
}

template <typename T>
void MyList<T>::pop_front() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr; // if the list is now empty, set tail to nullptr
        }
        delete temp;
        size_--;
    }
}

template <typename T>
void MyList<T>::push_back(const T& value) {
    Node* newNode = new Node(value, tail, nullptr);
    if (tail != nullptr) {
        tail->next = newNode;
    }
    else {
        head = newNode; // if the list was empty, set head to newNode
    }

    tail = newNode;
    tail->next = endnode;
    size_++;
}

template <typename T>
void MyList<T>::pop_back() {
    if (tail != nullptr) {
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr; // if the list is now empty, set head to nullptr
        }

        delete temp;
        size_--;
    }
}

template <typename T>
bool MyList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
int MyList<T>::size() const {
    return size_;
}

template <typename T>
void MyList<T>::initialize() {
    head = nullptr;
    tail = nullptr;
    endnode = new Node;
    size_ = 0;
}

template <typename T>
void MyList<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size_ = 0;
}



template <typename T>
void MyList<T>::insert(const Iterator& position, const T& value) {
    //if (position.current_ ->next== nullptr) {
    //    push_back(value);
    //    return;
    //}
    //if (position.current_->prev == nullptr) {
        //push_front(value);
        //return;
   // }

    if (position.current_ == endnode) {
        Node *newNode = new Node(value, position.current_->prev, position.current_);
        position.current_->prev = newNode;
        tail = position.current_->prev;
   
    }
    else if (position.current_ == head) {
        Node *newNode = new Node(value, position.current_->prev, position.current_);
        head->prev = newNode;
        head = newNode;

    }
    else if (position.current_ != head) {
        Node *newNode = new Node(value, position.current_->prev, position.current_);
        position.current_->prev->next = newNode;
        //position.current_->next->prev = newNode;
        position.current_->prev = newNode;

    }

    /* if (position.current_->prev != nullptr) {
         position.current_->prev->next = newNode;
     }
     else {
         head = newNode;
     }*/
     //position.current_->prev = newNode;
     //endnode->prev = tail;

    size_++;
}

template <typename T>
void MyList<T>::erase(const Iterator& position) {
    if (position.current_ == nullptr) {
        return;
    }
    if (position.current_ == tail) {
        position.current_->prev->next = position.current_->next;
        position.current_->next->prev = position.current_->prev;
        tail = position.current_->prev;

    }
    else if (position.current_ == head) {
        position.current_->next->prev = position.current_->prev;
        head = position.current_->next;
    }
    else if (position.current_ != head) {
        position.current_->prev->next = position.current_->next;
        position.current_->next->prev = position.current_->prev;
    }

    delete position.current_;
    size_--;
}

template <typename T>
typename MyList<T>::Iterator MyList<T>::begin() {
    return Iterator(head);
}

template <typename T>
typename MyList<T>::Iterator MyList<T>::end() {

    tail->next = endnode;
    endnode->prev = tail;
    endnode->next = nullptr;
    return Iterator(endnode);
}



#endif // MY_LIST_HPP_





