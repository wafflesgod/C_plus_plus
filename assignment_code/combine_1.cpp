#include <iostream>
#include <cstdlib> //for system
#include <limits>
using namespace std;

char response;

void clearScreen() {
#ifdef _WIN32
    system("cls"); //clear screen for wWindows
#else
    system("clear"); // Clear screen for Unix/Linux
#endif //endif when WIN32 not defined
}

void displayMenu() {
    cout << "==========CP FISH AQUARIUM==========" << endl;
    cout << "\nMenu:" << endl;
    cout << "1. Fish_Stock_Calculator(FRESH WATER) " << endl;
    cout << "2. Fish_Stock_Calculator(SALT WATER)" << endl;
    cout << "3. Exit" << endl;
}

void displaySecondMenu() {
    clearScreen();
    cout << "\nFish_Stock_Calculator:" << endl;
    cout << "1. Calculation for Fresh Water, Juvenile Fish" << endl;
    cout << "2. Calculation for Fresh Water, Full Growth Fish" << endl;
    cout << "3. Back to Main Menu" << endl;
}

void displayThirdMenu() {
    clearScreen();
    cout << "\nFish_Stock_Calculator:" << endl;
    cout << "1. Calculation for Salt Water, Juvenile Fish" << endl;
    cout << "2. Calculation for Salt Water, Full Growth Fish" << endl;
    cout << "3. Back to Main Menu" << endl;
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

void error(){
    while (response != 'Y' && response != 'y' && response != 'N' && response != 'n') {
            cout << "\nYou could only enter 'Y' or 'N'. Please enter again: ";
            cin >> response;
        }
}

void jun_fresh(){
    double tank[3];

    cout << "**Juvenile Fish Stock Calculator (Fresh Water)** " << endl;
    cout << "\n\nPlease insert your tank length (cm): ";
    cin >> tank[0];
    cout << "Please insert your tank width (cm): ";
    cin >> tank[1];
    cout << "Please insert your tank height (cm): ";
    cin >> tank[2];

    cout << endl << "Your tank length, width and height are ";
    for (int i = 0; i < 3; i++) {
        cout << tank[i] << "cm" << " ";
    }

    do {
        cout << "\n\nIs it correct? (Y/N):";
        cin >> response;

        error();

        if (response == 'N' || response == 'n') {
            cout << "\n\nPlease insert again your tank length(cm): ";
            cin >> tank[0];
            cout << "Please insert again your tank width(cm) : ";
            cin >> tank[1];
            cout << "Please insert again your tank height(cm): ";
            cin >> tank[2];
            cout << "\n\nYour tank length, width and height are ";
            for (int i = 0; i < 3; i++) {
                cout << tank[i] << "cm ";
            }
        }
    }while (response == 'N' || response == 'n');

            double volume, capacity;
            int amount;
            volume = tank[0]*tank[1]*tank[2];
            capacity = (volume/1000) * 0.85;
            amount = capacity / 3.785 ;
            cout<< "\n\n-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\t\t\t*CALCULATION*"<<endl;
            cout<< "-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\nVolume: "<<volume<< "cm^3"<<endl;
            cout<< "Water capacity: "<<capacity<< "cm^3"<<endl;
            cout<< "Maximum amount of the fish in the tank: "<<amount<<endl;
            cout<< "\n-----------------------------------------------------------------------------------------------------------"<<endl;

}

void full_fresh(){
    double tank[3];

    cout << "**Full Growth Fish Stock Calculator (Fresh Water)**"
    << endl;
    cout <<"\n\nPlease insert your tank length (cm): ";
    cin >> tank[0];
    cout <<"Please insert your tank width (cm): ";
    cin >> tank[1];
    cout <<"Please insert your tank height (cm): ";
    cin >> tank[2];

    cout << endl <<"your tank length, width and height are ";
    for (int i = 0; i < 3; i++){
        cout << tank[i] << "cm" << " ";
    }

    do {
        cout << "\n\nIs it correct? (Y/N):";
        cin >> response;

        error();

        if (response == 'N' || response == 'n') {
            cout << "\n\nPlease insert again your tank length(cm): ";
            cin >> tank[0];
            cout << "Please insert again your tank width(cm) : ";
            cin >> tank[1];
            cout << "Please insert again your tank height(cm): ";
            cin >> tank[2];
            cout << "\n\nYour tank length, width and height are ";
            for (int i = 0; i < 3; i++) {
                cout << tank[i] << "cm ";
            }
        }
    }while (response == 'N' || response == 'n');

    double volume, capacity;
    int amount;
    volume = tank[0]*tank[1]*tank[2];
    capacity = (volume/1000) * 0.85;
    amount = capacity / (3.785 * 2);
     cout<< "\n\n-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\t\t\t*CALCULATION*"<<endl;
            cout<< "-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\nVolume: "<<volume<< "cm^3"<<endl;
            cout<< "Water capacity: "<<capacity<< "cm^3"<<endl;
            cout<< "Maximum amount of the fish in the tank: "<<amount<<endl;
            cout<< "\n-----------------------------------------------------------------------------------------------------------"<<endl;

}

void jun_salt(){
    double tank[3];

    cout << "**Juvenile Fish Stock Calculator (Salt Water)** " << endl;
    cout << "\n\nPlease insert your tank length (cm): ";
    cin >> tank[0];
    cout << "Please insert your tank width (cm): ";
    cin >> tank[1];
    cout << "Please insert your tank height (cm): ";
    cin >> tank[2];

    cout << endl << "Your tank length, width and height are ";
    for (int i = 0; i < 3; i++) {
        cout << tank[i] << "cm" << " ";
    }

    do {
        cout << "\n\nIs it correct? (Y/N):";
        cin >> response;

        error();

        if (response == 'N' || response == 'n') {
            cout << "\n\nPlease insert again your tank length(cm): ";
            cin >> tank[0];
            cout << "Please insert again your tank width(cm) : ";
            cin >> tank[1];
            cout << "Please insert again your tank height(cm): ";
            cin >> tank[2];
            cout << "\n\nYour tank length, width and height are ";
            for (int i = 0; i < 3; i++) {
                cout << tank[i] << "cm ";
            }
        }
    }while (response == 'N' || response == 'n');

            double volume, capacity;
            int amount;
            volume = tank[0]*tank[1]*tank[2];
            capacity = (volume/1000) * 0.85;
            amount = capacity / (3.785 * 3) ;
            cout<< "\n\n-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\t\t\t*CALCULATION*"<<endl;
            cout<< "-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\nVolume: "<<volume<< "cm^3"<<endl;
            cout<< "Water capacity: "<<capacity<< "cm^3"<<endl;
            cout<< "Maximum amount of the fish in the tank: "<<amount<<endl;
            cout<< "\n-----------------------------------------------------------------------------------------------------------"<<endl;

}

void full_salt(){
    double tank[3];

    cout << "**Full Growth Fish Stock Calculator (Salt Water)** " << endl;
    cout << "\n\nPlease insert your tank length (cm): ";
    cin >> tank[0];
    cout << "Please insert your tank width (cm): ";
    cin >> tank[1];
    cout << "Please insert your tank height (cm): ";
    cin >> tank[2];

    cout << endl << "Your tank length, width and height are ";
    for (int i = 0; i < 3; i++) {
        cout << tank[i] << "cm" << " ";
    }

    do {
        cout << "\n\nIs it correct? (Y/N):";
        cin >> response;

        error();

        if (response == 'N' || response == 'n') {
            cout << "\n\nPlease insert again your tank length(cm): ";
            cin >> tank[0];
            cout << "Please insert again your tank width(cm) : ";
            cin >> tank[1];
            cout << "Please insert again your tank height(cm): ";
            cin >> tank[2];
            cout << "\n\nYour tank length, width and height are ";
            for (int i = 0; i < 3; i++) {
                cout << tank[i] << "cm ";
            }
        }
    }while (response == 'N' || response == 'n');

            double volume, capacity;
            int amount;
            volume = tank[0]*tank[1]*tank[2];
            capacity = (volume/1000) * 0.85;
            amount = capacity / (3.785 * 4.5);
            cout<< "\n\n-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\t\t\t*CALCULATION*"<<endl;
            cout<< "-----------------------------------------------------------------------------------------------------------"<<endl;
            cout<< "\nVolume: "<<volume<< "cm^3"<<endl;
            cout<< "Water capacity: "<<capacity<< "cm^3"<<endl;
            cout<< "Maximum amount of the fish in the tank: "<<amount<<endl;
            cout<< "\n-----------------------------------------------------------------------------------------------------------"<<endl;

}

int main() {
    int choice, choice_1, choice_2;

    do {
        clearScreen();
        cout << "\033[1;37;44m"; // white text on light blue background
        displayMenu();
        cout << "\033[0m"; // reset text attributes

        choice = getValidChoice(1, 3); //1-min, 3-max

        switch (choice) {
            case 1:
                do {
                    clearScreen();
                    cout << "\033"; // white text
                    displaySecondMenu();

                    choice_1 = getValidChoice(1, 3);

                    switch (choice_1) {
                        case 1:
                            cout << "You selected Option 1." << endl << endl;
                                jun_fresh();
                                do{

                                    cout << "Do you want to continue? (Y/N):";
                                    cin >> response;

                                    error();

                                    if (response == 'Y' || response == 'y'){
                                        cout << "\nDo you still want to calculate the same type of fish and the same type of water for a tank? (Y/N):";
                                        cin >> response;

                                        error();

                                            if (response == 'Y' || response == 'y'){
                                                cout << "Okay sure here it is!";
                                                cout <<endl <<endl;
                                                jun_fresh();
                                            }

                                            else if (response == 'N' || response == 'n'){
                                                cout << "Okay sure here it is!";
                                                //main menu
                                        }
                                    }
                                }while (response == 'Y' || response == 'y');

                                cout << endl <<"\n\nHope we've been able to help you out!\n\n";
                            break;
                        case 2:
                            cout << "You selected Option 2." << endl << endl;
                                full_fresh();
                                do{

                                    cout << "Do you want to continue? (Y/N):";
                                    cin >> response;

                                    error();

                                    if (response == 'Y' || response == 'y'){
                                        cout << "\nDo you still want to calculate the same type of fish and the same type of water for a tank? (Y/N):";
                                        cin >> response;

                                        error();

                                            if (response == 'Y' || response == 'y'){
                                                cout << "Okay sure here it is!";
                                                cout <<endl <<endl;
                                                full_fresh();
                                            }

                                            else if (response == 'N' || response == 'n'){
                                                cout << "Okay sure here it is!";
                                                //main menu
                                        }
                                    }
                                }while (response == 'Y' || response == 'y');

                                cout << endl <<"\n\nHope we've been able to help you out!\n\n";
                                //main menu

                            break;
                        case 3:
                            // Return to the main menu
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                    }
                } while (choice_1 != 3);
                break;

            case 2:
                do {
                    clearScreen();
                    cout << "\033"; // white text
                    displayThirdMenu();

                    choice_2 = getValidChoice(1, 3);

                    switch (choice_2) {
                        case 1:
                            cout << "You selected Option 1." << endl <<endl;
                                jun_salt();
                                do{

                                    cout << "Do you want to continue? (Y/N):";
                                    cin >> response;

                                    error();

                                    if (response == 'Y' || response == 'y'){
                                        cout << "\nDo you still want to calculate the same type of fish and the same type of water for a tank? (Y/N):";
                                        cin >> response;

                                        error();

                                            if (response == 'Y' || response == 'y'){
                                                cout << "Okay sure here it is!";
                                                cout <<endl <<endl;
                                                jun_salt();
                                            }

                                            else if (response == 'N' || response == 'n'){
                                                cout << "Okay sure here it is!";
                                                //main menu
                                        }
                                    }
                                }while (response == 'Y' || response == 'y');

                                cout << endl <<"\n\nHope we've been able to help you out!\n\n";
                                //main menu

                            break;
                        case 2:
                            cout << "You selected Option 2." << endl << endl;
                                full_salt();
                                do{

                                    cout << "Do you want to continue? (Y/N):";
                                    cin >> response;

                                    error();

                                    if (response == 'Y' || response == 'y'){
                                        cout << "\nDo you still want to calculate the same type of fish and the same type of water for a tank? (Y/N):";
                                        cin >> response;

                                        error();

                                            if (response == 'Y' || response == 'y'){
                                                cout << "Okay sure here it is!";
                                                cout <<endl <<endl;
                                                full_salt();
                                            }

                                            else if (response == 'N' || response == 'n'){
                                                cout << "Okay sure here it is!";
                                                //main menu
                                        }
                                    }
                                }while (response == 'Y' || response == 'y');

                                cout << endl <<"\n\nHope we've been able to help you out!\n\n";
                                //main menu

                            break;
                        case 3:
                            // Return to the main menu
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                    }
                } while (choice_2 != 3);
                break;

            case 3:
                cout << "Exiting the program."<<endl;
                cout << "Thank you for using our system!"<< endl;
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
        }

    } while (choice !=3);

    return 0;
}


