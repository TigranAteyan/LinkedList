#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <utility>
#include <functional>
#include "IndexOutOfBounds.hpp"

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const LinkedList& other) : LinkedList() {
        LinkedList temp; 
        Node* current = other.head;
        while (current) {
            temp.InsertTail(current->data);
            current = current->next;
        }
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(size, temp.size);
    }

    LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    ~LinkedList() {
        Clear();
    }

    void Clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    void InsertHead(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size;
    }

    void InsertTail(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void Insert(const int& position, const T& value) {
        if (position < 0 || position > size) {
            throw IndexOutOfBounds();
        }
        if (position == 0) {
            InsertHead(value);
        } else if (position == size) {
            InsertTail(value);
        } else {
            Node* newNode = new Node(value);
            Node* current = head;
            for (int i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            ++size;
        }
    }

    T& Get(const int& position) const {
        if (position < 0 || position >= size) {
            throw IndexOutOfBounds();
        }
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void Remove(const int& position) {
        if (position < 0 || position >= size) {
            throw IndexOutOfBounds();
        }
        Node* toRemove = nullptr;
        if (position == 0) {
            toRemove = head;
            head = head->next;
            if (!head) tail = nullptr;
        } else {
            Node* current = head;
            for (int i = 0; i < position - 1; ++i) {
                current = current->next;
            }
            toRemove = current->next;
            current->next = toRemove->next;
            if (toRemove == tail) {
                tail = current;
            }
        }
        delete toRemove;
        --size;
    }

    int Size() const {
        return size;
    }

    void PrintAll() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            LinkedList temp(other);           
            std::swap(head, temp.head);       
            std::swap(tail, temp.tail);
            std::swap(size, temp.size);
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            Clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void ForEach(std::function<void(T&)> func) 
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            func(*it);
        }
    }

    class Iterator {
    private:
        Node* it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* ptr) : it(ptr) {}
        Iterator() : it(nullptr) {}

        Iterator& operator++() 
        {
            if (!it) throw std::out_of_range("going beyond the boundaries");
            it = it->next;
            return *this;
        }

        Iterator operator++(int) 
        {
            Iterator temp = *this;
            if (!it) throw std::out_of_range("going beyond the boundaries");
            it = it->next;
            return temp;
        }

        bool operator!=(const Iterator& other) const { return it != other.it; }
        bool operator==(const Iterator& other) const { return it == other.it; }

        T& operator*() 
        { 
            if (!it) throw std::out_of_range("dereferencing end()");
            return it->data; 
        }
    };

    class ConstIterator {
        const Node* it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const Node* ptr) : it(ptr) {}
        ConstIterator() : it(nullptr) {}

        ConstIterator& operator++() 
        {
            if (!it) throw std::out_of_range("going beyond the boundaries");
            it = it->next;
            return *this;
        }

        Iterator operator++(int) 
        {
            Iterator temp = *this;
            if (!it) throw std::out_of_range("going beyond the boundaries");
            it = it->next;
            return temp;
        }

        const T& operator*() const 
        {
            if (!it) throw std::out_of_range("dereferencing end()");
            return it->data; 
        }

        bool operator!=(const ConstIterator& other) const { return it != other.it; }
        bool operator==(const ConstIterator& other) const { return it == other.it; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }

    ConstIterator cbegin() const { return ConstIterator(head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }

    Iterator find(const T& value) {
        for (Iterator it = begin(); it != end(); ++it) {
            if (*it == value) return it;
        }
        return end();
    }

};

#endif
