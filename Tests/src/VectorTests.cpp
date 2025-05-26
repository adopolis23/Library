#include <gtest/gtest.h>
#include "Vector.h"

namespace VectorTests {


    // --- Basic Vector Tests ---
    TEST(VectorTests, AtRetrievesValue) {

        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);

        EXPECT_EQ(vec[0], 1);
        EXPECT_EQ(vec[2], 3);

    }
    TEST(VectorTests, PushBackStoresValue) {

        MyLibrary::Vector<int> vec;
        vec.PushBack(123);
        vec.PushBack(321);
        vec.PushBack(321);
        vec.PushBack(3);

        EXPECT_EQ(vec[0], 123);
        EXPECT_EQ(vec[3], 3);

    }

    TEST(VectorTests, ToStringReturnsCorrect)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(123);
        EXPECT_EQ(vec.ToString(), "[123]");
    }

    TEST(VectorTests, GetSizeReturnsCorrect)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(123);
        vec.PushBack(123);
        vec.PushBack(123);
        vec.PushBack(123);
        EXPECT_EQ(vec.GetSize(), 4);
    }

    TEST(VectorTests, ConstSquareBracketsOperator)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        EXPECT_EQ(vec[1], 2);
        EXPECT_EQ(vec[3], 4);
        EXPECT_EQ(vec[-1], 4);
        EXPECT_EQ(vec[-2], 3);
    }

    TEST(VectorTests, SquareBracketsOperator)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        vec[1] = 50;
        vec[3] = 100;

        EXPECT_EQ(vec[1], 50);
        EXPECT_EQ(vec[3], 100);
    }

    TEST(VectorTests, EqualsOperator)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        MyLibrary::Vector<int> vec2;
        vec2 = vec;

        EXPECT_EQ(vec2[1], 2);
        EXPECT_EQ(vec2[3], 4);
    }

    TEST(VectorTests, Resize)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);
        vec.PushBack(5);
        vec.PushBack(6);
        vec.Resize(4);
        
        EXPECT_EQ(*(vec.End()), 4);

        vec.Resize(10, 1);

        EXPECT_EQ(*(vec.End()), 1);
    }

    TEST(VectorTests, Capacity)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        EXPECT_EQ(vec.Capacity(), 4);

        vec.PushBack(4);

        EXPECT_EQ(vec.Capacity(), 8);

        MyLibrary::Vector<int> vec2(10);
        vec2.PushBack(1);
        vec2.PushBack(2);

        EXPECT_EQ(vec2.Capacity(), 10);
    }

    TEST(VectorTests, Empty)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        EXPECT_EQ(vec.Empty(), false);

        MyLibrary::Vector<int> vec2;

        EXPECT_EQ(vec2.Empty(), true);
    }

    TEST(VectorTests, LargeCapacityTest)
    {
        MyLibrary::Vector<int> vec;

        int count = 10000;

        for (int i = 0; i < count; i++)
        {
            vec.PushBack(i);
        }

        EXPECT_EQ(vec.GetSize(), count);
    }


    // --- Vector Iterator Tests ---
    TEST(VectorIteratorTests, BeginIterator)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        Iterator<int> iter = vec.Begin();
        EXPECT_EQ(*iter, 1);
    }

    TEST(VectorIteratorTests, EndIterator)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        Iterator<int> iter = vec.End();
        EXPECT_EQ(*iter, 4);
    }

    TEST(VectorIteratorTests, EqualOperator)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);

        for (Iterator<int> i = vec.Begin(); i != vec.End(); i++)
        {
            if (i == vec.End())
            {
                EXPECT_EQ(*i, 3);
            }
        }
    }
}