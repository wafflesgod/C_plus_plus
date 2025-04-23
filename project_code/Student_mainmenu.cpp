#include <iostream>
#include <fstream>
#include <cstdlib> // for system("clear") or system("cls")
#include <limits>
#include <string>
#include <thread>
#include <iomanip>
#include <ios>
#include <sstream>

using namespace std;

void clearScreen() { 
#ifdef _WIN32
    system("cls");
    system("color 07");
#else
    system("clear");
#endif
}

void welcome(){
        cout<<"  //  /////// ///  /////  //  //////////  ///        /////////  ////////////  /////////////// //////////"<<endl;
        cout<<"   //  ///// // //  ///  //   //          ///        //         //        //  //    //    //  //       "<<endl;
        cout<<"    //  /// //  //  //  //    /////////   ///        //         //        //  //    //    //  //////////"<<endl;
        cout<<"     // // //   //  /  //     /////////   ///        //         //        //  //    //    //  //////////"<<endl;
        cout<<"      /   //    //   //       //          ///        //         //        //  //    //    //  //       "<<endl;
        cout<<"       ///       ////         /////////   /////////  /////////  ////////////  //    //    //  //////////"<<endl;
}

int getValidChoice(int min, int max) {
    int choice;
    while (true) { //loop will continues until user enter a valid choice
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < min || choice > max) {
            //cin.fail: when the user enters a non integer value, the input operation failed
            // choice < min || choice > max: if the user entered choice is outside the specified range, it means the input is invalid.
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl; // Clear the error state to allow further input attempts
            cin.clear();  // Clears the error state of the input stream to allow further input attempts.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
            // '\n': preventing the program from getting stuck in a loop due to invalid input.
        } else {
            break;
        }
    }
    return choice;
}

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

void UpperCase(string& upcase) { // Function to convert string to uppercase
    for (char& c : upcase) {
        c = toupper(c);
    }
}

void Enter() {
    cout << "Press Enter to continue...";
    cin.ignore();  // Wait for Enter key
    cin.get();     // Clear the newline character
}

class Student{
    private:
        int Idnum; //studentid

    public:
        string name, password, dateofbirth, course;
        char gender;
        string enterIdnum;
        //int storedStudentID;
        string storedStudentID, storedUsername, storedPassword, storedGender, storedDateOfBirth, storedCourse;
        string storedScore, storedStress_Level;

        Student(int id, string password = "default123"): Idnum(id) {
            //display id for testing
            //cout << "ID: " << Idnum << endl;
            //cout << "password: " <<  password; //overloaded
        }

    void displayMenusignUp(){
        cout << "Enter Student_ID: ";
        cin >> Idnum; //set the length of studentid if can

        cout << "Enter your name: ";
        cin >> name;

        string tmp_password; 

        cout << "Do you want to use the default password? (y/n): ";
        char Default;
        cin >> Default;

        if (Default == 'n' || Default == 'N') {
            cout << "Create a new password:\n";
            cin >> tmp_password;

            cout << "Re-enter the password:\n";
            cin >> password;

            while (tmp_password != password) {
                cout << "Passwords do not match. Please try again.\n";
                cout << "Create a new password:\n";
                cin >> tmp_password;
                cout << "Re-enter the password:\n";
                cin >> password;
            }
        } else {
            password = "default123";
            cout << "Your default password is " << password << "." << endl;
        }
        cout << "Password set successfully!\n";

        char gender;
        cout << "Enter Gender [F/M]: ";
        cin >> gender;

        // Validate input (optional)
        while (!(gender == 'F' || gender == 'f' || gender == 'M' || gender == 'm')) {
            cout << "Invalid gender input. Please enter F or M.\n";
            cout << "Enter Gender [F/M]: ";
            cin >> gender;
        }

        if (gender == 'F' || gender == 'f')
            cout << "Female\n";
        else {
            cout << "Male\n";
        }

        cout << "Enter your Date of birth (ddmmyy): ";
        cin >> dateofbirth;

        while (dateofbirth.size() != 6) {
            cout << "Invalid Date_of birth input. Please enter exactly 6 characters.\n";
            cout << "Enter your Date of birth (ddmmyy): ";
            cin >> dateofbirth;
        }

        cout << "Valid Date_of birth input.\n";
        
        cout << "Enter your course [FIST, FET, FOB, FOL]: ";
        cin >> course;
        UpperCase(course);

        while (!(course == "FIST" || course == "FET" || course == "FOB" || course == "FOL")) {
            cout << "Invalid course input. Please enter FIST, FET, FOB, or FOL.\n";
            cout << "Enter your course [FIST, FET, FOB, FOL]: ";
            cin >> course;
            UpperCase(course);
        }
        cout << "Valid course input.\n";

        ofstream outFile("Std_users.txt", ios::app); //open file for writing, for input
        ofstream writepass("student_password.txt", ios::app); 

        if (outFile.is_open()) {
            outFile << Idnum << " " << name << " " << gender << " " << dateofbirth << " " << course << endl;
            outFile.close();
            cout << "Sign-up successful!\n";
        } else {
            cout << "Error opening file for sign-up.\n";
        }
            
        if (writepass.is_open()) {
            writepass << Idnum << " " << name << " " << password << endl;
            writepass.close();
            cout << "Password recorded!\n";
        } else {
            cout << "Error opening file for password.\n";
        }
    }

    bool login(){
        string enterpassword;
        cout << "Enter Student_ID: ";
        cin >> enterIdnum;

        cout << "Enter password: ";
        cin >> enterpassword;

        ifstream read("student_password.txt"); //open the file for reading, for output

        bool loginSuccessful = false; //for tracking the login success or not

        while (read >> storedStudentID >> storedUsername >> storedPassword) {
            if (storedStudentID == enterIdnum && storedPassword == enterpassword) {
                cout << "Your name is " << storedUsername << endl;
                cout << "Login successful!\n";
                loginSuccessful = true;
                break;
            } 
        }
        
        if (!loginSuccessful){
            cout << "Login failed. Invalid username or password.\n";
        }

        read.close();
        return loginSuccessful;
    }

    /*bool LoginSuccessful() const {
        return loginSuccessful;
    }*/

    void Std_checkinfo() {
        ifstream outuser("Std_users.txt"); //output user file
        //outuser.open("Std_users.txt");

        while (outuser >> storedStudentID >> storedUsername >> storedGender >> storedDateOfBirth >> storedCourse) {
            if (storedStudentID == enterIdnum) {
                cout << "Student ID: " << storedStudentID << endl;
                cout << "Name: " << storedUsername << endl;
                cout << "Gender: " << storedGender << endl;
                cout << "Date of birth: " << storedDateOfBirth << endl;
                cout << "Course: " << storedCourse << endl;
                break;
            } 
        }

        outuser.close();
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
                UpperCase(response);
                cout << endl;

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

        cout << "Completed. Waiting for your result";

        //loadingBar(50);
        cout << endl;

        if (score <= 14) {
            cout << "+-----------------------------------------------------------------------------------------------------------------+\n"
                << "|Your stress level is low.                                                                                        |\n"
                << "|You are cool, calm and collected.                                                                                |\n"
                << "|You really have a handle on coping with stress. If you begin to see changes in your life,                        |\n"
                << "|you may try maintain this level by discovering sources of stress that you can eliminate.                         |\n"
                << "+-----------------------------------------------------------------------------------------------------------------+"
                << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)\n";
                stress_level = "low";
                Enter();
        } else if (score > 14 && score <= 25) {
            cout << "+-----------------------------------------------------------------------------------------------------------------+\n"
                << "|Your stress level is moderate.                                                                                   |\n"
                << "|You definitely have some stress going on.                                                                        |\n"
                << "|You probably have enough coping skills for stress as well.                                                       |\n"
                << "|Find ways to relieve your stress by discovering sources of stress that you can eliminate                         |\n"
                << "|and also by including effective strategies like physical activity, breathing exercises or music.                 |\n"
                << "+-----------------------------------------------------------------------------------------------------------------+"
                << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)\n";
                stress_level = "moderate";
                Enter();
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
                << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)\n";
                stress_level = "high";
                Enter();
        }

        //ofstream write_result("Std_testlevel.txt", ios::app);
        //ifstream outuser("Std_users.txt");
        ifstream readexisting("Std_testlevel_1.txt");
        ofstream write_result("Std_testlevel_1.txt", ios::app);

        bool userExists = false;

        // Check if the student already has a test result recorded
        while (readexisting >> storedStudentID >> storedUsername >> storedScore >> storedStress_Level) {
            if (storedStudentID == enterIdnum) {
                userExists = true;
                break;
            }
        }

        readexisting.close();

        // Open the file in append mode to add or update the test result
        ofstream write_result("Std_testlevel_1.txt", ios::app);

        if (userExists) {
            // Update the existing user's test result
            while (readexisting >> storedStudentID >> storedUsername >> storedScore >> storedStress_Level) {
                if (storedStudentID == enterIdnum) {
                    // Update the result
                    write_result << storedStudentID << " " << storedUsername << " " << score << " " << stress_level << endl;
                    break;
                }
            }
        } else {
            // Add a new entry for the user
            write_result << enterIdnum << " " << storedUsername << " " << score << " " << stress_level << endl;
        }

        write_result.close();
    }
};

int main(){
    int choice;
    int barWidth = 50;

    welcome();

    char userType;
    cout << "Are you a student (s) or a counselor (c)? ";
    cin >> userType;

    while (!(userType == 's' || userType == 'S' || userType == 'c' || userType == 'C')) {
        cout << "Invalid user type. Please enter 's' or 'c'.\n";
        cout << "Are you a student (s) or a counselor (c)? ";
        cin >> userType;
    }

    char action;
    cout << "Log in (l) or Sign up (s)? ";
    cin >> action;

    while (!(action == 'l' || action == 'L' || action == 's' || action == 'S')) {
        cout << "Invalid action. Please enter 'l' or 's'.\n";
        cout << "Log in (l) or Sign up (s)? ";
        cin >> action;
    }

    //Create an instance of the Student class
    Student student(123); //for trigger the void inside the class

    if (action == 'l' || action == 'L') {
        bool loginSuccessful = student.login();

        // Check if the login was successful before proceeding to the menu
        if (!loginSuccessful) {
            cout << "Login failed. Exiting the program.\n";
            return 1; // Exit the program with an error code
        }
    } else if (action == 's' || action == 'S') {
        student.displayMenusignUp();
    }
    Enter();

    do {
        clearScreen();
        
        cout << "\n\t\t\t\t\tTo our stress test system\n"
            << "\t\t\t\t+------------------------------------------+\n"
            << "\t\t\t\t|           STRESS TEST SYSTEM             |\n"
            << "\t\t\t\t|------------------------------------------|\n"
            << "\t\t\t\t|         1. Check Personal Info           |\n"
            << "\t\t\t\t|         2. Test Your Stress Level        |\n"
            << "\t\t\t\t|         3. Exit                          |\n"
            << "\t\t\t\t+------------------------------------------+\n";
            //<< "\t\t\t\t\tEnter your option(1-3): ";
        
        choice = getValidChoice(1,3);

        // Clear the newline character from the buffer // to fix the auto nextline (getline function)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        switch (choice) {
            case 1:
                cout << "You selected Option A." << endl;
                student.Std_checkinfo();
                Enter();
                break;
            case 2:
                clearScreen();
                cout << "You selected Option B." << endl;
                //int barWidth = 50;
                system("color E4"); //to change the whole background colour
                cout << "\n\n\n\n\t\t\t\t\tLoading...\n\n";
                //student.loadingBar(barWidth); // called function
                student.Test_Result(); // called function
                break;
            case 3:
                // Return to the main menu
                break;
            default:
                cout << "\nInvalid choice. Please enter a number between 1 and 3." << endl;
        }
    } while (choice != 3);

    return 0;
}
