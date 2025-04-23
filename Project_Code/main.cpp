#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include "utilities.hpp"
#include "user.hpp"
#include "booking.hpp"
#include "admin.cpp"

using namespace std;

void UserMenu(int uid) {
    int uchoice;

    do {
        cout << "==================\n";
        cout << "User Menu:\n";
        cout << "==================\n";
        cout << "1. Add Booking\n";
        cout << "2. Display Booking\n";
        cout << "3. Display Pet\n";
        cout << "4. Delete Booking\n";
        cout << "5. Edit Pet\n";
        cout << "6. Log Out\n";
        cout << "Enter your choice: ";
        cin >> uchoice;

        switch (uchoice) {
            case 1:
                system("cls");
                addBooking(uid);
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                disBooking(uid);
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                dispet(uid);
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                delbooking(uid);
                break;
            case 5:
                system("cls");
                PetEditMenu(uid);
                break;
            case 6:
                cout << "Loading\n";
                this_thread::sleep_for(chrono::seconds(1));
                cout << "Bye!\n";
                system("pause");
                system("cls");
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (uchoice != 6);
}

void AdminMenu() {
    Admin admin_x;
    int achoice;
    int petId;
    string petName, ownerName;

    do {
        cout << "==============\n";
        cout << "Admin Menu:\n";
        cout << "==============\n";
        cout << "1. Display Booking\n";
        cout << "2. Display User's Pet\n";
        cout << "3. Display Queue & Dequeue\n";
        cout << "4. Log Out\n";
        cout << "Enter your choice: ";
        cin >> achoice;

        switch (achoice) {
            case 1:
                system("cls");
                admin_x.a_displaybookings();
                break;
            case 2:
                system("cls");
                admin_x.a_displayuserpet();
                break;
            case 3:
                system("cls");
                admin_x.a_displayqueuedequeue();
                break;
            case 4:
                cout << endl;
                this_thread::sleep_for(chrono::seconds(1));
                cout << "See you Byeee...\n";
                system("pause");
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (achoice != 4);
}

int main() {
    Admin admin;
    int choice;
    while (true) {
        cout << "===============\n";
        cout << "Main Menu:\n";
        cout << "===============\n";
        cout << "1. New User\n";
        cout << "2. User Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            newuser();
        } else if (choice == 2) {
            int uid;
            string username;
            if (login(uid, username)) {
                system("cls");
                cout << "==================\n";
                cout << "Welcome! " << username << " (Make sure have update your pet at No.5 (EditPet) first)"<<endl;
                UserMenu(uid);
            } else {
                cout << "Login failed. Invalid UID or password." << endl;
            }
        } else if (choice == 3) {
            bool loginSuccessful = admin.a_login();

            if (!loginSuccessful){
                cout << "Maximum login attempts reached. Exiting the program.\n\n";
                return 1;
            }
            system("pause");
            system("cls");
            AdminMenu();
        } else if (choice == 4) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
