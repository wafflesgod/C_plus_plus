#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (){
    int enterIdnum;
    string enterpassword;
    int storedStudentID;
    string storedName, storedGender, storedDateofbirth, storedCourse;

    ifstream outuser("Std_users.txt"); //output user file
    //outuser.open("Std_users.txt");

    outuser >> storedStudentID >> storedName >> storedGender >> storedDateofbirth >> storedCourse;
    cout << "Student ID: " << storedStudentID << endl;
    cout << "Name: " << storedName << endl;
    cout << "Gender: " << storedGender << endl;
    cout << "Date of birth: " << storedDateofbirth << endl;
    cout << "Course: " << storedCourse << endl;
    outuser.close();
    
    return 0;
}
//04041829