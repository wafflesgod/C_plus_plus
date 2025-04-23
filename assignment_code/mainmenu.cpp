#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu() {
    cout << "==========CP FISH AQUARIUM==========" << endl;
    cout << "\nMenu:" << endl;
    cout << "1. Fish_Stock_Calculator(FRESH WATER) " << endl;
    cout << "2. Fish_Stock_Calculator(SALT WATER)" << endl;
    cout << "0. Exit" << endl;
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
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < min || choice > max) {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
            cin.clear();  // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
        } else {
            break;
        }
    }
    return choice;
}

int main() {
    int choice;

    do {
        clearScreen();
        cout << "\033[1;37;44m"; // white text on light blue background
        displayMenu();
        cout << "\033[0m"; // reset text attributes

        choice = getValidChoice(0, 2);

        switch (choice) {
            case 1:
                do {
                    clearScreen();
                    cout << "\033[1;37;44m"; // white text on light blue background
                    displaySecondMenu();
                    cout << "\033[0m"; // reset text attributes

                    choice = getValidChoice(1, 3);

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
                            // Return to the main menu
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                    }
                } while (choice != 3);
                break;

            case 2:
                do {
                    clearScreen();
                    cout << "\033[1;37;44m"; // white text on light blue background
                    displayThirdMenu();
                    cout << "\033[0m"; // reset text attributes

                    choice = getValidChoice(1, 3);

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
                            // Return to the main menu
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                    }
                } while (choice != 3);
                break;


            case 0:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }

    } while (choice != 2 || choice < 0);

    return 0;
}


