#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using namespace std;

bool ValidResponse(const string& response) {
    return response.size() == 1 && (response[0] == 'A' || response[0] == 'B' || response[0] == 'C' || response[0] == 'D');
}

void loadingBar(int width){
    cout << "\r";
    cout << "\t\t\t\t\t[";

    for (int i = 0; i < 20; i++) {
        cout << "=" << flush;

        this_thread::sleep_for(chrono::milliseconds(80)); //use to set the time to flush in the "="
    }
    cout << "] 100%" << endl;
}


void Test_Result() {
    const int numQuestions = 13; // Update this with the correct number of questions
    const int numAnswers = 4;
    int score = 0;
    string response, stress_level;

    string questions[numQuestions]= {
            "Question 1: How often do you feel overwhelmed or unable to cope with your daily responsibilities?",
            "Question 2: How often do you experience physical symptoms of stress such as headaches or muscle tension?",
            "Question 3: How often do you feel anxious or worried?",
            "Question 4: How often do you experience feelings of hopelessness or despair?",
            "Question 5: How often do you feel disconnected from others like family and friends?",
            "Question 6: How often do you turn to unhealthy habits such as drinking or smoking to cope with stress?",
            "Question 7: How often do you find it difficult to stay focused and concentrated on your work during the day?",
            "Question 8: How frequently do you feel like you're not living up to your own expectations or standards?",
            "Question 9: How often do you experience difficulty concentrating or making decisions?",
            "Question 10: How often do you experience tension or conflict with coworkers or family members?",
            "Question 11: How often do you feel like your stress levels are impacting your physical health?",
            "Question 12: How often do you feel like you need a break from your daily routine in order to reduce stress?",
            "Question 13: Have you ever thought about suicide?"
    };

    string options[numAnswers] = {
        "Never", "Rarely", "Several times a week", "Almost Everyday"
    };

    string answers[numQuestions][numAnswers];

    // Initializing all answers with the same options
    for (int i = 0; i < numQuestions; ++i) {
        for (int j = 0; j < numAnswers; ++j) {
            answers[i][j] = options[j];
        }
    }

    cout<< "+------------------------+\n"
        << "| Test Your Stress Level |\n"
        << "+------------------------+\n"
        << "This quiz is NOT a diagnostic tool.\n"
        << endl << endl;
    for (int i = 0; i < numQuestions; ++i) {
    string response;

        // Displaying the original questions and getting user responses
        cout << questions[i] << endl;
        for (int j = 0; j < numAnswers; ++j) {
            cout << "  " << char('A' + j) << ". " << answers[i][j] << endl;
        }

        // Validate and process the user's response
        bool validResponse = false;
        while (!validResponse) {
            cout << "Enter your answer (A, B, C, or D): ";
            getline(cin, response);
            cout << endl;

            // Convert the response to uppercase
            for (char& c : response) {
                c = toupper(c);
            }

            if (ValidResponse(response)) {
                validResponse = true;
            } else {
                cout << "Invalid input. Please enter A, B, C, or D." << endl;
            }
        }

        // Process the response and update the score
        if (response[0] == 'A') {
            score += 0;
        } else if (response[0] == 'B') {
            score += 1;
        } else if (response[0] == 'C') {
            score += 2;
        } else if (response[0] == 'D') {
            score += 3;
        }
    }

    // ... (your existing code for loading bar)

    cout << "Completed. Waiting for your result";
    loadingBar(50);
    cout << endl;

    ofstream write_result;
    write_result.open ("Std_testlevel.txt", ios::app);

    if (score <= 14) {
        cout << "+-----------------------------------------------------------------------------------------------------------------+\n"
             << "|Your stress level is low.                                                                                        |\n"
             << "|You are cool, calm and collected.                                                                                |\n"
             << "|You really have a handle on coping with stress. If you begin to see changes in your life,                        |\n"
             << "|you may try maintain this level by discovering sources of stress that you can eliminate.                         |\n"
             << "+-----------------------------------------------------------------------------------------------------------------+"
             << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)";
             stress_level = "low";
    } else if (score > 14 && score <= 25) {
        cout << "+-----------------------------------------------------------------------------------------------------------------+\n"
             << "|Your stress level is moderate.                                                                                   |\n"
             << "|You definitely have some stress going on.                                                                        |\n"
             << "|You probably have enough coping skills for stress as well.                                                       |\n"
             << "|Find ways to relieve your stress by discovering sources of stress that you can eliminate                         |\n"
             << "|and also by including effective strategies like physical activity, breathing exercises or music.                 |\n"
             << "+-----------------------------------------------------------------------------------------------------------------+"
             << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)";
             stress_level = "moderate";
    } else {
        cout << "+-----------------------------------------------------------------------------------------------------------------+\n"
             << "|Your stress level is high.                                                                                       |\n"
             << "|There is way too much stress going on in your life.                                                              |\n"
             << "|Take steps to reduce and manage your stress now.                                                                 |\n"
             << "|Find ways to relieve your stress by discovering sources of stress that you can eliminate                         |\n"
             << "|and also by including effective strategies like physical activity, breathing exercises or music.                 |\n"
             << "|If you think you may be suffering from stress, anxiety, or any other medical health condition,                   |\n"
             << "|We strongly recommends that you seek help from a mental health professional                                      |\n"
             << "|in order to receive a proper diagnosis and support.                                                              |\n"
             << "+-----------------------------------------------------------------------------------------------------------------+"
             << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)";
             stress_level = "high";
    }

    write_result << " "/*Idnum*/<< " " << " "/*name*/ << " " << score << " " << stress_level << endl << endl;
    write_result.close();
}

int main() {
int barWidth = 50;

    system("color E4"); //to change the whole background colour
    cout << "\n\n\n\n\t\t\t\t\tLoading...\n\n";
    loadingBar(barWidth); // called function
   // Stress_Test(); // called function
    Test_Result(); // called function

return 0;
}
