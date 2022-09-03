//  Project 1 Starter Code - DNA Profiling
//  Name: Haoji Ni
//  CS 251
//  2022 Spring

/*
 *  Creative Component instructions
 *  before use command please make sure DNA is being processed
 *  Use command "show_all" to execute function
 *  Then it will display all STR occurrences in DNA sequence
 */

#include <fstream>
#include <sstream>
#include <string>
#include "ourvector.h"

using namespace std;

// Function prototypes
bool check_filename(ifstream& file, const string& fileName);
void load_data_header(ifstream& file,
                      ourvector<ourvector<char>>& database_header);
void load_database(const string& fileName, int& database_flag,
                   ourvector<ourvector<string>>& data_for_display,
                   ourvector<ourvector<char>>& database_header);
void load_DNA(const string& fileName, int& dna_flag, ourvector<char>& dna);
bool process_req(int& database_flag, int& dna_flag, int& process_flag);
ourvector<int> process_DNA(int& process_flag,
                           ourvector<ourvector<char>>& database_header,
                           ourvector<char>& dna, ourvector<int>& result);
void count_repeats(ourvector<int> temp_result, int length,
                   ourvector<int>& result, ourvector<int>& all_result);
bool search_req(int& database_flag, int& dna_flag, int& process_flag);
void search(ourvector<ourvector<char>>& database_header,
            ourvector<ourvector<string>>& data_for_display,
            ourvector<int>& result);
void display_data(ourvector<ourvector<string>>& data_for_display);
void display_dna(ourvector<char>& dna);
void display_process(ourvector<ourvector<char>>& database_header,
                     ourvector<int>& result);
void display(int& database_flag, int& dna_flag, int& process_flag,
             ourvector<ourvector<string>>& data_for_display,
             ourvector<ourvector<char>>& database_header, ourvector<char>& dna,
             ourvector<int>& result);
void show_all(int& process_flag, ourvector<ourvector<char>>& database_header,
              ourvector<int>& all_result);
void main_menu();

// This function will check function file if is not valid
// If file is valid, return true
// Otherwise, return false
bool check_filename(ifstream& file, const string& fileName) {
    if (file.is_open()){
        return true;
    } else {
        cout << "Error: unable to open '" << fileName << "'" << endl;
        return false;
    }
}

// This function will load the first line of the database
// Then store the header into ourvector
void load_data_header(ifstream& file,
                      ourvector<ourvector<char>>& database_header) {
    string line;
    getline(file, line);
    // Creates a temp_database to push into ourvector
    ourvector<char> temp_database;
    istringstream iss(line);
    string chars;
    // Split string into chars and push back into ourvector
    // Clear temp ourvector after each
    while (getline(iss, chars, ',')) {
        for (char i : chars) {
            temp_database.push_back(i);
        }
        database_header.push_back(temp_database);
        temp_database.clear();
    }
}

// This function will open database file
// and store the data_for_display into ourvector
void load_database(const string& fileName, int& database_flag,
                   ourvector<ourvector<string>>& data_for_display,
                   ourvector<ourvector<char>>& database_header) {
    ifstream file(fileName);
    string line;
    cout << "Loading database..." << endl;
    // Use check_filename function to check if file is valid
    if (check_filename(file, fileName)) {
        data_for_display.clear();
        load_data_header(file, database_header);
        // Use stringstream to split input line into words
        while (getline(file, line)) {
            stringstream ss(line);
            string word;
            ourvector<string> temp_chart;
            // Push back each word into 2d ourvector
            while (getline(ss, word, ',')) temp_chart.push_back(word);
            data_for_display.push_back(temp_chart);
            temp_chart.clear();
        }
        database_flag = 1;
        file.close();
    } else {
        database_flag = 0;
    }
}

// This function will load DNA files
// save the DNA as chars
// and store the DNA into ourvector
void load_DNA(const string& fileName, int& dna_flag, ourvector<char>& dna) {
    ifstream file(fileName);
    string line;
    cout << "Loading DNA..." << endl;
    // Use check_filename function to check if file is valid
    // Clear the dna vector before process to avoid duplicate
    if (check_filename(file, fileName)) {
        dna.clear();
        while (getline(file, line)) {
            for (char i : line) {
                dna.push_back(i);
            }
        }
        dna_flag = 1;
        file.close();
    } else {
        dna_flag = 0;
    }
}

// This function will check if the user input is valid
// It will check the flag of database and DNA
bool process_req(int& database_flag, int& dna_flag, int& process_flag) {
    if (database_flag == 0) {
        cout << "No database loaded." << endl;
        return false;
    } else if (dna_flag == 0) {
        cout << "No DNA loaded." << endl;
        return false;
    } else {
        cout << "Processing DNA..." << endl;
        return true;
    }
}

// This function will process the DNA and sort it
// Use for loop to go through the dna sequence
// It will return an ourvector for Creative Component function
ourvector<int> process_DNA(int& process_flag, ourvector<ourvector<char>>& database_header, ourvector<char>& dna, ourvector<int>& result) {
    result.clear();
    ourvector<int> temp_result, all_result;
    int str_line = 1;
    int k = 0;
    int length;
    // It will check if the char is the same within the length
    // Use k to count the length, reset to 0 when the char is not the same
    while (str_line < database_header.size()) {
        length = database_header[str_line].size();
        for (int i = 0; i < dna.size() - length; i++) {
            if (dna[i] == database_header[str_line][k]) {
                k++;
                // If matched, push the location of char in DNA to temp result vector
                // and reset k to 0
                if (k == length) {
                    temp_result.push_back(i - length + 1);
                    if (i + 1 + length == dna.size()) temp_result.push_back(i + 1);
                    k = 0;
                }
            } else {
                // If not matched, reset k to 0
                // If "i" is smaller than 0, set it back to 0 to avoid out of range
                i = i - k;
                if (i < 0) i = 0;
                k = 0;
            }
        }
        str_line++;
        count_repeats(temp_result, length, result, all_result);
        // Clear temp result vector after finish count repeats DNA sequence
        temp_result.clear();
    }
    process_flag = 1;
    return all_result;
}

// This function will count the repeats DNA sequence
// Use for loop to go through the temp_result vector
void count_repeats(ourvector<int> temp_result, int length,
                   ourvector<int>& result, ourvector<int>& all_result) {
    int max = 1;
    int count = 1;
    int i = 0;
    if (temp_result.size() > 0) {
        while (i < temp_result.size() - 1) {
            // If they are repeated, the range between char should equal to length
            // So, if i+length is equal to i+1, it means they are repeated
            if (temp_result.at(i) + length == temp_result.at(i + 1)) {
                count++;
                i++;
                if (count > max) max = count;
            } else {
                count = 1;
                i++;
            }
        }
        if (temp_result.at(0) == 5) max++;
        result.push_back(max);
    } else {
        // If result vector size is equal to 0, that means no match found
        // So push back 0 to result vector
        result.push_back(0);
    }
    all_result.push_back(temp_result.size());
}

// This function will check requirement for search function
// If one of the flag is equal to zero, display error message and return false
bool search_req(int& database_flag, int& dna_flag, int& process_flag) {
    if (database_flag == 0) {
        cout << "No database loaded." << endl;
        return false;
    } else if (dna_flag == 0) {
        cout << "No DNA loaded." << endl;
        return false;
    } else if (process_flag == 0) {
        cout << "No DNA processed." << endl;
        return false;
    } else {
        return true;
    }
}

// This function will search paired DNA
// Use for loop the go through the result vector
void search(ourvector<ourvector<char>>& database_header,
            ourvector<ourvector<string>>& data_for_display,
            ourvector<int>& result) {
    cout << "Searching database..." << endl;
    // -1 because the first element in database header is "N A M E"
    int length = database_header.size() - 1;
    int k = 0;
    int found_flag = 0;
    for (auto& i : data_for_display) {
        for (int j = 1; j < i.size(); j++) {
            int temp_number = stoi(i[j]);
            // Similar to process_DNA function, if found, k++
            // If k is equal to length, that means the DNA sequence is found
            // Use break function to stop for loop, set flag equal to 1
            if (temp_number == result[j - 1]) {
                k++;
                if (k == length) {
                    cout << "Found in database!  DNA matches: " << i[0] << endl;
                    found_flag = 1;
                    break;
                }
            } else {
                k = 0;
            }
            if (found_flag == 1) break;
        }
    }
    // If flag is equal to 0, that means no match found
    if (found_flag == 0) cout << "Not found in database." << endl;
}

// This function will display database file
// Use for range loop to output database
void display_data(ourvector<ourvector<string>>& data_for_display) {
    for (auto& i : data_for_display) {
        for (int j = 0; j < i.size(); j++) {
            if (j == i.size() - 1)
                cout << i[j];
            else
                cout << i[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// This function will display DNA file
// Use for range loop to output database
void display_dna(ourvector<char>& dna) {
    for (auto& i : dna) {
        cout << i;
    }
    cout << endl << endl;
}

// This function will display processed result
// Use for range loop to output process result
void display_process(ourvector<ourvector<char>>& database_header,
                     ourvector<int>& result) {
    // i is equal to one because first element is "N A M E"
    for (int i = 1; i < database_header.size(); i++) {
        for (char j : database_header[i]) cout << j;
        cout << ": " << result.at(i - 1) << endl;
    }
    cout << endl;
}

// This function is a base of the display
// Will lead to different display function
// Use flags to determine each function status
void display(int& database_flag, int& dna_flag, int& process_flag,
             ourvector<ourvector<string>>& data_for_display,
             ourvector<ourvector<char>>& database_header, ourvector<char>& dna,
             ourvector<int>& result) {
    if (database_flag == 0) {
        cout << "No database loaded." << endl;
    } else {
        cout << "Database loaded: " << endl;
        display_data(data_for_display);
    }
    if (dna_flag == 0) {
        cout << "No DNA loaded." << endl << endl;
    } else {
        cout << "DNA loaded: " << endl;
        display_dna(dna);
    }
    if (process_flag == 0) {
        cout << "No DNA has been processed." << endl;
    } else {
        cout << "DNA processed, STR counts: " << endl;
        display_process(database_header, result);
    }
}

// Creative Component instructions
// This function will count all STR occurrences
void show_all(int& process_flag, ourvector<ourvector<char>>& database_header,
              ourvector<int>& all_result) {
    if (process_flag == 1) {
        cout << "All STR counts: " << endl;
        display_process(database_header, all_result);
        all_result.clear();
    } else {
        cout << "Please process DNA first." << endl;
    }
}

// This function will print a user screen and let user input choice
// Declare all the flags and ourvector here
// Use pass by reference to use
void main_menu() {
    int database_flag = 0;
    int dna_flag = 0;
    int process_flag = 0;
    ourvector<ourvector<string>> data_for_display;
    ourvector<ourvector<char>> database_header;
    ourvector<char> dna;
    ourvector<int> result, all_result;
    string db_name, dna_name, choice;
    while (choice != "#") {
        cout << "Enter command or # to exit: ";
        cin >> choice;
        if (choice == "load_db") {
            cin >> db_name;
            load_database(db_name, database_flag, data_for_display, database_header);
        } else if (choice == "display")
            display(database_flag, dna_flag, process_flag, data_for_display, database_header, dna, result);
        else if (choice == "load_dna") {
            cin >> dna_name;
            load_DNA(dna_name, dna_flag, dna);
        } else if (choice == "process") {
            if (process_req(database_flag, dna_flag, process_flag))
                all_result = process_DNA(process_flag, database_header, dna, result);
        } else if (choice == "search") {
            if (search_req(database_flag, dna_flag, process_flag))
                search(database_header, data_for_display, result);
        } else if (choice == "show_all")
            show_all(process_flag, database_header, all_result);
    }
}

// Main, will load main menu function to start program
int main() {
    cout << "Welcome to the DNA Profiling Application." << endl;
    main_menu();
    return 0;
}
