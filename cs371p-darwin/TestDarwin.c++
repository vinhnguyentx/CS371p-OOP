/** @file TestDarwin.c++
 *  @brief this file contains tests for Darwin's World
 */

// --------
// include
// --------

#define private public

#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <cassert>  // assert
#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// ----
// Class Darwin
// ----

/**
 * test constructor, addCreature, isWall, isEmpty
 */

TEST(DarwinFixture, constructor1) {
    Darwin d (2, 2);
    ASSERT_EQ (d.grid.size(), 4);
}

TEST(DarwinFixture, constructor2) {
    Darwin d (3, 3);
    ASSERT_EQ (d.grid.size(), 9);
    for (int i = 0; i < 9; ++i){
        ASSERT_EQ (d.grid.at(i), nullptr);
    }
}

TEST(DarwinFixture, constructor3) {
    Darwin d (3, 8);
    ASSERT_EQ (d.grid.size(), 24);
    for (int i = 0; i < 24; ++i){
        ASSERT_EQ (d.grid.at(i), nullptr);
    }
}

TEST(DarwinFixture, constructor4) {
    Darwin d (3, 8);
    ASSERT_EQ (d.grid.size(), 24);
    ASSERT_EQ (d.row, 3);
    ASSERT_EQ (d.col, 8);
}

TEST(DarwinFixture, constructor5) {
    Darwin d (3, 3);
    ASSERT_EQ (d.grid.size(), 9);
    ASSERT_EQ (d.row, 3);
    ASSERT_EQ (d.col, 3);
}

TEST(DarwinFixture, constructor6) {
    Darwin d (8, 8);
    ASSERT_EQ (d.grid.size(), 64);
    ASSERT_TRUE (d.row == 8);
    ASSERT_FALSE (d.col == 3);
}

TEST(DarwinFixture, constructor7) {
    Darwin d (2, 5);
    ASSERT_FALSE (d.col == 8);
}

TEST(DarwinFixture, constructor8) {
    Darwin d (3, 8);
    ASSERT_FALSE (d.grid.size() == 64);
}

TEST(DarwinFixture, constructor9) {
    Darwin d (72, 72);
    ASSERT_FALSE (d.grid.size() == 24);
    ASSERT_FALSE (d.row == 78);
    ASSERT_TRUE (d.col == 72);
}

TEST(DarwinFixture, constructor10) {
    Darwin d (5, 5);
    ASSERT_FALSE (d.row == 3);
    ASSERT_EQ (d.col, 5);
}

TEST(TestDarwin, addCreature1){
    Darwin map(5, 7);

    Species sp("abc");
    Creature cr(&sp, "south");

    map.addCreature(&cr, {0, 0});

    ASSERT_EQ(map.at({0, 0}), &cr);
}

TEST(TestDarwin, addCreature2){
    Darwin map(4, 8);

    Species sp("abc");
    Creature cr(&sp, "south");

    int a = map.addCreature(&cr, {0, 0});

    ASSERT_EQ(a, 0);
}

TEST(TestDarwin, addCreature3){
    Darwin map(4, 8);

    Species sp("abc");
    Creature cr(&sp, "south");

    int a = map.addCreature(&cr, {4, 0});

    ASSERT_EQ(a, -1);
}

TEST(TestDarwin, addCreature4){
    Darwin map(4, 8);

    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");

    int a = map.addCreature(&cr1, {1, 0});
    int b = map.addCreature(&cr2, {1, 0});

    ASSERT_EQ(a, 0);
    ASSERT_EQ(b, -1);
}

TEST(TestDarwin, addCreature5){
    Darwin map(4, 8);

    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");

    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 0});

    ASSERT_EQ(map.at({1, 0}), &cr1);

}

TEST(TestDarwin, isWall1){
    Darwin map(4, 8);

    ASSERT_EQ(map.isWall({-1, -1}), 1);

}

TEST(TestDarwin, isWall2){
    Darwin map(4, 8);

    ASSERT_EQ(map.isWall({1, 1}), 0);

}

TEST(TestDarwin, isWall3){
    Darwin map(4, 8);

    ASSERT_EQ(map.isWall({4, 8}), 1);

}

TEST(TestDarwin, isWall4){
    Darwin map(4, 4);

    ASSERT_EQ(map.isWall({4, 4}), 1);

}

TEST(TestDarwin, isWall5){
    Darwin map(8, 8);

    ASSERT_EQ(map.isWall({4, 7}), 0);
}

TEST(TestDarwin, isWall6){
    Darwin map(80, 80);

    ASSERT_TRUE(map.isWall({80, 80}));
    ASSERT_EQ(map.isWall({0, 0}), 0);
}

TEST(TestDarwin, isWall7){
    Darwin map(800, 800);

    ASSERT_FALSE(map.isWall({80, 80}));
    ASSERT_EQ(map.isWall({0, 0}), 0);
}

TEST(TestDarwin, isWall8){
    Darwin map(10, 10);

    ASSERT_TRUE(map.isWall({80, 80}));
    ASSERT_EQ(map.isWall({0, 0}), 0);
}

TEST(TestDarwin, isWall9){
    Darwin map(1, 1);

    ASSERT_EQ(map.isWall({0, 0}), 0);
}

TEST(TestDarwin, isWall10){
    Darwin map(1, 1);

    ASSERT_FALSE(map.isWall({0, 0}));
}

TEST(TestDarwin, isEmpty1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.isEmpty({1, 2}), 1);

}

TEST(TestDarwin, isEmpty2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.isEmpty({1, 0}), 0);

}

TEST(TestDarwin, isEmpty3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.isEmpty({1, 1}), 0);

}

TEST(TestDarwin, isEmpty4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.isEmpty({-1, 1}), 0);

}

TEST(TestDarwin, isEmpty5){

    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {3, 1});
    ASSERT_TRUE(map.isEmpty({2, 1}));

}

TEST(TestDarwin, isEmpty6){

    Darwin map(8, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Species sp3("def");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "east");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {2, 7});
    map.addCreature(&cr3, {1, 4});
    ASSERT_TRUE(map.isEmpty({3, 1}));

}

TEST(TestDarwin, isEmpty7){

    Darwin map(2, 2);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp1, "north");
    Creature cr3(&sp1, "east");
    Creature cr4(&sp1, "west");

    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {0, 0});
    map.addCreature(&cr4, {1, 1});
    ASSERT_FALSE(map.isEmpty({2, 1}));

}

TEST(TestDarwin, isEmpty8){

    Darwin map(2, 2);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp1, "north");
    Creature cr3(&sp1, "east");

    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {0, 0});
    ASSERT_TRUE(map.isEmpty({1, 1}));

}

TEST(TestDarwin, isEmpty9){

    Darwin map(1, 1);

    ASSERT_TRUE(map.isEmpty({0, 0}));

}

TEST(TestDarwin, isEmpty10){

    Darwin map(10, 20);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp1, "north");
    Creature cr3(&sp1, "east");

    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {0, 0});
    ASSERT_TRUE(map.isEmpty({9, 11}));

}

/**
 * test: Darwin is indexable
 */

TEST(TestDarwin, at1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.at({1, 1}), &cr2);

}

TEST(TestDarwin, at2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.at({1, 0}), &cr1);

}

TEST(TestDarwin, at3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.at({0, 0}), nullptr);

}

TEST(TestDarwin, at4){
    
    Darwin map(2, 2);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {0, 1});
    ASSERT_EQ(map.at({1, 0}), &cr1);

}

TEST(TestDarwin, at5){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {1, 0});
    map.addCreature(&cr2, {1, 1});
    ASSERT_EQ(map.at({1, 0})->_p, &sp1);

}

TEST(TestDarwin, at6){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    ASSERT_FALSE(map.at({3, 0})->_c);

}

TEST(TestDarwin, at7){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    ASSERT_TRUE(map.at({3, 0})->_p);

}

/**
 * test: Darwin is iterable with begin()
 */

TEST(TestDarwin, begin1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    ASSERT_TRUE(*it);
}

TEST(TestDarwin, begin2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    ASSERT_FALSE(*(it+1));
}

TEST(TestDarwin, begin3){
    
    Darwin map(2, 2);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {1, 0});
    Darwin::iterator it = map.begin();
    ASSERT_TRUE(*(it+2));
}

TEST(TestDarwin, begin4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    ASSERT_FALSE(*(it+3));
}

TEST(TestDarwin, begin5){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    ASSERT_TRUE(*(it++));
}

TEST(TestDarwin, begin6){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    ASSERT_TRUE(*(++it));
}

TEST(TestDarwin, begin7){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {0, 2});
    Darwin::iterator it = map.begin();
    ASSERT_TRUE(*(--(it + 3)));
}

TEST(TestDarwin, begin8){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    it = it + 2;
    ASSERT_FALSE(*(it--));
}

TEST(TestDarwin, begin9){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 2});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    Darwin::iterator it2 = it + 10;
    ASSERT_EQ(it2 - it, 10);
}

TEST(TestDarwin, begin10){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.begin();
    it = it + 1;
    ASSERT_TRUE(*(it--));
}


/**
 * test: Darwin is iterable with end()
 */

TEST(TestDarwin, end1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    ASSERT_TRUE(*(--it));
}

TEST(TestDarwin, end2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {0, 1});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    ASSERT_TRUE(*(--it) == &cr3);
}

TEST(TestDarwin, end3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    it = it - 2;
    ASSERT_TRUE(*it);
}

TEST(TestDarwin, end4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    it = it - 1;
    ASSERT_TRUE(*it);
}

TEST(TestDarwin, end5){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    it = it - 3;
    ASSERT_FALSE(*it);
}

TEST(TestDarwin, end6){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    it = it - 9;
    ASSERT_FALSE(*it);
}

TEST(TestDarwin, end7){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    it = it - 3;
    ASSERT_TRUE(*it);
}

TEST(TestDarwin, end8){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it - it2 == 32);
}

TEST(TestDarwin, end9){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE((it - 32) == it2);
}

TEST(TestDarwin, end9_2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it == it2 + 32);
}

TEST(TestDarwin, end10){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it != it2);
}

TEST(TestDarwin, end11){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it != it2 + 31);
}

TEST(TestDarwin, end12){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it2 - it == -32);
}

TEST(TestDarwin, end13){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it - it2 == 32);
}

TEST(TestDarwin, end14){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Species sp2("def");
    Species sp3("xzy");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    Creature cr3(&sp3, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    map.addCreature(&cr3, {3, 7});
    Darwin::iterator it = map.end();
    Darwin::iterator it2 = map.begin();
    ASSERT_TRUE(it - it2 == 32);
}

// ----
// Class Species
// ----

/**
 * test addInstruction
 */

TEST(TestSpecies, addInstruction1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    int i = sp1.addInstruction("go", 0);
    ASSERT_TRUE(i == 0);
}

TEST(TestSpecies, addInstruction2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("go", 3);
    ASSERT_TRUE(sp1.program[0].second == 3);
}

TEST(TestSpecies, addInstruction3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("go", 0);
    sp1.addInstruction("hop");
    ASSERT_TRUE(sp1.program.size() == 2);
}

TEST(TestSpecies, addInstruction4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("go", 0);
    sp1.addInstruction("go", 0);
    sp1.addInstruction("go", 0);
    sp1.addInstruction("infect");
    ASSERT_TRUE(sp1.program.size() == 4);
}

TEST(TestSpecies, addInstruction5){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("go", 0);
    sp1.addInstruction("hop");
    sp1.addInstruction("go", 0);
    sp1.addInstruction("abcxyz", 0);
    ASSERT_TRUE(sp1.program[1].first == "hop");
}

TEST(TestSpecies, addInstruction6){
    
    Darwin map(4, 8);
    Species sp1("abc");
    int i = sp1.addInstruction("gogo", 0);
    ASSERT_TRUE(i == -1);
}

TEST(TestSpecies, addInstruction7){
    
    Darwin map(4, 8);
    Species sp1("abc");
    int i = sp1.addInstruction("goUp", 0);
    ASSERT_TRUE(i == -1);
}

TEST(TestSpecies, addInstruction8){
    
    Darwin map(4, 8);
    Species sp1("abc");
    int i = sp1.addInstruction("infect");
    ASSERT_TRUE(i == 0);
}

TEST(TestSpecies, addInstruction9){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("go", 12);
    ASSERT_TRUE(sp1.program[0].second == 12);
}

TEST(TestSpecies, addInstruction10){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("gogo", 0);
    ASSERT_TRUE(sp1.program.size() == 0);
}

TEST(TestSpecies, addInstruction11){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("gogo", 0);
    sp1.addInstruction("goUp", 0);
    sp1.addInstruction("goDown", 0);
    ASSERT_TRUE(sp1.program.size() == 0);
}

TEST(TestSpecies, addInstruction12){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("go", 0);
    sp1.addInstruction("go", 0);
    sp1.addInstruction("go", 0);
    sp1.addInstruction("go", 0);
    ASSERT_TRUE(sp1.program.size() == 4);
}

TEST(TestSpecies, addInstruction13){
    
    Darwin map(4, 8);
    Species sp1("abc");
    sp1.addInstruction("gogo", 0);
    sp1.addInstruction("go", 0);
    sp1.addInstruction("gogo", 0);
    sp1.addInstruction("go", 0);
    ASSERT_TRUE(sp1.program.size() == 2);
}

// ----
// Class Creatures
// ----

/**
 * test constructor : create a Creature of a Species
 */

 TEST(TestCreatures, constructor1){
    
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    ASSERT_TRUE(cr1._p == &sp1);
} 

TEST(TestCreatures, constructor2){
    
    Species sp1("abc");
    Species sp2("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    ASSERT_TRUE(cr1._p != &sp2);
} 

TEST(TestCreatures, constructor3){
    
    Species sp1("abc");
    Species sp2("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    ASSERT_TRUE(cr1._p != cr2._p );
} 

TEST(TestCreatures, constructor4){
    
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp1, "north");
    ASSERT_TRUE(cr1._p == cr2._p );
} 

TEST(TestCreatures, constructor5){
    
    Species sp1("abc");
    Species sp2("abc");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    ASSERT_TRUE(cr2._p == &sp2 );
} 

TEST(TestCreatures, constructor6){
    
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    ASSERT_TRUE(cr1._p->sp_name == "abc");
}

/**
 * test other methods
 */

TEST(TestCreatures, turnLeft1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    cr1.turnLeft();
    ASSERT_TRUE(cr1._d == "east");

}

TEST(TestCreatures, turnLeft2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {0, 0});
    cr1.turnLeft();
    ASSERT_TRUE(cr1._d == "west");

}

TEST(TestCreatures, turnLeft3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "west");
    map.addCreature(&cr1, {0, 0});
    cr1.turnLeft();
    ASSERT_TRUE(cr1._d == "south");

}

TEST(TestCreatures, turnLeft4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "east");
    map.addCreature(&cr1, {0, 0});
    cr1.turnLeft();
    ASSERT_TRUE(cr1._d == "north");

}

TEST(TestCreatures, turnRight1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    cr1.turnRight();
    ASSERT_TRUE(cr1._d == "west");

}

TEST(TestCreatures, turnRight2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {0, 0});
    cr1.turnRight();
    ASSERT_TRUE(cr1._d == "east");

}

TEST(TestCreatures, turnRight3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "west");
    map.addCreature(&cr1, {0, 0});
    cr1.turnRight();
    ASSERT_TRUE(cr1._d == "north");

}

TEST(TestCreatures, turnRight4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "east");
    map.addCreature(&cr1, {0, 0});
    cr1.turnRight();
    ASSERT_TRUE(cr1._d == "south");

}

TEST(TestCreatures, hop1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    cr1.hop({0,0}, map);
    ASSERT_TRUE(map.at({1,0}) == &cr1);

}

TEST(TestCreatures, hop2){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {1, 1});
    cr1.hop({1,1}, map);
    ASSERT_TRUE(map.at({2,1}) == &cr1);

}

TEST(TestCreatures, hop3){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "west");
    map.addCreature(&cr1, {0, 0});
    cr1.hop({0,0}, map);
    ASSERT_TRUE(map.at({0,0}) == &cr1);

}

TEST(TestCreatures, hop4){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {2, 2});
    cr1.hop({2,2}, map);
    ASSERT_TRUE(map.at({1,2}) == &cr1);

}

TEST(TestCreatures, hop5){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "east");
    map.addCreature(&cr1, {2, 2});
    cr1.hop({2,2}, map);
    ASSERT_TRUE(map.at({2,3}) == &cr1);

}

TEST(TestCreatures, hop6){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "east");
    map.addCreature(&cr1, {2, 2});
    cr1.hop({2,2}, map);
    cr1.hop({2,3}, map);
    ASSERT_TRUE(map.at({2,4}) == &cr1);

}

TEST(TestCreatures, hop7){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "east");
    map.addCreature(&cr1, {2, 2});
    cr1.hop({2,2}, map);
    cr1.hop({2,3}, map);
    cr1.hop({2,4}, map);
    ASSERT_TRUE(map.at({2,5}) == &cr1);

}

TEST(TestCreatures, hop8){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {2, 2});
    cr1.hop({2,2}, map);
    cr1.hop({3,2}, map);
    ASSERT_TRUE(map.at({3,2}) == &cr1);

}

TEST(TestCreatures, hop9){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {2, 2});
    cr1.hop({2,2}, map);
    cr1.hop({1,2}, map);
    cr1.hop({0,2}, map);
    ASSERT_TRUE(map.at({0,2}) == &cr1);

}

TEST(TestCreatures, hop10){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "west");
    map.addCreature(&cr1, {0, 0});
    cr1.hop({0,0}, map);
    cr1.hop({0,0}, map);
    cr1.hop({0,0}, map);
    cr1.hop({0,0}, map);
    ASSERT_TRUE(map.at({0,0}) == &cr1);

}

TEST(TestCreatures, hop11){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "east");
    Creature cr2(&sp1, "east");
    map.addCreature(&cr1, {2, 2});
    map.addCreature(&cr2, {2, 3});
    cr1.hop({2,2}, map);
    ASSERT_TRUE(map.at({2,2}) == &cr1);

}

TEST(TestCreature, infect1){
    
    Darwin map(5, 8);
    Species sp1("abc");
    Species sp2("def");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {4, 5});
    cr1.infect({3,5}, map);
    ASSERT_TRUE(map.at({4,5})->_p == &sp1);
}

TEST(TestCreature, infect2){
    
    Darwin map(5, 8);
    Species sp1("abc");
    Species sp2("def");
    Creature cr1(&sp1, "south");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {4, 5});
    cr2.infect({4,5}, map);
    ASSERT_TRUE(map.at({3,5})->_p == &sp2);
}

TEST(TestCreature, infect3){
    
    Darwin map(5, 8);
    Species sp1("abc");
    Species sp2("def");
    Creature cr1(&sp1, "east");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {4, 5});
    cr1.infect({3,5}, map);
    ASSERT_FALSE(map.at({4,5})->_p == &sp1);
}

TEST(TestCreature, infect4){
    
    Darwin map(5, 8);
    Species sp1("abc");
    Species sp2("def");
    Creature cr1(&sp1, "east");
    Creature cr2(&sp2, "west");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    cr1.infect({3,5}, map);
    ASSERT_TRUE(map.at({3,6})->_p == &sp1);
}

TEST(TestCreature, infect5){
    
    Darwin map(5, 8);
    Species sp1("abc");
    Species sp2("def");
    Creature cr1(&sp1, "east");
    Creature cr2(&sp2, "west");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {3, 6});
    cr2.infect({3,6}, map);
    ASSERT_TRUE(map.at({3,5})->_p == &sp2);
}

TEST(TestCreature, infect6){
    
    Darwin map(5, 8);
    Species sp1("abc");
    Species sp2("def");
    Creature cr1(&sp1, "west");
    Creature cr2(&sp2, "north");
    map.addCreature(&cr1, {3, 5});
    map.addCreature(&cr2, {4, 5});
    cr1.infect({3,5}, map);
    ASSERT_FALSE(map.at({4,5})->_p == &sp1);
}

TEST(TestCreatures, ifEmpty1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {2, 2});
    ASSERT_TRUE(cr1.ifEmpty({2,2}, map));

}

TEST(TestCreatures, ifEmpty2){
    
    Darwin map(1, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    ASSERT_FALSE(cr1.ifEmpty({0,0}, map));

}

TEST(TestCreatures, ifEmpty3){
    
    Darwin map(3, 4);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {0, 1});
    ASSERT_FALSE(cr1.ifEmpty({0,1}, map));

}

TEST(TestCreatures, ifEmpty4){
    
    Darwin map(2, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    Creature cr2(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 0});
    ASSERT_FALSE(cr1.ifEmpty({0,0}, map));

}

TEST(TestCreatures, ifEmpty5){
    
    Darwin map(3, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    Creature cr2(&sp1, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {2, 0});
    ASSERT_TRUE(cr2.ifEmpty({2,0}, map));

}

TEST(TestCreatures, ifWall1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {2, 2});
    ASSERT_FALSE(cr1.ifWall({2,2}, map));

}

TEST(TestCreatures, ifWall2){
    
    Darwin map(1, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    ASSERT_TRUE(cr1.ifWall({0,0}, map));

}

TEST(TestCreatures, ifWall3){
    
    Darwin map(3, 4);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {0, 1});
    ASSERT_TRUE(cr1.ifWall({0,1}, map));

}

TEST(TestCreatures, ifWall4){
    
    Darwin map(2, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    Creature cr2(&sp1, "south");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 0});
    ASSERT_TRUE(cr1.ifWall({0,0}, map));

}

TEST(TestCreatures, ifWall5){
    
    Darwin map(3, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    Creature cr2(&sp1, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {2, 0});
    ASSERT_FALSE(cr2.ifWall({2,0}, map));

}

TEST(TestCreatures, ifEnemy1){
    
    Darwin map(4, 8);
    Species sp1("abc");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {2, 2});
    Creature cr2(&sp1, "south");
    map.addCreature(&cr2, {3, 2});
    ASSERT_FALSE(cr1.ifEnemy({2,2}, map));

}

TEST(TestCreatures, ifEnemy2){
    
    Darwin map(10, 10);
    Species sp1("abc");
    Species sp2("xyz");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {2, 3});
    Creature cr2(&sp2, "north");
    map.addCreature(&cr2, {3, 3});
    ASSERT_TRUE(cr2.ifEnemy({3,3}, map));

}

TEST(TestCreatures, ifEnemy3){
    
    Darwin map(3, 4);
    Species sp1("abc");
    Creature cr1(&sp1, "north");
    map.addCreature(&cr1, {0, 1});
    ASSERT_FALSE(cr1.ifEnemy({0,1}, map));

}

TEST(TestCreatures, ifEnemy4){
    
    Darwin map(2, 1);
    Species sp1("abc");
    Creature cr1(&sp1, "west");
    Creature cr2(&sp1, "north");
    map.addCreature(&cr1, {0, 0});
    map.addCreature(&cr2, {1, 0});
    ASSERT_FALSE(cr2.ifEnemy({1,0}, map));

}

TEST(TestCreatures, ifEnemy5){
     
    Darwin map(10, 10);
    Species sp1("abc");
    Species sp2("xyz");
    Creature cr1(&sp1, "south");
    map.addCreature(&cr1, {2, 3});
    Creature cr2(&sp2, "west");
    map.addCreature(&cr2, {3, 3});
    ASSERT_TRUE(cr1.ifEnemy({2,3}, map));

}

