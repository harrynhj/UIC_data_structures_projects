// Filename: barchartanimate.h
// This header file will process animation.
// Included in application.cpp
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// 2022/02/12

#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "barchart.h"
#include "myrandom.h"

using namespace std;

// BarChartAnimate class
class BarChartAnimate {
private:
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // Elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    int count;
    string title;
    string xlabel;
    string source;
    map<string, string> colorMap;


    // ExpandCapacity:
    // This function doubles the capacity of the array
    void ExpandCapacity() {
        int newCapacity = capacity *= 2;
        BarChart* new_BarChart = new BarChart[newCapacity];
        for (int i = 0; i < size; i++) {
            new_BarChart[i] = barcharts[i];
        }
        // Delete old array
        delete[] barcharts;
        // Replace with new array
        barcharts = new_BarChart;
    }

public:
    // A parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // With a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        // Initialize barcharts with size of 4
        barcharts = new BarChart[4];
        capacity = 4;
        size = 0;
        count = 0;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    // Destructor:
    // Called automatically by C++ to free the memory associated
    // By BarChartAnimate.
    virtual ~BarChartAnimate() {
        // Delete the dynamically allocated array in the barcharts
        for (int i = 0; i < capacity - 1; i++) {
            if (barcharts[i].getSize() != 0) {
                barcharts[i].clear();
            }
        }
        // Delete barcharts array if is not nullptr
        if (barcharts != nullptr) {
            delete[] barcharts;
        }
    }

    // AddFrame:
    // Adds a new BarChart to the BarChartAnimate object from the file stream.
    // If the barcharts has run out of space, double the capacity (see
    // Ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream& file) {
        // If capacity is full, run expand function
        if (size == capacity) ExpandCapacity();
        string frame, name, value, category, line;
        getline(file, line);
        getline(file, line);
        // If next line is empty, that means is eof
        if (line == "") return;
        BarChart temp_BarChart(stoi(line));
        int cap = stoi(line);
        barcharts[size] = temp_BarChart;
        temp_BarChart.clear();
        for (int i = 0; i < cap; i++) {
            getline(file, line);
            // use stringstream to split line
            stringstream ss(line);
            // get frame, name, value, category
            getline(ss, frame, ',');
            getline(ss, name, ',');
            getline(ss, line, ',');
            getline(ss, value, ',');
            getline(ss, category, ',');
            // Check if the category have a color
            if (colorMap.count(category) == 0) {
                colorMap[category] = COLORS.at(count);
                // repeat the color
                if (count == 6) {
                    count = 0;
                } else
                    count++;
            }
            // Set the frame for this barchart
            barcharts[size].setFrame(frame);
            // Add bar into barchart
            barcharts[size].addBar(name, stoi(value), category);
        }
        size++;
    }

    // Animate:
    // This function plays each frame stored in barcharts.  In order to see the
    // Animation in the terminal, you must pause between each frame.  To do so,
    // Type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // Terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // In between each frame.
    void animate(ostream& output, int top, int endIter) {
        // If endIter is -1, then print all
        if (endIter == -1)
            endIter = size;
        for (int i = 0; i < endIter; i++) {
            unsigned int microsecond = 50000;
            // Place to adjust the speed of the animation
            usleep(3 * microsecond);
            // Clear the terminal
            output << CLEARCONSOLE;
            // Print title and source
            output << BLACK << title << endl;
            output << BLACK << source << endl;
            // print bar chart
            barcharts[i].graph(output, colorMap, top);
            // print xlabel and frame
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: "<< barcharts[i].getFrame() << endl;
        }
    }

    // Public member function.
    // Returns the size of the BarChartAnimate object.
    int getSize() { return size; }

    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    BarChart& operator[](int i) {
        // Check if i is out of bounds
        if (i > size || i < 0) {
            throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }
};
