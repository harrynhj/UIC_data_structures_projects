// FileName: main.cpp
// Project 2: Personality Tests
// Name: Haoji Ni
// UIC CS251 Spring 2022
// Date: 1/27/2022

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include "driver.h"

using namespace std;



// Function prototypes
int get_amount();
Question get_question_factor(const string& line);
void get_person_scores(const string& line, set<Person>& p_set);
set<Person> initialize_people(const string& file_name);
void get_result(set<Person> p_set, map<char, int> scores);
set<Question> initialize_question(const string& file_name);
int display_questions(const Question& selected_question);
string get_file_name(int choice);
void people_menu(map<char, int>& scores);



// This function is used to get question factor
// Input line, then use stringstream to split the line
// Use erase function to remove ':' and store the number
// Return Question struct
Question get_question_factor(const string& line) {
    // Declare variables
    Question q;
    char factor;
    int number;
    string temp, question;
    stringstream ss(line);

    // Stop at the first '.', store the question
    getline(ss, question, '.');
    q.questionText = question;
    // Stop at the first space, store the factor
    getline(ss, temp, ' ');

    while (getline(ss, temp, ' ')) {
        factor = temp[0];
        // Erase factor and ':'
        temp.erase(0, 2);
        number = stoi(temp);
        q.factors.emplace(factor, number);
    }
    return q;
}

// This function is used to store question set
// Open the file, use function get_question_factor
// return Question struct bak and insert into the set
set<Question> initialize_question(const string& file_name) {
    // Declare variables
    set<Question> q_set;
    string line;
    ifstream infile;

    // Open the file
    infile.open(file_name);
    while (getline(infile, line)) {
        Question q = get_question_factor(line);
        q_set.insert(q);
    }
    infile.close();

    return q_set;
}

// This function will display welcome message
// And get amount of questions that user want to answer
int get_amount() {
    int number_of_questions;
    cout << "Welcome to the Personality Quiz!" << endl << endl;
    cout << "Choose number of questions: " << endl;
    cin >> number_of_questions;
    return number_of_questions;
}

// This function will display selection menu
// Calculate the test result and display it
// exit when user input 0
void people_menu(map<char, int>& scores) {
    int choice = -1;
    while (choice != 0) {
        cout << "1. BabyAnimals" << endl;
        cout << "2. Brooklyn99" << endl;
        cout << "3. Disney" << endl;
        cout << "4. Hogwarts" << endl;
        cout << "5. MyersBriggs" << endl;
        cout << "6. SesameStreet" << endl;
        cout << "7. StarWars" << endl;
        cout << "8. Vegetables" << endl;
        cout << "9. mine" << endl;
        cout << "0. To end program." << endl << endl;
        cout << "Choose test number (1-9, or 0 to end):";
        cin >> choice;
        if (choice == 0)
            break;
        // Get the file name
        string file_name = get_file_name(choice);
        // use function to get people set
        set<Person> p_result = initialize_people(file_name);
        // Print the result
        get_result(p_result, scores);
    }
    cout << " Goodbye!" << endl;
}

// This function is to get the final result
// Then display the result
void get_result(set<Person> p_set, map<char, int> scores) {
    Person result = mostSimilarTo(scores, p_set);
    cout << " You got " << result.name << "!" << endl << endl;
}

// This function is to get the file name
// Use switch case to get the file name
string get_file_name(int choice) {
    string file_name;
    switch (choice) {
        case 1:
            file_name = "BabyAnimals.people";
            break;
        case 2:
            file_name = "Brooklyn99.people";
            break;
        case 3:
            file_name = "Disney.people";
            break;
        case 4:
            file_name = "Hogwarts.people";
            break;
        case 5:
            file_name = "MyersBriggs.people";
            break;
        case 6:
            file_name = "SesameStreet.people";
            break;
        case 7:
            file_name = "StarWars.people";
            break;
        case 8:
            file_name = "Vegetables.people";
            break;
        case 9:
            file_name = "mine.people";
    }
    return file_name;
}

// This function is to get the question set
// Use file name from switch case and open it
set<Person> initialize_people(const string& file_name) {
    // Declare variables
    set<Person> p_set;
    string line;
    ifstream infile;

    // Open the file and store the result
    infile.open(file_name);
    while (getline(infile, line)) {
        get_person_scores(line, p_set);
    }
    infile.close();
    return p_set;
}

// This function is to get scores from each person
// Use stringstream and erase to collect numbers and factors
// Use reference to store the result
void get_person_scores(const string& line, set<Person>& p_set) {
    // Declare variables
    Person p;
    char scores;
    int number;
    string temp, name;
    stringstream ss(line);

    // Get name
    getline(ss, name, '.');
    p.name = name;
    getline(ss, temp, ' ');
    // Get factors and scores
    while (getline(ss, temp, ' ')) {
        scores = temp[0];
        temp.erase(0, 2);
        number = stoi(temp);
        p.scores.emplace(scores, number);
    }
    p_set.insert(p);
}

// This function will display the question
// From the question set
// Gets back the user answer and return it
int display_questions(const Question& selected_question) {
    int answer;
    cout << "How much do you agree with this statement?" << endl;
    // cout selected question
    cout << "\"" << selected_question.questionText << ".\"" << endl << endl;
    cout << "1. Strongly disagree" << endl;
    cout << "2. Disagree" << endl;
    cout << "3. Neutral" << endl;
    cout << "4. Agree" << endl;
    cout << "5. Strongly agree" << endl << endl;
    cout << "Enter your answer here (1-5): " << endl;
    cin >> answer;
    return answer;
}

// Main function is the place to call all others functions
int main() {
    // Declare file name
    string question_file_name = "questions.txt";
    // Place to store user answers
    map<Question, int> answers;
    // Get number of questions from user
    int number_of_questions = get_amount();
    // initialize all questions at beginning
    set<Question> questions = initialize_question(question_file_name);
    // print out questions in range of number of questions
    for (int i = 0; i < number_of_questions; i++) {
        // temp is selected question
        Question temp = randomQuestionFrom(questions);
        // display the question, return answer back
        int answer = display_questions(temp);
        // store the answer
        answers.emplace(temp, answer);
    }
    // Calculate user final score before compare
    map<char, int> scores = scoresFrom(answers);
    // process to selection menu
    people_menu(scores);
    return 0;
}
