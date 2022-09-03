// Bar Chart Animation
// Created by: Shanon Reckinger
// U. of Illinois, Chicago
// CS 251: Fall 2021
// Modified by: Haoji Ni
// 2022/02/12

/*
 * ------------------Creative Component User Guide------------------
 * 1. Enter the file name that contains the data,
 *    if the file is not exist, the program will exit.
 *
 * 2. Then, the program will ask for the number of frames to display,
 *    the range is from 1-max size of bar chart.
 *
 * 3. At end, the program will ask for the number of bars to display,
 *    range is all positive integers, since the program will only
 *    display the max number of bars.
 *
 * 4. The program will display the bar chart animation, once is done,
 *    it will ask if you want watch again, if input is 0, the program
 *    will replay the animation, if input is other number, the program
 *    will exit.
 *-------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;

// Function prototypes
void mainMenu();
int getNumFrames(int max);
int getNumBars();

void mainMenu() {
    // Ask for the file name, open it
    string filename, title, xlabel, source;
    cout << "Please Enter The File Name: ";
    cin >> filename;
    ifstream inFile(filename);
    // If file does not exist, exit
    if (!inFile.is_open()) {
        cout << "File Not Found!" << endl;
        return;
    }
    // Get the title, xlabel, and source
    getline(inFile, title);
    getline(inFile, xlabel);
    getline(inFile, source);
    // Create class object, add frame data
    BarChartAnimate bca(title, xlabel, source);
    while (!inFile.eof()) {
        bca.addFrame(inFile);
    }
    // Get user options
    int numFrames = getNumFrames(bca.getSize()-1);
    int numBars = getNumBars();
    int i = 0;
    // Display the animation, if user input 0, replay
    while(i == 0) {
        bca.animate(cout,numBars,numFrames);
        cout << "Input 0 to watch again, other number to quit: " << endl;
        cin >> i;
    }
    cout << "Goodbye!" << endl;
}


int getNumFrames(int max){
    int numFrames;
    cout << "Please pick number of frames you want to view(enter -1 to view all): ";
    cin >> numFrames;
    // Validate input, if not in range, ask again
    if (numFrames == -1) {
        // If user input -1, do nothing
        return numFrames;
    } else if (numFrames < 1 || numFrames > max) {
        cout << "Invalid Number of Frames!" << endl;
        return getNumFrames(max);
    } else {
        return numFrames;
    }
}

int getNumBars(){
    int numBars;
    cout << "Please pick number of bars you want to view: ";
    cin >> numBars;
    // Validate input, if not in range, ask again
    if (numBars < 1) {
        cout << "Invalid Number of Bars!" << endl;
        return getNumBars();
    } else {
        return numBars;
    }
}

int main() {
    // cout Welcome message
    cout << "Welcome To BarChart Application!" << endl;
    cout << "This Application Will Read The File With Correct Format" << endl;
    cout << "And Produce An Animated BarChart" << endl;
    mainMenu();
    return 0;
}
