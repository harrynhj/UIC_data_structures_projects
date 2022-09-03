// Filename: EscapeTheLabyrinth.h
// This header file will check the user input.
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// University of Illinois at Chicago
// CS 251: Fall 2021
// 2022/02/26

#include <random>
#include <set>
#include <utility>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok
 * too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Haoji Ni";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "SESENSWWSEWNENNEESSS";
const string kPathOutOfTwistyMaze = "EWEWNSEW";

// Function prototypes
bool check_nullptr(MazeCell* start, char direction);
MazeCell* move(MazeCell* start, char direction);
void check_flags(MazeCell* start, int& book_flag, int& potion_flag,
                 int& wand_flag);
bool check_invalid_move(MazeCell* start, char direction);

// This function is to check if the user input is path to freedom
// Will return true if 3 items are collected and no invalid move
// Will return false in other cases
bool isPathToFreedom(MazeCell* start, const string& moves) {
    // Initialize the flags
    int book_flag = 0;
    int potion_flag = 0;
    int wand_flag = 0;
    int size = moves.size();
    // Check if the user input is empty
    if (size == 0) return false;
    // Check if there is an item at start
    check_flags(start, book_flag, potion_flag, wand_flag);
    // Go through the user input
    for (int i = 0; i < size; i++) {
        // Check if the user input contains invalid character
        if (check_invalid_move(start, moves[i])) return false;
        // Check if the user input leads to nullptr
        if (check_nullptr(start, moves[i])) {
            // Move to next cell
            start = move(start, moves[i]);
            // Check if there is an item at current cell
            check_flags(start, book_flag, potion_flag, wand_flag);
        } else {
            return false;
        }
    }
    // Check if the user input collected 3 items
    if (book_flag == 1 && potion_flag == 1 && wand_flag == 1) {
        return true;
    } else {
        return false;
    }
}

// This function checks if the cell is nullptr
// If pointer is nullptr, return false
bool check_nullptr(MazeCell* start, char direction) {
    if (direction == 'N') {
        if (start->north == nullptr) return false;
    } else if (direction == 'S') {
        if (start->south == nullptr) return false;
    } else if (direction == 'E') {
        if (start->east == nullptr) return false;
    } else if (direction == 'W') {
        if (start->west == nullptr) return false;
    } else {
        return false;
    }
    return true;
}

// This function will return the pointer of next cell
MazeCell* move(MazeCell* start, char direction) {
    if (direction == 'N') {
        return start->north;
    } else if (direction == 'S') {
        return start->south;
    } else if (direction == 'E') {
        return start->east;
    } else if (direction == 'W') {
        return start->west;
    } else {
        return nullptr;
    }
}

// This function will check whats here in the cell
// If there is an item, set the flag to 1
void check_flags(MazeCell* start, int& book_flag, int& potion_flag,
                 int& wand_flag) {
    if (start->whatsHere == "Spellbook") {
        book_flag = 1;
    } else if (start->whatsHere == "Potion") {
        potion_flag = 1;
    } else if (start->whatsHere == "Wand") {
        wand_flag = 1;
    }
}

// This function will check if there is any invalid character
// If there is, return true
// Otherwise return false
bool check_invalid_move(MazeCell* start, char direction) {
    if (direction != 'N' && direction != 'S' && direction != 'E' &&
        direction != 'W') {
        return true;
    } else {
        return false;
    }
}
