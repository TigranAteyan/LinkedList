#include "LinkedList.hpp"
#include <gtest/gtest.h>

TEST(LinkedListTest, InsertHeadOneElement) {
    LinkedList<int> list;
    list.InsertHead(10);
    EXPECT_EQ(list.Size(), 1);
}

TEST(LinkedListTest, InsertTailOneElement) {
    LinkedList<int> list;
    list.InsertTail(20);
    EXPECT_EQ(list.Size(), 1);
}

TEST(LinkedListTest, InsertTailMultiple) {
    LinkedList<int> list;
    list.InsertTail(10);
    list.InsertTail(20);
    list.InsertTail(30);
    EXPECT_EQ(list.Size(), 3);
}

TEST(LinkedListTest, InsertAtPosition) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(3);
    list.Insert(1, 2); 
    EXPECT_EQ(list.Get(1), 2);
}

TEST(LinkedListTest, GetCorrectValue) {
    LinkedList<int> list;
    list.InsertTail(5);
    list.InsertTail(6);
    EXPECT_EQ(list.Get(0), 5);
    EXPECT_EQ(list.Get(1), 6);
}

TEST(LinkedListTest, RemoveElement) {
    LinkedList<int> list;
    list.InsertTail(100);
    list.InsertTail(200);
    list.InsertTail(300);
    list.Remove(1);  
    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(list.Get(0), 100);
    EXPECT_EQ(list.Get(1), 300);
}

TEST(LinkedListTest, OutOfRangeGet) {
    LinkedList<int> list;
    list.InsertTail(1);
    EXPECT_THROW(list.Get(5), IndexOutOfBounds);
}

TEST(LinkedListTest, OutOfRangeRemove) {
    LinkedList<int> list;
    list.InsertTail(1);
    EXPECT_THROW(list.Remove(3), IndexOutOfBounds);
}

TEST(LinkedListTest, CopyConstructorCreatesDeepCopy) {
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

TEST(LinkedListTest, MoveConstructorTransfersOwnership) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);

    LinkedList<int> moved(std::move(list));
    EXPECT_EQ(moved.Size(), 2);
    EXPECT_EQ(moved.Get(0), 1);
    EXPECT_EQ(moved.Get(1), 2);
    EXPECT_EQ(list.Size(), 0);  
}

TEST(LinkedListTest, CopyAssignmentWorksCorrectly) {
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

TEST(LinkedListTest, MoveAssignmentTransfersOwnership) {
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
