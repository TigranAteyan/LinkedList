#include "LinkedList.hpp"
#include <gtest/gtest.h>

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
