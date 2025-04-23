#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Counselor{
    private:
        int CounselorId;
        string C_password;
    public:
        string username, r_num;
        int p_num;

    Counselor (int c_id = 0, string c_pass = "nothing"): CounselorId(c_id), C_password(c_pass) {
        // display both for testing
        //cout << "ID: " << CounselorId << endl;
        //cout << "password: " << C_password << endl;
    } 

    void try_1(){
        cout << "You are checking all student's information" << endl;

        ifstream read_std; //file handling must run in function
        read_std.open("Std_users.txt");
        
        string storedStudentID, storedUsername, storedGender, storedDateOfBirth, storedCourse;

        while (read_std >> storedStudentID >> storedUsername >> storedGender >> storedDateOfBirth >> storedCourse) {
            cout << "Student ID: " << storedStudentID << endl;
            cout << "Username: " << storedUsername << endl;
            cout << "Gender: " << storedGender << endl;
            cout << "Date of Birth: " << storedDateOfBirth << endl;
            cout << "Course: " << storedCourse << endl << endl;
        }

        if (!read_std.is_open()) {
            cout << "Error opening file for reading." << endl; // Handle the error as needed
        }

        read_std.close();
    }

    void try_2(){
        string entercourse;
        cout << "You are checking all student's infomation by course" << endl;
        cout << "Enter a course: ";
        cin >> entercourse;

        ifstream read_std("Std_users.txt");

        string storedStudentID, storedUsername, storedGender, storedDateOfBirth, storedCourse;

        while (read_std >> storedStudentID >> storedUsername  >> storedGender >> storedDateOfBirth >> storedCourse) {
            if(storedCourse == entercourse){
                cout << "Student ID: " << storedStudentID << endl;
                cout << "Username: " << storedUsername << endl;
                cout << "Gender: " << storedGender << endl;
                cout << "Date of Birth: " << storedDateOfBirth << endl;
                cout << "Course: " << storedCourse << endl << endl;
             }   
        }

        read_std.close();
    }

    void try_3(){
        string enterStress_level;
        cout << "You are checking all student's infomation by stress zone" << endl;
        cout << "Enter a stress zone: ";
        cin >> enterStress_level;

        ifstream read_testlevel("Std_testlevel.txt");

        string storedStudentID, storedUsername, storedScore, storedStress_level;

        while (read_testlevel >> storedStudentID >> storedUsername  >> storedScore >> storedStress_level) {
            if(storedStress_level == enterStress_level){
                cout << "Student ID: " << storedStudentID << endl;
                cout << "Username: " << storedUsername << endl;
                cout << "Score: " << storedScore << endl;
                cout << "Stress level: " << storedStress_level << endl << endl;
             }   
        }

        read_testlevel.close();
    }

    void try_4(){
        string enterStudentID;
        int choice;
        string new_StudentID, new_Username, new_Gender, new_DateOfBirth, new_Course;
        cout << "You are editing student's information" << endl;
        cout << "Enter a Student ID: ";
        cin >> enterStudentID;

        ifstream read("Std_users.txt");
        ofstream edit("temp.txt", ios::in | ios::app); //open a temporary file to write
        
        if (!read.is_open() || !edit.is_open()) {
            cout << "Error opening file for reading or writing." << endl;
            return;
        }

        string storedStudentID, storedUsername, storedGender, storedDateOfBirth, storedCourse;

        while (read >> storedStudentID >> storedUsername >> storedGender >> storedDateOfBirth >> storedCourse) {
        if (storedStudentID == enterStudentID) {
            cout << "1. Student ID: " << storedStudentID << endl;
            cout << "2. Username: " << storedUsername << endl;
            cout << "3. Gender: " << storedGender << endl;
            cout << "4. Date of Birth: " << storedDateOfBirth << endl;
            cout << "5. Course: " << storedCourse << endl << endl;

            cout << "Which record do you want to edit?" << endl;
            cout << "Enter your option (1-5): ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "Enter a new Student ID: ";
                    cin >> new_StudentID;
                    edit << new_StudentID << " " << storedUsername << " " << storedGender << " " << storedDateOfBirth << " " << storedCourse << endl;
                    break;
                }
                case 2: {
                    cout << "Enter a new Username: ";
                    cin >> new_Username;
                    edit << storedStudentID << " " << new_Username << " " << storedGender << " " << storedDateOfBirth << " " << storedCourse << endl;
                    break;
                }
                case 3: {
                    cout << "Enter a new Gender: ";
                    cin >> new_Gender;
                    edit << storedStudentID << " " << storedUsername << " " << new_Gender << " " << storedDateOfBirth << " " << storedCourse << endl;
                    break;
                }
                case 4: {
                    cout << "Enter a new Date of Birth: ";
                    cin >> new_DateOfBirth;
                    edit << storedStudentID << " " << storedUsername << " " << storedGender << " " << new_DateOfBirth << " " << storedCourse << endl;
                    break;
                }
                case 5: {
                    cout << "Enter a new Course: ";
                    cin >> new_Course;
                    edit << storedStudentID << " " << storedUsername << " " << storedGender << " " << storedDateOfBirth << " " << new_Course << endl;
                    break;
                }
                default:
                    cout << "Invalid option." << endl;
                    return;
            }
        } else {
            // Write the existing data to the temporary file
            edit << storedStudentID << " " << storedUsername << " " << storedGender << " " << storedDateOfBirth << " " << storedCourse << endl;
        }
    }

        // Write the modified data to the temporary file
        //edit << new_StudentID << " " << new_Username << " " << new_Gender << " " << new_DateOfBirth << " " << new_Course << endl;

        read.close();
        edit.close();

        // Replace the original file with the temporary file
        remove("Std_users_1.txt");
        rename("Temp.txt", "Std_users_1.txt");

    }

};
    
int main () {
    Counselor counselor(123, "ali"); // as trigger for class
    counselor.try_1();
    counselor.try_2();
    counselor.try_3();
    counselor.try_4();

    return 0;
}
