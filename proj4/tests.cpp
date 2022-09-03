// Filename: tests.cpp
// This file is for testing purposes only
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// University of Illinois at Chicago
// CS 251: Fall 2021
// 2022/02/26

#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"


TEST(grid, defaultConstructor){
    Grid<int> grid;
    EXPECT_EQ(grid.numrows(), 4);
    EXPECT_EQ(grid.numcols(0), 4);
}

TEST(grid, Parameters_Constructor_int){
    Grid<int> grid1(5,10);
    EXPECT_EQ(grid1.numrows(), 5);
    EXPECT_EQ(grid1.numcols(0), 10);
}

TEST(grid, Parameters_Constructor_double){
    Grid<double> grid2(4,9);
    EXPECT_EQ(grid2.numrows(), 4);
    EXPECT_EQ(grid2.numcols(0), 9);
}

TEST(grid, Parameters_Constructor1_string){
  Grid<string> grid3(3,8);
                EXPECT_EQ(grid3.numrows(), 3);
        EXPECT_EQ(grid3.numcols(0), 8);
}

TEST(grid, Parameters_Constructor_char){
    Grid<char> grid4(2,7);
    EXPECT_EQ(grid4.numrows(), 2);
    EXPECT_EQ(grid4.numcols(0), 7);
}

TEST(grid, NumRows_int){
    Grid<int> grid1(4,7);
    Grid<int> grid2(5,6);
    EXPECT_EQ(grid1.numrows(), 4);
    EXPECT_EQ(grid2.numrows(), 5);
}

TEST(grid, NumRows_double){
    Grid<double> grid1(9,7);
    Grid<double> grid2(8,6);
    EXPECT_EQ(grid1.numrows(), 9);
    EXPECT_EQ(grid2.numrows(), 8);
}

TEST(grid, NumRows_string){
Grid<string> grid1(1,7);
Grid<string> grid2(2,6);
EXPECT_EQ(grid1.numrows(), 1);
EXPECT_EQ(grid2.numrows(), 2);
}

TEST(grid, NumRows_char){
    Grid<char> grid1(2,7);
    Grid<char> grid2(3,6);
    EXPECT_EQ(grid1.numrows(), 2);
    EXPECT_EQ(grid2.numrows(), 3);
}

TEST(grid, NumCol_int){
    Grid<int> grid1(4,7);
    Grid<int> grid2(5,6);
    EXPECT_EQ(grid1.numcols(0), 7);
    EXPECT_EQ(grid2.numcols(0), 6);
}

TEST(grid, NumCols_double){
    Grid<double> grid1(9,5);
    Grid<double> grid2(8,4);
    EXPECT_EQ(grid1.numcols(0), 5);
    EXPECT_EQ(grid2.numcols(0), 4);
}

TEST(grid, NumCols_string){
    Grid<string> grid1(1,1);
    Grid<string> grid2(2,3);
    EXPECT_EQ(grid1.numcols(0), 1);
    EXPECT_EQ(grid2.numcols(0), 3);
}

TEST(grid, NumCols_char){
    Grid<char> grid1(2,6);
    Grid<char> grid2(3,1);
    EXPECT_EQ(grid1.numcols(0), 6);
    EXPECT_EQ(grid2.numcols(0), 1);
}

TEST(grid, size_int){
    Grid<int> grid1(4,7);
    Grid<int> grid2(5,6);
    EXPECT_EQ(grid1.size(), 28);
    EXPECT_EQ(grid2.size(), 30);
}

TEST(grid, size_double){
    Grid<double> grid1(5,8);
    Grid<double> grid2(5,9);
    EXPECT_EQ(grid1.size(), 40);
    EXPECT_EQ(grid2.size(), 45);
}

TEST(grid, size_string){
    Grid<string> grid1(1,3);
    Grid<string> grid2(2,6);
    EXPECT_EQ(grid1.size(), 3);
    EXPECT_EQ(grid2.size(), 12);
}

TEST(grid, size_char){
    Grid<char> grid1(2,3);
    Grid<char> grid2(1,5);
    EXPECT_EQ(grid1.size(), 6);
    EXPECT_EQ(grid2.size(), 5);
}

TEST(grid, bracket_operator_int){
    Grid<int> grid1(2,3);
    Grid<int> grid2(1,5);
    grid1(0,0) = 3;
    grid2(0,0) = 4;
    EXPECT_EQ(grid1(0,0), 3);
    EXPECT_EQ(grid2(0,0), 4);
}

TEST(grid, bracket_operator_double){
    Grid<double> grid1(2,3);
    Grid<double> grid2(1,5);
    grid1(0,0) = 1.19;
    grid2(0,0) = 1.17;
    EXPECT_EQ(grid1(0,0), 1.19);
    EXPECT_EQ(grid2(0,0), 1.17);
}

TEST(grid, bracket_operator_string){
    Grid<string> grid1(2,3);
    Grid<string> grid2(1,5);
    grid1(0,0) = "aa";
    grid2(0,0) = "bb";
    EXPECT_EQ(grid1(0,0), "aa");
    EXPECT_EQ(grid2(0,0), "bb");
}

TEST(grid, bracket_operator_char){
    Grid<char> grid1(2,3);
    Grid<char> grid2(1,5);
    grid1(0,0) = 'a';
    grid2(0,0) = 'b';
    EXPECT_EQ(grid1(0,0), 'a');
    EXPECT_EQ(grid2(0,0), 'b');
}

TEST(grid, copy_int){
    Grid<int> grid1(3,5);
    Grid<int> grid2(grid1);
    EXPECT_EQ(grid2.numrows(), 3);
    EXPECT_EQ(grid2.numcols(0), 5);
}

TEST(grid, copy_double){
    Grid<double> grid3(4,6);
    Grid<double> grid4(grid3);
    EXPECT_EQ(grid4.numrows(), 4);
    EXPECT_EQ(grid4.numcols(0), 6);
}

TEST(grid, copy_string){
    Grid<string> grid5(5,7);
    Grid<string> grid6(grid5);
    EXPECT_EQ(grid6.numrows(), 5);
    EXPECT_EQ(grid6.numcols(0), 7);
}

TEST(grid, copy_char){
    Grid<char> grid7(6,8);
    Grid<char> grid8(grid7);
    EXPECT_EQ(grid8.numrows(), 6);
    EXPECT_EQ(grid8.numcols(0), 8);
}

TEST(grid, copy_operator_int){
    Grid<int> grid1(1,1);
    Grid<int> grid2(8,8);
    grid1 = grid2;
    EXPECT_EQ(grid1.numrows(), 8);
    EXPECT_EQ(grid1.numcols(0), 8);
}

TEST(grid, copy_operator_double){
    Grid<double> grid3(3,6);
    Grid<double> grid4(2,9);
    grid3 = grid4;
    EXPECT_EQ(grid3.numrows(), 2);
    EXPECT_EQ(grid3.numcols(0), 9);
}

TEST(grid, copy_operator_string){
    Grid<string> grid5(4,10);
    Grid<string> grid6(3,10);
    grid5 = grid6;
    EXPECT_EQ(grid5.numrows(), 3);
    EXPECT_EQ(grid5.numcols(0), 10);
}

TEST(grid, copy_operator_char){
    Grid<char> grid7(6,4);
    Grid<char> grid8(6,7);
    grid7 = grid8;
    EXPECT_EQ(grid7.numrows(), 6);
    EXPECT_EQ(grid7.numcols(0), 7);
}

TEST(maze, basic) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 2);


    EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
    EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));


    EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

    EXPECT_FALSE(isPathToFreedom(start, "WW"));
    EXPECT_FALSE(isPathToFreedom(start, "NN"));
    EXPECT_FALSE(isPathToFreedom(start, "EE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

TEST(maze, tryingToGoThroughWalls) {
    vector<string> textMaze;

    textMaze.push_back("* S *");
    textMaze.push_back("     ");
    textMaze.push_back("W * P");
    textMaze.push_back( "     ");
    textMaze.push_back( "* * *");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
    EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
    EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
    EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}


TEST(maze, startOnItem) {
    vector<string> textMaze;

    textMaze.push_back("P-S-W");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    EXPECT_TRUE(isPathToFreedom(start, "EE"));
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "WEE"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "WW"));

}


TEST(maze, invalidChar) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_FALSE(isPathToFreedom(start, "Q"));
    EXPECT_FALSE(isPathToFreedom(start, "X"));
    EXPECT_FALSE(isPathToFreedom(start, "!"));
    EXPECT_FALSE(isPathToFreedom(start, "?"));

    EXPECT_FALSE(isPathToFreedom(start, "n"));
    EXPECT_FALSE(isPathToFreedom(start, "s"));
    EXPECT_FALSE(isPathToFreedom(start, "e"));
    EXPECT_FALSE(isPathToFreedom(start, "w"));

    ///* These are tricky - they're legal paths that happen to have an unexpected
    // * character at the end.
    start = m.getStart(2, 2);
    EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

TEST(maze, selfmade_maze1) {
    vector<string> textMaze;

    textMaze.push_back("*-*-W-*");
    textMaze.push_back("      |");
    textMaze.push_back("*-*-S-*");
    textMaze.push_back("|      ");
    textMaze.push_back("*-*-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("* *-* P");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);
    EXPECT_TRUE(isPathToFreedom(start, "EEESWWWSEEES"));

}

TEST(maze, selfmade_maze2) {
    vector<string> textMaze;

    textMaze.push_back("*-S-W-P");
    textMaze.push_back("  |    ");
    textMaze.push_back("*-*-*-*");
    textMaze.push_back("  |   |");
    textMaze.push_back("*-*-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("* *-* *");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);
    EXPECT_TRUE(isPathToFreedom(start, "EEE"));

}

//// Provided Test: This tests your personalized regular maze to see if you were
//// able to escape.
TEST(maze, escapeRegularMaze) {
    Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

//// Provided Test: This tests your personalized twisty maze to see if you were
//// able to escape.
TEST(maze, escapeTwistyMaze) {
    Maze m(4, 4);
    MazeCell* start = m.twistyMazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

