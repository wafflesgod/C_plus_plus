#include <iostream> //console input/output
#include <fstream> //file input/output
#include <cstdlib> // for system("clear") or system("cls")
#include <limits> //numeric type limits
#include <string> //string manipulation
#include <thread> //allow creation of multiple threads within a program
#include <iomanip> //for setting field width, precision...
#include <ios> //helps in handling state of I/O streams during operations
#include <sstream> //string stream operations

using namespace std;

void clearScreen() { 
#ifdef _WIN32
    system("cls");
    system("color 07"); //change back to default color
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

bool ValidResponse(const string& response) { //used for boolean operation
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

void LowerCase(string& lowercase) {
    for (char& c : lowercase) {
        c = tolower(c);
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
        string storedStudentID, storedUsername, storedPassword, storedGender, storedDateOfBirth, storedCourse;
        

        Student(int id, string password = "default123"): Idnum(id) {
            //display id for testing
            //cout << "ID: " << Idnum << endl;
            //cout << "password: " <<  password; //overloaded
        }

    void displayMenusignUp(){
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
        int maxattempts = 3;

        cout << "Enter Student_ID: ";
        cin >> enterIdnum;

        cout << "Enter password: ";
        cin >> enterpassword;

        ifstream read("student_password.txt"); //open the file for reading, for output

        bool loginSuccessful = false; //for tracking the login success or not

        for (int attempts = 0; attempts < maxattempts ; attempts++) {
            bool found = false; //to match username and password
            while (read >> storedStudentID >> storedUsername >> storedPassword) {
                if (storedStudentID == enterIdnum && storedPassword == enterpassword) {
                    cout << "Your name is " << storedUsername << endl;
                    cout << "Login successful!\n";
                    loginSuccessful = true;
                    found = true;
                    break;
                } 
            }

            //read the file from beginning
            read.clear(); //clear the end-of-file flag
            read.seekg(0, ios::beg); //reset the file pointer to the beginning

            if (!found){
                cout << "Login failed. Invalid username or password.\n\n";
                if (attempts < maxattempts -1) {
                    cout << "Enter password again: ";
                    cin >> enterpassword;
                }
            } else {
                break; //break out of the outer loop if login is successful
            }
        }

        if (!loginSuccessful){
            cout << "Access denied.\n";
        }

        read.close();
        
        return loginSuccessful;
    }

    void Std_checkinfo() {
        ifstream outuser("Std_users.txt"); //output user file

        bool studentFound = false;

        while (outuser >> storedStudentID >> storedUsername >> storedGender >> storedDateOfBirth >> storedCourse) {
            if (storedStudentID == enterIdnum) {
                cout << "Student ID: " << storedStudentID << endl;
                cout << "Name: " << storedUsername << endl;
                cout << "Gender: " << storedGender << endl;
                cout << "Date of birth: " << storedDateOfBirth << endl;
                cout << "Course: " << storedCourse << endl;
                
                studentFound = true;
            } 
        }

        outuser.close();

        if(!studentFound){
            cout << "Student ID 1: " << Idnum << endl;
            cout << "Name: " << name << endl;
            cout << "Gender: " << gender << endl;
            cout << "Date of birth: " << dateofbirth << endl;
            cout << "Course: " << course << endl;
        }
    }

    void Test_Result() { 
        const int numQuestions = 13; // Update this with the correct number of questions
        const int numAnswers = 4;
        int score = 0;
        string storedScore, storedStress_Level, storedZone;
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

        cout << "\n\n\n\n\t\t\t\t\tLoading...\n\n";
        loadingBar(50);
        cout << endl;

        if (score <= 14) {
            cout << "+-----------------------------------------------------------------------------------------------------------------+\n"
                << "|Your stress level is low.                                                                                        |\n"
                << "|You are cool, calm and collected.                                                                                |\n"
                << "|You really have a handle on coping with stress. If you begin to see changes in your life,                        |\n"
                << "|you may try maintain this level by discovering sources of stress that you can eliminate.                         |\n"
                << "+-----------------------------------------------------------------------------------------------------------------+"
                << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)\n\n";
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
                << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)\n\n";
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
                << "\n(It's crucial to remember that only qualified mental health professionals can provide accurate diagnoses.)\n\n";
                stress_level = "high";
                Enter();
        }

        ifstream readexisting("Std_testlevel.txt"); //match existing user
        ofstream write_stdresult("test_tmp.txt", ios::app);
        
        bool userExists = false; //already done test and is a existing user //replace record
        bool userFound = false; // don't have test and is a new user //add record

        string storedUsername_file; //name in file

        // Check if the student already has a test result recorded
        while (readexisting >> storedStudentID >> storedUsername_file >> storedScore >> storedStress_Level) {
            if (enterIdnum == storedStudentID) { //replace record
                userExists = true;
                userFound = true;
                // Update the result
                write_stdresult << storedStudentID << " " << storedUsername << " " << score << " " << stress_level << endl;
            } else {
                write_stdresult << storedStudentID << " " << storedUsername_file << " " << storedScore << " " << storedStress_Level << endl; 
            }
        }

        readexisting.close();
        write_stdresult.close();

        remove("Std_testlevel.txt");
        rename("test_tmp.txt", "Std_testlevel.txt");

        if (!userFound) { //no test and is a new user
            ofstream write_1("Std_testlevel.txt", ios::app);
            if (write_1.is_open()){
                write_1 << Idnum << " " << name << " " << score << " " << stress_level << endl;
                write_1.close();
            }
        }
    }
};

class Counselor{
    private:
        int CounselorId;
        string C_password;
    public:
        string C_name, Room_num;
        string Phone_num;
        int C_enterIdnum;
        int storedCounselorID;
        string C_storedName, C_storedPassword;

    Counselor (int c_id = 0, string c_pass = "default123"): CounselorId(c_id), C_password(c_pass) {
        // display both for testing
        //cout << "ID: " << CounselorId << endl;
        //cout << "password: " << C_password << endl;
    } 

    void c_displayMenusignUp(){
        cout << "Enter Counselor_ID: ";
        cin >> CounselorId; 

        cout << "Enter your name(can't put space // put _ as space): ";
        cin >> C_name;

        string C_tmp_password;

        cout << "Do you want to use the default password? (y/n): ";
        char C_Default;
        cin >> C_Default;

        if (C_Default == 'n' || C_Default == 'N') {
            cout << "Create a new password:\n";
            cin >> C_tmp_password;

            cout << "Re-enter the password:\n";
            cin >> C_password;

            while (C_tmp_password != C_password) {
                cout << "Passwords do not match. Please try again.\n";
                cout << "Create a new password:\n";
                cin >> C_tmp_password;
                cout << "Re-enter the password:\n";
                cin >> C_password;
            }
        } else {
            C_password = "default123";
            cout << "Your default password is " << C_password << "." << endl;
        }
        cout << "Password set successfully!\n";

        //Enter phone number
        cout << "Enter your phone number(don't space): ";
        cin >> Phone_num;

        //Enter room number
        cout << "Enter your room number(xxx000): ";
        cin >> Room_num;
        UpperCase(Room_num);

        while (Room_num.size() != 6) {
            cout << "Invalid room number input. Please enter exactly 6 characters.\n";
            cout << "Enter your room number(xxx000): ";
            cin >> Room_num;
            UpperCase(Room_num);
        }
        cout << "Valid room number input.\n";

        ofstream write_Cusers("C_users.txt", ios::app);
        ofstream write_Cpass("C_password.txt", ios::app);

        if (write_Cusers.is_open()) {
            write_Cusers << CounselorId << " " << C_name << " " << Phone_num << " " << Room_num << endl;
            write_Cusers.close();
            cout << "Sign-up successful!\n";
        } else {
            cout << "Error opening file for sign-up.\n";
        }

        if (write_Cpass.is_open()) {
            write_Cpass << CounselorId << " " << C_name << " " << C_password << endl;
            write_Cpass.close();
            cout << "Password recorded!\n";
        } else {
            cout << "Error opening file for password.\n";
        }
    }

    bool c_login(){
        string C_enterpassword;
        int maxattempts = 3;
        
        cout << "Enter Counselor_ID: ";
        cin >> C_enterIdnum;

        cout << "Enter password: ";
        cin >> C_enterpassword;

        ifstream read_Cpass("C_password.txt"); 

        bool loginSuccessful_1 = false;

        for (int attempts = 0; attempts < maxattempts; attempts++){
            bool found = false; //to match username and password
            while (read_Cpass >> storedCounselorID >> C_storedName >> C_storedPassword){
                if (storedCounselorID == C_enterIdnum && C_storedPassword == C_enterpassword) {
                    cout << "Your name is " << C_storedName << endl;
                    cout << "Login successful!\n";
                    loginSuccessful_1 = true;
                    found = true;
                    break;
                }
            }

            //read the file from beginning
            read_Cpass.clear(); //clear the end-of-file flag
            read_Cpass.seekg(0, ios::beg); //reset the file pointer to the beginning

            if (!found) {
                cout << "Login failed. Invalid username or password.\n\n";
                if (attempts < maxattempts -1) {
                    cout << "Enter password again: ";
                    cin >> C_enterpassword;
                }
            } else {
                break; //break out of the outer loop if login is successful
            }
        }

        if (!loginSuccessful_1){
            cout << "Access denied.\n";
        }

        read_Cpass.close();

        return loginSuccessful_1;
    }

    void check_all(){
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

    void check_course(){
        string entercourse;
        cout << "You are checking all student's infomation by course" << endl;
        cout << "Enter a course(FIST, FET, FOB, FOL): ";
        cin >> entercourse;
        UpperCase(entercourse);

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

    void check_stresszone(){
        string enterStress_level;
        cout << "You are checking all student's infomation by stress zone" << endl;
        cout << "Enter a stress zone(low, moderate, high): ";
        cin >> enterStress_level;
        LowerCase(enterStress_level);

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

    void edit_stdinfo(){
        string enterStudentID;
        int choice;
        string new_StudentID, new_Username, new_Gender, new_DateOfBirth, new_Course;

        cout << "You are editing student's information" << endl;
        cout << "Enter a Student ID: ";
        cin >> enterStudentID;

        ifstream read("Std_users.txt");
        ofstream edit("temp.txt", ios::out | ios::app); //open a temporary file to write
        ifstream readinpass("student_password.txt");
        ofstream editinpass("pass_temp.txt", ios::out | ios::app);
        ifstream readtest("Std_testlevel.txt");
        ofstream edittest("test_temp.txt", ios::out | ios::app);

        if (!read.is_open() || !edit.is_open() ) {
            cout << "Error opening file for reading or writing." << endl;
            return;
        }

        if (!readinpass.is_open() || !editinpass.is_open() ) {
            cout << "Error opening file for reading or writing." << endl;
            return;
        }

        if (!readtest.is_open() || !edittest.is_open() ) {
            cout << "Error opening file for reading or writing." << endl;
            return;
        }

        string storedStudentID, storedUsername, storedGender, storedDateOfBirth, storedCourse;
        string storedPassword;
        string storedScore, storedZone;

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
                        cout << "\nAfter changing: " << endl << endl;
                        cout << "1. Student ID: " << new_StudentID << endl;
                        cout << "2. Username: " << storedUsername << endl;
                        cout << "3. Gender: " << storedGender << endl;
                        cout << "4. Date of Birth: " << storedDateOfBirth << endl;
                        cout << "5. Course: " << storedCourse << endl << endl;
                        break;
                    }
                    case 2: {
                        cout << "Enter a new Username: ";
                        cin >> new_Username;
                        edit << storedStudentID << " " << new_Username << " " << storedGender << " " << storedDateOfBirth << " " << storedCourse << endl;
                        cout << "\nAfter changing: " << endl << endl;
                        cout << "1. Student ID: " << storedStudentID << endl;
                        cout << "2. Username: " << new_Username << endl;
                        cout << "3. Gender: " << storedGender << endl;
                        cout << "4. Date of Birth: " << storedDateOfBirth << endl;
                        cout << "5. Course: " << storedCourse << endl << endl;
                        break;
                    }
                    case 3: {
                        cout << "Enter a new Gender [f/m]: ";
                        cin >> new_Gender;
                        LowerCase(new_Gender);
                        edit << storedStudentID << " " << storedUsername << " " << new_Gender << " " << storedDateOfBirth << " " << storedCourse << endl;
                        cout << "\nAfter changing: " << endl << endl;
                        cout << "1. Student ID: " << storedStudentID << endl;
                        cout << "2. Username: " << storedUsername << endl;
                        cout << "3. Gender: " << new_Gender << endl;
                        cout << "4. Date of Birth: " << storedDateOfBirth << endl;
                        cout << "5. Course: " << storedCourse << endl << endl;
                        break;
                    }
                    case 4: {
                        cout << "Enter a new Date of Birth (ddmmyy): ";
                        cin >> new_DateOfBirth;
                        edit << storedStudentID << " " << storedUsername << " " << storedGender << " " << new_DateOfBirth << " " << storedCourse << endl;
                        cout << "\nAfter changing: " << endl << endl;
                        cout << "1. Student ID: " << storedStudentID << endl;
                        cout << "2. Username: " << storedUsername << endl;
                        cout << "3. Gender: " << storedGender << endl;
                        cout << "4. Date of Birth: " << new_DateOfBirth << endl;
                        cout << "5. Course: " << storedCourse << endl << endl;
                        break;
                    }
                    case 5: {
                        cout << "Enter a new Course [FIST/FET/FOB/FOL]: ";
                        cin >> new_Course;
                        UpperCase(new_Course);
                        edit << storedStudentID << " " << storedUsername << " " << storedGender << " " << storedDateOfBirth << " " << new_Course << endl;
                        cout << "\nAfter changing: " << endl << endl;
                        cout << "1. Student ID: " << storedStudentID << endl;
                        cout << "2. Username: " << storedUsername << endl;
                        cout << "3. Gender: " << storedGender << endl;
                        cout << "4. Date of Birth: " << storedDateOfBirth << endl;
                        cout << "5. Course: " << new_Course << endl << endl;
                        break;
                    }
                    default:{
                        cout << "Invalid option." << endl;
                        return;
                    }
                }
            } else {
                // Write the existing data to the temporary file
                edit << storedStudentID << " " << storedUsername << " " << storedGender << " " << storedDateOfBirth << " " << storedCourse << endl;
                
            }
        }

        while (readinpass >> storedStudentID >> storedUsername >> storedPassword) {
            if (storedStudentID == enterStudentID){

                switch (choice){
                    case 1:{
                        editinpass << new_StudentID << " " << storedUsername << " " << storedPassword << endl;
                        break;
                    }
                    case 2:{
                        editinpass << storedStudentID << " " << new_Username << " " << storedPassword << endl;
                        break;
                    }
                    case 3:{
                        editinpass << storedStudentID << " " << storedUsername << " " << storedPassword << endl;
                        cout << "none" << endl;
                        break;
                    }
                    case 4:{
                        editinpass << storedStudentID << " " << storedUsername << " " << storedPassword << endl;
                        cout << "none" << endl;
                        break;
                    }
                    case 5:{
                        editinpass << storedStudentID << " " << storedUsername << " " << storedPassword << endl;
                        cout << "none" << endl;
                        break;
                    }
                    default:{
                        cout << "Error when saving data for student password txt." << endl;
                        return;
                    }
                }
                cout << "Student ID and Username in Student password txt changed." << endl;
            } else{
                editinpass << storedStudentID << " " << storedUsername << " " << storedPassword << endl;
            }
        }

        while (readtest >> storedStudentID >> storedUsername >> storedScore >> storedZone){
            if (storedStudentID == enterStudentID){

                switch (choice){
                    case 1:{
                        edittest << new_StudentID << " " << storedUsername << " " << storedScore << " " << storedZone << endl;
                        break;
                    }
                    case 2:{
                        edittest << storedStudentID << " " << new_Username << " " << storedScore << " " << storedZone << endl;
                        break;
                    }
                    case 3:{
                        edittest << storedStudentID << " " << storedUsername << " " << storedScore << " " << storedZone << endl;
                        cout << "none" << endl;
                        break;
                    }
                    case 4:{
                        edittest << storedStudentID << " " << storedUsername << " " << storedScore << " " << storedZone << endl;
                        cout << "none" << endl;
                        break;
                    }
                    case 5:{
                        edittest << storedStudentID << " " << storedUsername << " " << storedScore << " " << storedZone << endl;
                        cout << "none" << endl;
                        break;
                    }
                    default:{
                        edittest << storedStudentID << " " << storedUsername << " " << storedScore << " " << storedZone << endl;
                        cout << "Error when saving data for student textlevel txt." << endl;
                        return;
                    }
                }
                cout << "Student ID and Username in Student testlevel txt changed." << endl;
            } else {
                edittest << storedStudentID << " " << storedUsername << " " << storedScore << " " << storedZone << endl;
            }
        }

        read.close();
        edit.close();

        readinpass.close();
        editinpass.close();

        readtest.close();
        edittest.close();

        // Replace the original file with the temporary file
        remove("Std_users.txt");
        rename("Temp.txt", "Std_users.txt");

        remove("student_password.txt");
        rename("pass_temp.txt", "student_password.txt");

        remove("Std_testlevel.txt");
        rename("test_temp.txt", "Std_testlevel.txt");

    }
};

int main(){
    int choice, choice_c;
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

    //Create an instance of the Student class //as trigger
    Student student(123); 
    Counselor counselor(123);

    if (userType == 's' || userType == 'S'){
        if (action == 'l' || action == 'L') {
            bool loginSuccessful = student.login();

            // Check if the login was successful before proceeding to the menu
            if (!loginSuccessful) {
                cout << "Maximum login attempts reached. Exiting the program.\n\n";
                return 1; // Exit the program with an error code
            }
                    
        } else if (action == 's' || action == 'S') {
            student.displayMenusignUp();
        }
        Enter();
    } else if (userType == 'c' || userType == 'C'){
        if (action == 'l' || action == 'L') {
            bool loginSuccessful_1 = counselor.c_login();

            // Check if the login was successful before proceeding to the menu
            if (!loginSuccessful_1) {
                cout << "Maximum login attempts reached. Exiting the program.\n\n";
                    return 1; // Exit the program with an error code
            }
                    
            
        } else if (action == 's' || action == 'S') {
            counselor.c_displayMenusignUp();
        }
        Enter();
    }

    if (userType == 's' || userType == 'S'){
        do {
            clearScreen();
            
            cout << "\n\t\t\t\t\tWelcome to our stress test system\n"
                << "\t\t\t\t+------------------------------------------+\n"
                << "\t\t\t\t|           STRESS TEST SYSTEM             |\n"
                << "\t\t\t\t|------------------------------------------|\n"
                << "\t\t\t\t|         1. Check Personal Info           |\n"
                << "\t\t\t\t|         2. Test Your Stress Level        |\n"
                << "\t\t\t\t|         3. Exit                          |\n"
                << "\t\t\t\t+------------------------------------------+\n"
                << "\t\t\t\t(sign-up user must do the stress test directly)\n";
            
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
                    system("color E4"); //to change the whole background colour
                    student.Test_Result(); 
                    break;
                case 3:
                    // Return to the main menu
                    break;
                default:
                    cout << "\nInvalid choice. Please enter a number between 1 and 3." << endl;
            }
        } while (choice != 3);

    } else if (userType == 'c' || userType == 'C'){
        do {
            clearScreen();
            cout << "\n\t\t\t\t\tWelcome to our stress test system\n"
            << "\t\t\t\t+------------------------------------------+\n"
            << "\t\t\t\t|         STRESS TEST RECORD SYSTEM        |\n"
            << "\t\t\t\t|------------------------------------------|\n"
            << "\t\t\t\t|         1. Check for all                 |\n"
            << "\t\t\t\t|         2. Check by course               |\n"
            << "\t\t\t\t|         3. Check the stress zone         |\n"
            << "\t\t\t\t|         4. Edit student's info           |\n"
            << "\t\t\t\t|         5. Exit                          |\n"
            << "\t\t\t\t+------------------------------------------+\n";

            choice_c = getValidChoice(1,5);

            // Clear the newline character from the buffer // to fix the auto nextline (getline function)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice_c) {
            case 1:
                cout << "You selected Option A." << endl;
                counselor.check_all();
                Enter();
                break;
            case 2:
                clearScreen();
                cout << "You selected Option B." << endl;
                counselor.check_course();
                Enter();
                break;
            case 3:
                clearScreen();
                cout << "You selected Option C." << endl;
                counselor.check_stresszone();
                Enter();
                break;
            case 4:
                clearScreen();
                cout << "You selected Option D." << endl;
                counselor.edit_stdinfo();
                Enter();
                break;
            case 5:
                // Return to the main menu
                break;
            default:
                cout << "\nInvalid choice. Please enter a number between 1 and 5." << endl;
            }

        }while (choice_c !=5);
    }

    return 0;
}