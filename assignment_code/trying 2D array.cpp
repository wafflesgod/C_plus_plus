#include <iostream>
#include <string>

using namespace std;

int main() {
    const int numQuestions = 3;
    const int numAnswers = 3;

    // Questions
    string questions[numQuestions] = {
        "Question 1: How would you rate your stress level?",
        "Question 2: How satisfied are you with your work-life balance?",
        "Question 3: How often do you engage in physical exercise?"
    };

    // Answer options for each question
    string options[numQuestions][numAnswers] = {
        { "Low", "Medium", "High" },               // Options for Question 1
        { "Not satisfied", "Moderately satisfied", "Very satisfied" }, // Options for Question 2
        { "Rarely", "Regularly", "Daily" }         // Options for Question 3
    };

    // User responses
    string userResponses[numQuestions];

    // Display questions and get user responses
    for (int i = 0; i < numQuestions; ++i) {
        cout << questions[i] << endl;

        for (int j = 0; j < numAnswers; ++j) {
            cout << "  " << char('A' + j) << ". " << options[i][j] << endl;
        }

        cout << "Enter your answer (A, B, or C): ";
        getline(cin, userResponses[i]);
        cout << endl;
    }

    // Display user responses
    cout << "User Responses:" << endl;
    for (int i = 0; i < numQuestions; ++i) {
        cout << questions[i] << ": " << userResponses[i] << endl;
    }

    return 0;
}

