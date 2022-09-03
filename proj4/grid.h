// Filename: grid.h
// This header file will generate and modify the grid.
// Included in tests.cpp
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// University of Illinois at Chicago
// CS 251: Spring 2022
// 2022/02/26

#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Grid {
private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total # of columns (0..NumCols-1)
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };

    size_t NumRows;  // total # of rows (0..NumRows-1)
    CELL** Rows;     // C array of linked lists
public:
    // default constructor:
    // Called automatically by C++ to construct a 4x4 Grid.  All
    // elements are initialized to the default value of T.
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];

            // create the linked list for this row.
            for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }
    // parameterized constructor:
    // Called automatically by C++ to construct a Grid with R rows,
    // where each row has C columns. All elements are initialized to
    // the default value of T.
    Grid(size_t R, size_t C) {
        if (R < 1 || C < 1) {
            throw invalid_argument("Invalid input");
        }
        // initialize R rows
        Rows = new CELL*[R];
        NumRows = R;
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; r++) {
            Rows[r] = new CELL(nullptr, T(), C);
            CELL* cur = Rows[r];

            // create the linked list for this row.
            for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    // destructor:
    // Called automatically by C++ to free the memory associated by the vector.
    virtual ~Grid() {
        for (size_t r = 0; r < NumRows; r++) {
            CELL* cur = Rows[r];
            // Set the next pointer to nullptr
            while (cur != nullptr) {
                CELL* temp = cur;
                cur = cur->Next;
                delete temp;
            }
        }
        // Delete the array of pointers
        delete[] Rows;
    }

    // copy constructor:
    // Called automatically by C++ to construct a Grid that contains a
    // copy of an existing Grid.  Example: this occurs when passing
    // Grid as a parameter by value
    //
    //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
    //   { ... }
    //
    Grid(const Grid<T>& other) {
        // Copy elements from other
        NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        // Copy linked lists
        for (size_t r = 0; r < NumRows; r++) {
            Rows[r] = new CELL(nullptr, T(), other.Rows[r]->NumCols);
            CELL* cur = Rows[r];
            CELL* otherCur = other.Rows[r];
            // Copy individual cells
            while (otherCur != nullptr) {
                cur->Val = otherCur->Val;
                cur->Next = new CELL(nullptr, T(), otherCur->NumCols);
                cur = cur->Next;
                otherCur = otherCur->Next;
            }
        }
    }

    // copy operator=
    // Called when you assign one vector into another, i.e. this = other;
    // Delete the current grid and copy the other grid.
    Grid& operator=(const Grid& other) {
        // Delete old grid
        for (size_t r = 0; r < NumRows; r++) {
            CELL* cur = Rows[r];
            while (cur != nullptr) {
                CELL* temp = cur;
                cur = cur->Next;
                delete temp;
            }
        }
        delete[] Rows;
        // Copy elements from other
        NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        // Copy linked lists
        for (size_t r = 0; r < NumRows; r++) {
            Rows[r] = new CELL(nullptr, T(), other.Rows[r]->NumCols);
            CELL* cur = Rows[r];
            CELL* other_cur = other.Rows[r];
            // Copy individual cells
            while (other_cur != nullptr) {
                cur->Val = other_cur->Val;
                cur->Next = new CELL(nullptr, T(), other_cur->NumCols);
                cur = cur->Next;
                other_cur = other_cur->Next;
            }
        }
        return *this;
    }

    // numrows
    // Returns the # of rows in the Grid.  The indices for these rows
    // are 0..numrows-1.
    size_t numrows() const { return NumRows; }

    // numcols
    // Returns the # of columns in row r.  The indices for these columns
    // are 0..numcols-1.  For now, each row will have the same number of columns.
    size_t numcols(size_t r) const { return Rows[r]->NumCols; }

    // size
    // Returns the total # of elements in the grid.
    size_t size() const { return NumRows * Rows[0]->NumCols; }

    // ()
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    grid(r, c) = ...
    //    cout << grid(r, c) << endl;
    T& operator()(size_t r, size_t c) {
        // If out of bounds, throw an error
        if (r >= NumRows || c >= Rows[r]->NumCols) {
            throw out_of_range("Out of range");
        }
        for (CELL* cur = Rows[r]; cur != nullptr; cur = cur->Next) {
            if (c == 0) {
                return cur->Val;
            }
            // Use c-- to count down
            c--;
        }
    }

    // _output
    // Outputs the contents of the grid; for debugging purposes.  This is not
    // tested.
    void _output() {
        // Print out the grid by using double for loops
        for (size_t r = 0; r < NumRows; r++) {
            for (size_t c = 0; c < Rows[r]->NumCols; c++) {
                cout << operator()(r, c) << " ";
            }
            cout << endl;
        }
    }
};
