#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ios>
#include <sstream>

//u can change password in txt file
//the start of void, class, file handling (red point)

using namespace std;

// Function to convert string to uppercase
void UpperCase(string& upcase) {
    for (char& c : upcase) {
        c = toupper(c);
    }
}

class Student{
    private:
        int Idnum; //studentid

    public:
        string name, password, dateofbirth, course;
        char gender;

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

    void login(){
        int enterIdnum;
        string enterpassword;
        cout << "Enter Student_ID: ";
        cin >> enterIdnum;

        cout << "Enter password: ";
        cin >> enterpassword;

        ifstream read("student_password.txt"); //open the file for reading, for output

        int storedStudentID;
        string storedName, storedPassword;

        bool loginSuccessful = false; //for tracking the login success or not

        while (read >> storedStudentID >> storedName >> storedPassword) {
            if (storedStudentID == enterIdnum && storedPassword == enterpassword) {
                cout << "Your name is " << storedName << endl;
                cout << "Login successful!\n";
                loginSuccessful = true;
                break;
            } 
        }
        
        if (!loginSuccessful){
            cout << "Login failed. Invalid username or password.\n";
        }
        read.close();
    }
};


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

    //Create an instance of the Student class
    Student student(123); //for trigger the void inside the class
    //student.displayMenusignUp(); (for testing)

    if (action == 'l' || action == 'L') {
        student.login();
    } else if (action == 's' || action == 'S') {
        student.displayMenusignUp();
    }

    return 0;
}
/*//Update the IDs (not used yet, not idea)
    int newID;
    cout << "Enter ur ID: ";
    cin >> newID;
    s1.setIdnum(newID);
    cout << "Enter ur ID: ";
    cin >> newID;
    s2.setIdnum(newID);*/