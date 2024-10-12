#include <gtest/gtest.h>
#include "../include/Rhomb.h"
#include "../include/FiguresArray.h"
#include "../include/Point.h"
#include "../include/Hexagon.h"
#include "../include/Pentagon.h"
#include <iostream>

using namespace std;

TEST(testRhomb, defaultConstructorCreatesEmptyRhomb) {
    Rhomb fig1;
    Point p1(-4, 0), p2(0, 5), p3(4, 0), p0(0, -5);
    Point p4 = p0;
    Rhomb fig2(p1, p2, p3, p4);

    ASSERT_FALSE(fig1 == fig2);
}

TEST(testRhomb, assignmentOperatorCopiesRhomb) {
    Rhomb fig1;
    Point p1(-4, 0), p2(0, 5), p3(4, 0), p0(0, -5);
    Point p4 = p0;
    Rhomb fig2(p1, p2, p3, p4);
    fig1 = fig2;
    ASSERT_TRUE(fig1 == fig2);
}

TEST(testRhomb, squareReturnsCorrectValue) {
    Point p1(-4, 0), p2(0, 5), p3(4, 0), p0(0, -5);
    Point p4 = p0;
    Rhomb fig2(p1, p2, p3, p4);
    ASSERT_TRUE(fig2.square() == 40.0);
}

TEST(testRhomb, figuresArraySquareReturnsCorrectValue) {
    FiguresArray arr;
    Point p1(-4, 0), p2(0, 5), p3(4, 0), p0(0, -5);
    Point p4 = p0;
    Rhomb fig2(p1, p2, p3, p4);
    arr.push_back(&fig2);
    ASSERT_TRUE(arr[0]->square() == 40.0);
}

TEST(testRhomb, defaultSquareIsZero) {
    Rhomb fig;
    ASSERT_TRUE(fig.square() == 0.0);
}

TEST(testRhomb, centerReturnsCorrectPoint) {
    Point p1(-4, 0), p2(0, 5), p3(4, 0), p5(0, -5);
    Point p4 = p5;
    Point p0(0, 0);
    Rhomb fig2(p1, p2, p3, p4);
    ASSERT_TRUE(fig2.center() == p0);
}

TEST(testRhomb, figuresArrayCenterReturnsCorrectPoint) {
    FiguresArray arr;
    Point p1(-4, 0), p2(0, 5), p3(4, 0), p5(0, -5);
    Point p4 = p5;
    Point p0(0, 0);
    Rhomb fig2(p1, p2, p3, p4);
    arr.push_back(&fig2);
    ASSERT_TRUE(arr[0]->center() == p0);
}

TEST(testRhomb, defaultCenterIsOrigin) {
    Rhomb fig;
    Point p0;
    ASSERT_TRUE(fig.center() == p0);
}

TEST(testPentagon, defaultConstructorCreatesEmptyPentagon) {
    Pentagon fig1;
    Point p1(2, -3), p2(3, -1), p3(5, -3), p4(4, 4), p5(4, -4);
    Pentagon fig2(p1, p2, p3, p4, p5);
    ASSERT_FALSE(fig1 == fig2);
}

TEST(testPentagon, assignmentOperatorCopiesPentagon) {
    Pentagon fig1;
    Point p1(2, -3), p2(3, -1), p3(5, -3), p4(4, 4), p5(4, -4);
    Pentagon fig2(p1, p2, p3, p4, p5);
    fig1 = fig2;
    ASSERT_TRUE(fig1 == fig2);
}

TEST(testPentagon, squareIsNonZero) {
    Point p1(2, -3), p2(3, -1), p3(5, -3), p4(4, 4), p5(4, -4);
    Pentagon fig(p1, p2, p3, p4, p5);
    ASSERT_TRUE(fig.square() != 0);
}

TEST(testPentagon, defaultSquareIsZero) {
    Pentagon fig;
    ASSERT_TRUE(fig.square() == 0);
}

TEST(testPentagon, centerIsNotOrigin) {
    Point p1(2, -3), p2(3, -1), p3(5, -3), p4(4, 4), p5(4, -4);
    Pentagon fig(p1, p2, p3, p4, p5);
    Point p0;
    ASSERT_TRUE(fig.center() != p0);
}

TEST(testHexagon, defaultConstructorCreatesEmptyHexagon) {
    Hexagon fig1;
    Point p1(-1, -1), p2(-2, -3), p3(-4, -3), p4(2, 3), p5(5, 1), p6(-5, -1);
    Hexagon fig2(p1, p2, p3, p4, p5, p6);
    ASSERT_FALSE(fig1 == fig2);
}

TEST(testHexagon, assignmentOperatorCopiesHexagon) {
    Hexagon fig1;
    Point p1(-1, -1), p2(-2, -3), p3(-4, -3), p4(2, 3), p5(5, 1), p6(-5, -1);
    Hexagon fig2(p1, p2, p3, p4, p5, p6);
    fig1 = fig2;
    ASSERT_TRUE(fig1 == fig2);
}

TEST(testHexagon, squareIsNonZero) {
    Point p1(-1, -1), p2(-2, -3), p3(-4, -3), p4(2, 3), p5(5, 1), p6(-5, -1);
    Hexagon fig(p1, p2, p3, p4, p5, p6);
    ASSERT_TRUE(fig.square() != 0.0);
}

TEST(testHexagon, defaultSquareIsZero) {
    Hexagon fig;
    ASSERT_TRUE(fig.square() == 0);
}

TEST(testHexagon, centerIsNotOrigin) {
    Point p1(-1, -1), p2(-2, -3), p3(-4, -3), p4(2, 3), p5(5, 1), p6(-5, -1);
    Hexagon fig(p1, p2, p3, p4, p5, p6);
    Point p0;
    ASSERT_TRUE(fig.center() != p0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}