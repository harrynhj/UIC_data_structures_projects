// Filename: barchart.h
// This header file will generate frames for animation.
// Included in barchartanimate.h
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// 2022/02/12

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "bar.h"
#include "myrandom.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// Use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// BarChart class
class BarChart {
private:
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // Stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    Bar* bars;  // Pointer to a C-style array
    int capacity;
    int size;
    string frame;

public:
    // Default constructor:
    // Initializes to default values
    BarChart() {
        capacity = 0;
        size = 0;
        frame = "";
        bars = nullptr;
    }

    // Parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        bars = new Bar[n];
        capacity = n;
        size = 0;
        frame = "";
    }

    // Copy constructor:
    // Called automatically by C++ to create an BarChart that contains
    // A copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    BarChart(const BarChart& other) {
        bars = new Bar[other.capacity];
        // Copy all the elements in the other BarChart
        for (int i = 0; i < other.size; i++) {
            bars[i] = other.bars[i];
        }
        // Copy other member variables
        capacity = other.capacity;
        size = other.size;
        frame = other.frame;
    }

    // Copy operator=
    // Called when you assign one BarChart into another, i.e. this = other;
    BarChart& operator=(const BarChart& other) {
        // If is the same, do nothing
        if (this == &other) {
            return *this;
        }
        // Free out memory for old bars
        delete[] bars;
        // Allocate new memory for new bars
        bars = new Bar[other.capacity];
        // Copy all the elements in the other BarChart
        for (int i = 0; i < other.size; i++) {
            bars[i] = other.bars[i];
        }
        // Copy other member variables
        capacity = other.capacity;
        size = other.size;
        frame = other.frame;
        return *this;
    }

    // Clear
    // Frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;
        capacity = 0;
        size = 0;
        frame = "";
    }

    // Destructor:
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    virtual ~BarChart() {
        // Delete when size is greater than 0
        if (size > 0) {
            delete[] bars;
        }
        capacity = 0;
        size = 0;
        frame = "";
    }

    // SetFrame
    void setFrame(string frame) { this->frame = frame; }

    // GetFrame()
    // Returns the frame of the BarChart object.
    string getFrame() { return frame; }

    // AddBar
    // Adds a Bar to the BarChart.
    // Returns true if successful
    // Returns false if there is no room
    bool addBar(string name, int value, string category) {
        if (size == capacity) {
            return false;
        }
        Bar temp(name, value, category);
        bars[size] = temp;
        size++;
        return true;
    }

    // GetSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() { return size; }

    // Operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        if (i > size || i < 0) {
            throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i];
    }

    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    void dump(ostream& output) {
        // Sort before output
        sort(bars, bars + size, greater<Bar>());
        output << "frame: " << frame << endl;
        // Output all the bars for testing use
        for (int i = 0; i < size; i++) {
            output << bars[i].getName() << ' ' << bars[i].getValue() << ' '
                   << bars[i].getCategory() << endl;
        }
    }

    // Graph
    // Used for printing out the bar.
    // Output is any stream (cout, file stream, string stream)
    // ColorMap maps category -> color
    // Top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream& output, map<string, string>& colorMap, int top) {
        // This is number of BOXs that should be printed
        int lenMax = 60;
        // If there are less than top bars, print all bars
        if (size < top) {
            top = size;
        }
        string barstr = "";
        int number_of_boxes = 0;
        // Sort the c array
        sort(bars, bars + size, greater<Bar>());
        // Convert int to double
        double max = bars[0].getValue();
        for (int i = 0; i < top; i++) {
            // Calculate the width of the bar
            double temp_value = bars[i].getValue();
            double percent = temp_value / max;
            // Round to floor
            number_of_boxes = floor(percent * lenMax);
            // Set bar size
            for (int j = 0; j < number_of_boxes; j++) {
                barstr += BOX;
            }
            // Output the bar
            if (colorMap.count(bars[i].getCategory()) != 0) {
                output << colorMap.at(bars[i].getCategory()) << barstr << " "
                       << bars[i].getName() << " " << bars[i].getValue() << endl;
            } else {
                output << BLACK << barstr << " " << bars[i].getName() << " "
                       << bars[i].getValue() << endl;
            }
            // Reset barstr and color
            barstr = "";
        }
    }
};
