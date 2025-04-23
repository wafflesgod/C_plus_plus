#include <iostream>
using namespace std;

void sub_list(string subname[]){    // Function definition: listing subject
    for(int i=0; i<8; i++){
    cout << subname[i] << endl;
    }
}

bool valid_ID(long long int id){    // Function definition: check if student ID is valid
    if(id >= 1000000000 && id <= 9999999999){
        return true;
    }
    else return false;
}

int main(){
    int  opt,sub_num[4]={0,0,0,0};
    long long int std_ID;
    char std_name[20];
    string subject[8] = {"1. TMA1111 MATHEMATICAL TECHNIQUES",      // Array containing all subjects
                         "2. TCP1121 COMPUTER PROGRAMMING",
                         "3. TDB1131 DATABASE SYSTEM",
                         "4. TOS1141 OPERATING SYSTEM",
                         "5. TMA1211 DISCRETE MATH AND PROBABILITY",
                         "6. TAO1221 COMPUTER ARCHITECTURE AND ORGANIZATION" ,
                         "7. TDC1231 DATA COMMUNICATION AND NETWORK" ,
                         "8. TEP1241 ETHICS AND PROFESSIONAL CONDUCTS"};

    cout << "Enter your name: ";            // Key in student name
    cin >> std_name;
    cout << "Enter your Student_ID: ";      // Key in student ID
    cin >> std_ID;


    if (valid_ID(std_ID)){
        do{
            cout << "\n*MAIN MENU*\n1.Subject registration\n2.Check my subject\n3.Timetable\n4.Exit\n";
            cout << "Enter your option: " << endl;
            cin >> opt;

            if(opt == 1){               //option 1: Register subject

                cout << " \n\n Welcome to subject registration option ! "<<endl;
                cout << " You are required to choose 4 subjects to register. \n\n";
                sub_list(subject);
                for(int j=0; j<4; j++){
                cout << "\nRegister subject number : ";
                cin >> sub_num[j];
                    if(sub_num[j] <1 || sub_num[j] > 8){
                    cout << "Registration error, please try again!\n";
                    break;
                    }
                }
            }

            else if (opt==2){           //option 2: Check registered subject

                    sub_list(subject);
                    cout<<" \nSubjects that you have chosen are : \n"
                        << sub_num[0] << ", "
                        << sub_num[1] << ", "
                        << sub_num[2] << ", "
                        << sub_num[3] << endl;
                }

            else if (opt==3){           // option 3: Check timetable

                    cout<<"Below is your timetable"<<endl;
                    for(int j=0; j<4; j++){
                    if (sub_num[j]==1){
                        cout << "TMA1111. MATHEMATICAL TECHNIQUES:               Monday    0800-1000,   Wednesday 1600-1700"<<endl;
                    }
                    else if (sub_num[j]==2){
                        cout << "TCP1121 COMPUTER PROGRAMMING:                   Tuesday   1000-1200,   Wednesday 1700-1800"<<endl;
                    }
                    else if (sub_num[j]==3){
                        cout << "TDB1131 DATABASE SYSTEM:                        Wednesday 1000-1200,   Thursday  0800-1000"<<endl;
                    }
                    else if (sub_num[j]==4){
                        cout << "TOS1141 OPERATING SYSTEM:                       Monday    1500-1700,   Tuesday   1600-1800"<<endl;
                    }
                    else if (sub_num[j]==5){
                        cout << "TMA1211 DISCRETE MATH AND PROBABILITY:          Monday    1200-1400,   Friday    0800-1000"<<endl;
                    }
                    else if (sub_num[j]==6){
                        cout << "TAO1221 COMPUTER ARCHITECTURE AND ORGANIZATION: Monday    1000-1200,   Thursday  1700-1900"<<endl;
                    }
                    else if (sub_num[j]==7){
                        cout << "TDC1231 DATA COMMUNICATION AND NETWORK:         Tuesday   0800-1000,   Friday    1500-1700"<<endl;
                    }
                    else if (sub_num[j]==8){
                        cout << "TEP1241 ETHICS AND PROFESSIONAL CONDUCTS:       Thursday  1500-1600,   Friday    1200-1400"<<endl;
                    }
                    else{
                        cout << "\nSomething is going wrong!!!Please try to register the subject again!!!\n"<<endl;
                    }
                }
            }
        }
        while(opt != 4);            //option 4: Exit
        cout << "Thank you visiting our subject registration system"<<endl;
    }
    else                        // Error if student ID is invalid
        cout << "Error student ID !\n";
}
