#include <gtest/gtest.h>
#include "Vector.h"

namespace VectorTests {

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

    TEST(VectorTests, ConstSquareBracketsOperatorWorks)
    {
        MyLibrary::Vector<int> vec;
        vec.PushBack(1);
        vec.PushBack(2);
        vec.PushBack(3);
        vec.PushBack(4);

        EXPECT_EQ(vec[1], 2);
        EXPECT_EQ(vec[3], 4);
    }

    TEST(VectorTests, SquareBracketsOperatorWorks)
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

    TEST(VectorTests, EqualsOperatorWorks)
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

}