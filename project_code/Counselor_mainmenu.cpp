#include <iostream>
#include <cstdlib> // for system("clear") or system("cls")
#include <fstream>

using namespace std;

void clearScreen() { //暂时没有用到，看你们要加在哪里
#ifdef _WIN32
    system("cls");
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

int main(){
    int choice;
    welcome();
    cout << "\n\t\t\t\t\tTo our stress test system\n"
         << "\t\t\t\t+------------------------------------------+\n"
         << "\t\t\t\t|         STRESS TEST RECORD SYSTEM        |\n"
         << "\t\t\t\t|------------------------------------------|\n"
         << "\t\t\t\t|         1. Check for all                 |\n"
         << "\t\t\t\t|         2. Check by course               |\n"
         << "\t\t\t\t|         3. Check the stress zone         |\n"
         << "\t\t\t\t|         4. Edit student's info           |\n"
         << "\t\t\t\t|         5. Exit                          |\n"
         << "\t\t\t\t+------------------------------------------+\n"
         << "\t\t\t\t\tEnter your option(1-4): ";
         cin >> choice;

       switch (choice) {
        case 1:
            cout << "You selected Option A." << endl;
            // Add code for Option A
            break;
        case 2:
            cout << "You selected Option B." << endl;
            // Add code for Option B
            break;
        case 3:
            cout << "You selected Option C." << endl;
            // Add code for Option C
            break;
        case 4:
            cout << "You selected Option D." << endl;
            // Add code for Option D
            break;
        case 5:
            // Return to the main menu
            break;
        default:
            cout << "\nInvalid choice. Please enter a number between 1 and 5." << endl;
        }

    cout << endl;

}
