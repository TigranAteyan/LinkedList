#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
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

    LinkedList(const LinkedList& other)
    {
        Node* current = other.head;
        while (current)
        {
            this->InsertTail(current->data);
            current = current->next;
        }
    }

    LinkedList(LinkedList&& other) : head(other.head), tail(other.tail), size(other.size) 
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next; 
            delete current;
            current = next;
        }
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

    T Get(const int& position) const {
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
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = nullptr;
            size = 0;

            Node* current = other.head;
            while (current) {
                InsertTail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

};

#endif
