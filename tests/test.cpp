#include "LinkedList.hpp"
#include <gtest/gtest.h>
#include <algorithm>

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

TEST(LinkedListIteratorTest, EmptyListBeginEqualsEnd) {
    LinkedList<int> list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(LinkedListIteratorTest, IterateOverElements) {
    LinkedList<int> list;
    list.InsertTail(10);
    list.InsertTail(20);
    list.InsertTail(30);

    int expected[] = {10, 20, 30};
    int idx = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[idx++]);
    }
    EXPECT_EQ(idx, list.Size());
}

TEST(LinkedListIteratorTest, IteratorPostfixIncrement) {
    LinkedList<int> list;
    list.InsertTail(42);
    auto it = list.begin();
    auto it2 = it++;
    EXPECT_EQ(*it2, 42);
    EXPECT_EQ(it, list.end());
}

TEST(LinkedListIteratorTest, IteratorEquality) {
    LinkedList<int> list;
    list.InsertTail(1);
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_TRUE(it1 == it2);
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

TEST(LinkedListIteratorTest, FindElementUsingIterator) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);
    list.InsertTail(3);

    auto it = std::find(list.begin(), list.end(), 2);
    ASSERT_NE(it, list.end());
    EXPECT_EQ(*it, 2);

    auto itNotFound = std::find(list.begin(), list.end(), 99);
    EXPECT_EQ(itNotFound, list.end());
}

TEST(LinkedListIteratorTest, ConstIteratorWorks) {
    const LinkedList<int> list = [](){
        LinkedList<int> l;
        l.InsertTail(5);
        l.InsertTail(6);
        return l;
    }();

    int expected[] = {5, 6};
    int idx = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[idx++]);
    }
    EXPECT_EQ(idx, list.Size());
}

TEST(LinkedListIteratorTest, ForEachCallsFunctionOnAllElements) {
    LinkedList<int> list;
    list.InsertTail(1);
    list.InsertTail(2);
    list.InsertTail(3);

    int sum = 0;
    list.ForEach([&sum](int& x) { sum += x; });
    EXPECT_EQ(sum, 6);
}
