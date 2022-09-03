// FileName: driver.h
// Description: Driver for the program personality tests
// Name: Haoji Ni
// UIC CS251 Spring 2022
// Date: 1/27/2022

#include <cmath>
#include <limits>
#include <string>
#include <map>
#include <set>
#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;  // Text of the question
    map<char, int> factors;   // Map from factors to +1 or -1
    friend bool operator< (const Question& lhs, const Question& rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator== (const Question& lhs, const Question& rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator!= (const Question& lhs, const Question& rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;      // Name of the person
    map<char, int> scores;  // Map from factors to +1 or -1
    friend bool operator< (const Person& lhs,   const Person& rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator== (const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator!= (const Person& lhs, const Person& rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
*/
Question randomElement(set<Question>& questions) {
    int ind = randomInteger(0, (int)questions.size()-1);
    int i = 0;

    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

// This function will get a random question from unasked questions
// Remove the question from unasked questions and return it
Question randomQuestionFrom(set<Question>& questions) {
    // If questions set is empty, throw error
    if (questions.empty()) {
        throw runtime_error("set: empty");
    }

    Question temp = randomElement(questions);
    // If temp is exist in unasked questions, remove it
    if (questions.count(temp) > 0) {
        questions.erase(temp);
    }
    return temp;
}

// This function will compute the score of a person
// Return OCEAN scores in form of map<char,int>
map<char, int> scoresFrom(map<Question, int>& answers) {
    map<char, int> scores;

    for (auto& e : answers) {
        for (auto& f : e.first.factors) {
            // calculate the scores of each factor
            scores[f.first] += (e.second-3) * f.second;
        }
    }
    return scores;
}



// This function will calculate length of vector
// Store in a map and return it
map<char, double> normalize(const map<char, int>& scores) {
    // Declare variables
    map<char, double> normalize;
    double length_of_vector = 0;
    int i = 0;
    int j = 0;

    for (auto& e : scores) {
        if (e.second == 0)
            j++;
        length_of_vector += pow(e.second, 2);
        i++;
    }
    // If all scores are 0, throw error
    if (i == j)
        throw runtime_error("invalid input");
    length_of_vector = sqrt(length_of_vector);

    for (auto& e : scores) {
        normalize[e.first] = e.second / length_of_vector;
    }
    return normalize;
}

// This function will calculate similarity
// Between two normalized scores
// Return the result as a double
double cosineSimilarityOf(const map<char, double>& lhs,
                          const map<char, double>& rhs) {
    double similarity = 0;
    // Loop through each element to calculate similarity
    for (auto &e : lhs) {
        if (rhs.count(e.first) > 0)
            similarity += e.second * rhs.at(e.first);
    }
    return similarity;
}

// This function will find the best match
// By getting raw score and set of people
// Return Person
Person mostSimilarTo(map<char, int>& scores, set<Person>& people) {
    // If is empty, throw error
    if (people.empty()) {
        throw runtime_error("set: empty");
    }

    // Declare variables
    double max_similarity = lowest_double;
    map<char, double> normalized = normalize(scores);
    Person result;
    map<char, double> normalized_person;
    for (auto& e : people) {
        // Normalize scores of each person first
        normalized_person = normalize(e.scores);
        // Calculate similarity
        double similarity = cosineSimilarityOf(normalized, normalized_person);
        // If similarity is greater than max_similarity, update result
        if (similarity > max_similarity) {
            max_similarity = similarity;
            result = e;
        }
    }
    return result;
}
