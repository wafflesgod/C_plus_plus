#include <iostream>
#include <fstream>

using namespace std;

int main (){
    string enterIdnum;
    string storedStudentID;
    string storedUsername, storedPassword, storedGender, storedDateOfBirth, storedCourse;
    string Idnum, name, password, gender, dateofbirth, course;
    string enterpassword;

        cout << "Enter Student_ID: ";
        cin >> Idnum; //set the length of studentid if can

        cout << "Enter your name(can't put space // put _ as space): ";
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
        //UpperCase(course);

        while (!(course == "FIST" || course == "FET" || course == "FOB" || course == "FOL")) {
            cout << "Invalid course input. Please enter FIST, FET, FOB, or FOL.\n";
            cout << "Enter your course [FIST, FET, FOB, FOL]: ";
            cin >> course;
            //UpperCase(course);
        }

        cout << "Valid course input.\n";

        ofstream outFile("Std_users.txt", ios::app); //open file for writing, for input
        ofstream writepass("student_password.txt", ios::app); 

    ifstream outuser("Std_users.txt"); //output user file

    while (outuser >> storedStudentID >> storedUsername >> storedGender >> storedDateOfBirth >> storedCourse) {
        if (storedStudentID == enterIdnum) {
            cout << "Student ID: " << storedStudentID << endl;
            cout << "Name: " << storedUsername << endl;
            cout << "Gender: " << storedGender << endl;
            cout << "Date of birth: " << storedDateOfBirth << endl;
            cout << "Course: " << storedCourse << endl;
            break;
        } else if(storedStudentID != enterIdnum) {
            cout << "Student ID 1: " << Idnum << endl;
            cout << "Name: " << name << endl;
            cout << "Gender: " << gender << endl;
            cout << "Date of birth: " << dateofbirth << endl;
            cout << "Course: " << course << endl;
            break;
        } 
    }

    outuser.close();
    
    return 0;
}