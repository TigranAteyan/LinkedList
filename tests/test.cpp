#ifndef LINKEDLIST_H
#define LINKEDLIST_H

<<<<<<< HEAD
#include <iostream>
#include <utility>
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

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
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
};

#endif
=======
TEST(LinkedListTest, InsertHead_ShouldIncreaseSizeTo1) {
    LinkedList<int> list;

    list.InsertHead(10);

    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Get(0), 10);
}

TEST(LinkedListTest, InsertTail_ShouldIncreaseSizeTo1) {
    LinkedList<int> list;
    list.InsertTail(20);
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(list.Get(0), 20);
}

TEST(LinkedListTest, InsertTail_ThreeElements_ShouldBeInCorrectOrder) {
    LinkedList<int> list;
    list.InsertTail(10);
    list.InsertTail(20);
    list.InsertTail(30);
    EXPECT_EQ(list.Size(), 3);
    EXPECT_EQ(list.Get(0), 10);
    EXPECT_EQ(list.Get(1), 20);
    EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, InsertAtMiddle_ShouldShiftElementsRight) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(3);
    list.Insert(1, 2); 

    EXPECT_EQ(list.Size(), 3);
    EXPECT_EQ(list.Get(0), 1);
    EXPECT_EQ(list.Get(1), 2);
    EXPECT_EQ(list.Get(2), 3);
}

TEST(LinkedListTest, Get_ShouldReturnCorrectValues) {
    LinkedList<int> list;
    list.InsertTail(5);
    list.InsertTail(6);

    EXPECT_EQ(list.Get(0), 5);
    EXPECT_EQ(list.Get(1), 6);
}

TEST(LinkedListTest, Get_InvalidIndex_ShouldThrow) {
    LinkedList<int> list;
    list.InsertTail(1);
    EXPECT_THROW(list.Get(5), IndexOutOfBounds);
}

TEST(LinkedListTest, RemoveMiddleElement_ShouldShiftRemaining) {
    LinkedList<int> list;
    list.InsertTail(100);
    list.InsertTail(200);
    list.InsertTail(300);

    list.Remove(1);

    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(list.Get(0), 100);
    EXPECT_EQ(list.Get(1), 300);
}

TEST(LinkedListTest, Remove_InvalidIndex_ShouldThrow) {
    LinkedList<int> list;
    list.InsertTail(1);
    EXPECT_THROW(list.Remove(3), IndexOutOfBounds);
}

TEST(LinkedListTest, CopyConstructor_ShouldCreateDeepCopy) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);

    LinkedList<int> copy(list);

    EXPECT_EQ(copy.Size(), 2);
    EXPECT_EQ(copy.Get(0), 1);
    EXPECT_EQ(copy.Get(1), 2);

    list.Remove(0); 
    EXPECT_EQ(copy.Get(0), 1); 
}

TEST(LinkedListTest, MoveConstructor_ShouldTransferOwnership) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);

    LinkedList<int> moved(std::move(list));

    EXPECT_EQ(moved.Size(), 2);
    EXPECT_EQ(moved.Get(0), 1);
    EXPECT_EQ(moved.Get(1), 2);
    EXPECT_EQ(list.Size(), 0);
}

TEST(LinkedListTest, CopyAssignment_ShouldCreateIndependentCopy) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);

    LinkedList<int> copy;
    copy = list;

    EXPECT_EQ(copy.Size(), 2);
    EXPECT_EQ(copy.Get(0), 1);
    EXPECT_EQ(copy.Get(1), 2);

    list.Remove(0);
    EXPECT_EQ(copy.Get(0), 1);
}

TEST(LinkedListTest, MoveAssignment_ShouldTransferOwnership) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);

    LinkedList<int> moved;
    moved = std::move(list);

    EXPECT_EQ(moved.Size(), 2);
    EXPECT_EQ(moved.Get(0), 1);
    EXPECT_EQ(moved.Get(1), 2);
    EXPECT_EQ(list.Size(), 0);
}
>>>>>>> 2016326 (Refactor: add ConstIterator and cbegin/cend for const support)
