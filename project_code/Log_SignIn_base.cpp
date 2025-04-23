#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ios>
#include <sstream>

using namespace std;

void displayMenusignUp() {
    string username, password, studentID, dateofbirth, Course;

    cout << "Enter Student_ID: ";
    cin >> studentID;

    cout << "Enter your name: ";
    cin >> username;

    string defaultPassword = "default123";
    string enteredPassword, reenteredPassword;
    cout << "Create a new password:\n";
    cin >> enteredPassword;
    cout << "Re-enter the password:\n";
    cin >> reenteredPassword;

    while (enteredPassword != reenteredPassword) {
        cout << "Passwords do not match. Please try again.\n";
        cout << "Create a new password:\n";
        cin >> enteredPassword;
        cout << "Re-enter the password:\n";
        cin >> reenteredPassword;
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

    if (gender == 'F' || gender == 'f') {
        cout << "Female\n";
    } else {
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
    cin >> Course;

    while (!(Course == "FIST" || Course == "FET" || Course == "FOB" || Course == "FOL")) {
        cout << "Invalid course input. Please enter FIST, FET, FOB, or FOL.\n";
        cout << "Enter your course [FIST, FET, FOB, FOL]: ";
        cin >> Course;
    }

    cout << "Valid course input.\n";

    ofstream outFile("users.txt", ios::app);

    if (outFile.is_open()) {
        outFile << studentID << " " << username << " " << password << " " << gender << " " << dateofbirth << " " << Course << endl;
        outFile.close();
        cout << "Sign-up successful!\n";
    } else {
        cout << "Error opening file for sign-up.\n";
    }
}

void login() {
    string username, password;

    cout << "Enter Student_ID: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream inFile("users.txt");
    string storedStudentID, storedUsername, storedPassword, storedGender, storedDateOfBirth, storedCourse;

    while (inFile >> storedStudentID >> storedUsername >> storedPassword >> storedGender >> storedDateOfBirth >> storedCourse) {
        if (storedStudentID == username && storedPassword == password) {
            cout << "Login successful!\n";
            return;
        }
    }

    cout << "Login failed. Invalid username or password.\n";
}

int main() {
    string word = "WELCOME TO OUR SYSTEM!"; // Replace this with your desired word
    int boxWidth = word.length() + 4;        // Adjust based on the length of the word
    cout << "*" << setw(boxWidth) << setfill('-') << "*" << setfill(' ') << endl;
    cout << "| " << word << " |" << endl;
    cout << "*" << setw(boxWidth) << setfill('-') << "*" << setfill(' ') << endl;

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

    if (action == 'l' || action == 'L') {
        login();
    } else if (action == 's' || action == 'S') {
        displayMenusignUp();
    }

    return 0;
}
