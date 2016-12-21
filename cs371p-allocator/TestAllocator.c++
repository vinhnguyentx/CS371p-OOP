// ------------------------------------
// projects/allocator/TestAllocator1.c++
// Copyright (C) 2015
// Glenn P. Downing
// ------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// --------------
// TestAllocator1
// --------------

template <typename A>
struct TestAllocator1 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A                  allocator_type;
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            Allocator<int,    100>,
            Allocator<double, 100> >
        my_types_1;

TYPED_TEST_CASE(TestAllocator1, my_types_1);

TYPED_TEST(TestAllocator1, test_1) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

          allocator_type  x;
    const difference_type s = 1;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator1, test_10) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

          allocator_type  x;
    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

// --------------
// TestAllocator2
// --------------



// --------------
// TestAllocator3
// --------------

template <typename A>
struct TestAllocator3 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A                  allocator_type;
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;};

typedef testing::Types<
            Allocator<int,    100>,
            Allocator<double, 100> >
        my_types_2;

TYPED_TEST_CASE(TestAllocator3, my_types_2);

TYPED_TEST(TestAllocator3, test_100) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

          allocator_type  x;
    const difference_type s = 1;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator3, test_1000) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

          allocator_type  x;
    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

//=========
// My Tests
//=========

//Test Allocator

TEST(TestAllocator2, const_index_1) {
    const Allocator<int, 200> x;
    ASSERT_EQ(x[196], 192);}

TEST(TestAllocator2, const_index_2) {
    const Allocator<int, 50> x;
    ASSERT_EQ(x[4], 0);}

TEST(TestAllocator2, const_index_3) {
    const Allocator<double, 50> x;
    ASSERT_EQ(x[0], 42);}

//Test valid

TEST(TestAllocator4, valid_1) {
    Allocator<int, 50> x;
    ASSERT_TRUE(x.valid());}

TEST(TestAllocator4, valid_2){
    Allocator<int, 200> x;
    const int s = 10;
    x.allocate(s);
    ASSERT_TRUE(x.valid());}

TEST(TestAllocator4, valid_3) {
    Allocator<double, 100> x;
    x[0] = 32;
    x[36] = 32;
    x[40] = -52;
    x[96] = -52;
    ASSERT_TRUE(x.valid());}

//Test Allocator

//Set sentinel
TEST(TestAllocator5, Allocator_1) {
    Allocator<int, 150> x;
    ASSERT_TRUE(x.valid());}

//Set sentinel
TEST(TestAllocator5, Allocator_2) {
    Allocator<int, 90> x;
    ASSERT_TRUE(x.valid());}

// Throw bad_alloc
TEST(TestAllocator5, Allocator__3) {
    try {
        Allocator<int, 7> x;}
    catch (std::bad_alloc) {
        SUCCEED();}}

// Test allocate

// Find first fit
TEST(TestAllocator6, allocate_1) {
    Allocator<double, 200> x;
    x.allocate(8);
    ASSERT_EQ(x[0], -64);}

// Find no fit, throw bad_alloc
TEST(TestAllocator6, allocate_2) {
    Allocator<int, 200> x;
    try {
        x.allocate(150);}
    catch (std::bad_alloc) {
        SUCCEED();}}

// n < 0, throw bad_alloc
TEST(TestAllocator6, allocate_3) {
    Allocator<int, 200> x;
    try {
        x.allocate(-4);}
    catch (std::bad_alloc) {
        SUCCEED();}}

// Throws bad_alloc
TEST(TestAllocator6, allocate_4) {
    Allocator<int, 50> x;
    try {
        x.allocate(4);
        ASSERT_TRUE(x.valid());
        x.allocate(12);}
    catch (std::bad_alloc) {
        SUCCEED();}}

// Allocate many sentinels
TEST(TestAllocator6, allocate_5) {
    Allocator<int, 100> x;
    int s = 20;
    int*         p = x.allocate(s);
    int* _end = (p+s);
    int* _header = p-1;
    ASSERT_TRUE(*_header == -80);
    ASSERT_TRUE(*_end ==-80);}

// Test deallocate

// Deallocate 1 block
TEST(TestAllocator7, deallocate_1) {
    Allocator<double, 100> x;
    double* p = x.allocate(4);
    //coalesce with rest of array
    x.deallocate(p, 4);
    ASSERT_EQ(x[0], 92);
}

//Deallocate multiple blocks
TEST(TestAllocator7, deallocate_2) {
    Allocator<int, 100> x;
    int s = 20;
    int*         p = x.allocate(s);
    int* _end = (p+s);
    int* _header = p-1;
    ASSERT_TRUE(*_header == -80);
    ASSERT_TRUE(*_end ==-80);
    if (p != 0)
        x.deallocate(p, s);
    ASSERT_TRUE(*_header == 92);
}

//Throw invalid_argument
TEST(TestAllocator7, deallocate_3) {
    Allocator<int, 100> x;
    int* p = x.allocate(5);
    // int s = 5;

    try {
        int s = 5;
        x.deallocate(p - 3, s);
    }
    catch (const std::invalid_argument) {//} &"Argument is null") {
        SUCCEED();}}

// coalesce after block
TEST(TestAllocator7, deallocate_4) {
    Allocator<int, 100> x;
    int* ptr1 = x.allocate(4);
    std::size_t s = 4;
    x.deallocate(ptr1, s);
    int* ptr2 = x.allocate(4);
    ASSERT_EQ(ptr1, ptr2);
}

// coalesce before block
TEST(TestAllocator7, deallocate_5) {
    Allocator<double, 200> x;
    x.allocate(10);
    double* ptr1 = x.allocate(10);
    double* ptr2 = x.allocate(5);
    const std::size_t s = 10;
    x.deallocate(ptr1, s);
    x.deallocate(ptr2, s);
    double* ptr3 = x.allocate(20);
    ASSERT_EQ(ptr1, ptr3);}
