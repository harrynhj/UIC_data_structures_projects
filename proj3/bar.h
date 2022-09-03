// Filename: bar.h
// This header file will provide the base of bar class.
// Included in barchart.h
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// 2022/02/12

#include <iostream>
#include <string>
#include "myrandom.h"
using namespace std;

// Bar class
class Bar {
private:
    // Private member variables for a Bar object
    string name;
    int value;
    string category;

public:
    // Default constructor:
    // Initialize to default values
    Bar() {
        value = 0;
        name = "";
        category = "";
    }

    // Constructor with parameters:
    // Parameter passed in constructor Bar object.
    Bar(string name, int value, string category) {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // destructor: No need in this class
    virtual ~Bar() {}

    // getName: return the name of the bar
    string getName() { return name; }

    // getValue: return the value of the bar
    int getValue() { return value; }

    // getCategory: return the category of the bar
    string getCategory() { return category; }

    // operators overloading: return bool
    bool operator<(const Bar &other) const {
        return (this->value < other.value);
    }

    bool operator<=(const Bar &other) const {
        return (this->value <= other.value);
    }

    bool operator>(const Bar &other) const {
        return (this->value > other.value);
    }

    bool operator>=(const Bar &other) const {
        return (this->value >= other.value);
    }
};
