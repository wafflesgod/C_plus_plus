#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream> // File input/output
#include <string>  // String manipulation
#include <sstream> // String stream
#include <iomanip> // Input/output manipulation
#include "utilities.hpp"
using namespace std;

// Function to convert a date string (DD-MM-YYYY) to a comparable integer format (YYYYMMDD)


// Node structure for the Queue
struct Node {
    int dateValue;      // Date in comparable format (YYYYMMDD)
    string dateString;  // Original date string (e.g., "12-12-2025")
    Node* next;
    Node(int val, const string& date) : dateValue(val), dateString(date), next(nullptr) {}
};

// Class to implement queue operations using a linked list
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Add an element to the rear of the queue
    void enqueue(int new_data, const string& new_date) {
        Node* temp = new Node(new_data, new_date);
        if (rear == nullptr) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }

    // Remove an element from the front of the queue
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    // Get the date value of the front element
    int getFrontDate() {
        return front ? front->dateValue : -1; // Return -1 if the queue is empty
    }

    // Get the date string of the front element
    string getFrontDateString() {
        return front ? front->dateString : "";
    }

    // Get the date value of the rear element
    int getRearDate() {
        return rear ? rear->dateValue : -1; // Return -1 if the queue is empty
    }

    // Get the date string of the rear element
    string getRearDateString() {
        return rear ? rear->dateString : "";
    }
};

// Class to simulate time-related functionality
class Time {
public:
    string currentDay() {
        time_t tt; //declaring argument for time()

        struct tm* ti; //declaring variable to store return value of localtime()

        time(&tt); //applying time()

        ti = localtime(&tt); //using localtime()

        char buffer[80];

        strftime(buffer, sizeof(buffer), "%d-%m-%Y", ti); //formatting date and day

        cout << "Current Date is " << buffer << endl;

        return buffer;
    }
};

// Class to handle admin operations
class Admin {
private:
    string A_password;

public:
    Admin(const string& a_pass = "admin123") : A_password(a_pass) {}

    // Admin login functionality
    bool a_login() {
        string A_enterid, A_enterpassword;
        int maxattempts = 3, max_idattempts = 3;

        cout << "Enter your admin ID: ";
        cin >> A_enterid;

        cout << "Enter password: ";
        cin >> A_enterpassword;

        ifstream read_Apass("admin.txt");
        if (!read_Apass) {
            cerr << "Error opening admin.txt file." << endl;
            return false;
        }

        string stored_A_ID, stored_A_Name, stored_A_Password;
        bool loginSuccessful = false;

        for (int attempts = 0; attempts < maxattempts; attempts++) {
            bool found = false;
            while (read_Apass >> stored_A_ID >> stored_A_Name >> stored_A_Password) {
                if (stored_A_ID == A_enterid && stored_A_Password == A_enterpassword) {
                    cout << "\nYour name is " << stored_A_Name << endl;
                    cout << "Login successful!\n\n";
                    cout << "Hold on awhile... Loading\n";
                    this_thread::sleep_for(chrono::seconds(2));
                    loginSuccessful = true;
                    found = true;
                    break;
                }
            }

            read_Apass.clear(); // Clear the end-of-file flag
            read_Apass.seekg(0, ios::beg); // Reset the file pointer to the beginning

            if (!found) {
                cout << "Login failed. Invalid password.\n\n";
                if (attempts < maxattempts - 1) {
                    cout << "Enter your admin ID again: ";
                    cin >> A_enterid;
                    cout << "Enter password again: ";
                    cin >> A_enterpassword;
                }
            } else {
                break; // Break out of the outer loop if login is successful
            }
        }

        read_Apass.close();
        return loginSuccessful;
    }

    // Display bookings for a specific booking ID
    void a_displaybookings() {
        string entered_B_ID;
        cout << "Enter the booking ID: ";
        cin >> entered_B_ID;

        ifstream read_bookings("booking.txt");
        if (!read_bookings) {
            cerr << "Error opening booking.txt file." << endl;
            return;
        }

        string line;
        while (getline(read_bookings, line)) {
            stringstream ss(line);
            string stored_B_ID, stored_U_ID, stored_date, stored_PetName;

            getline(ss, stored_B_ID, ',');
            getline(ss, stored_U_ID, ',');
            getline(ss, stored_date, ',');
            getline(ss, stored_PetName, ',');

            if (stored_B_ID == entered_B_ID) {
                cout << "Booking ID: " << stored_B_ID
                     << "\nUser ID: " << stored_U_ID
                     << "\nDate: " << stored_date
                     << "\nPet Name: " << stored_PetName << endl << endl;
            }
        }

        read_bookings.close();
    }

    // Display pets for a specific user ID
    void a_displayuserpet() {
        string entered_U_ID;
        cout << "Enter the User ID: ";
        cin >> entered_U_ID;

        ifstream read_pet("pet.txt");
        if (!read_pet) {
            cerr << "Error opening pet.txt file." << endl;
            return;
        }

        string line;
        while (getline(read_pet, line)) {
            stringstream ss(line);
            string stored_P_ID, stored_U_ID, stored_PetName, stored_PetType, stored_PetAge, stored_PetGender;

            getline(ss, stored_P_ID, ',');
            getline(ss, stored_U_ID, ',');
            getline(ss, stored_PetName, ',');
            getline(ss, stored_PetType, ',');
            getline(ss, stored_PetAge, ',');
            getline(ss, stored_PetGender, ',');

            if (stored_U_ID == entered_U_ID) {
                cout << "\nPet ID: " << stored_P_ID
                     << "\nUser ID: " << stored_U_ID
                     << "\nPet Name: " << stored_PetName
                     << "\nPet Type: " << stored_PetType
                     << "\nPet Age: " << stored_PetAge
                     << "\nPet Gender: " << stored_PetGender << endl << endl;
            }
        }

        read_pet.close();
    }

    // Display and dequeue bookings earlier than the current date
    void a_displayqueuedequeue() {
        Queue q;
        ifstream readfile("booking.txt");
        if (!readfile) {
            cerr << "Error opening booking.txt file." << endl;
            return;
        }

        string entered_userid;
        cout << "Enter user id: ";
        cin >> entered_userid;

        string line;
        while (getline(readfile, line)) {
            stringstream ss(line);
            string stored_B_ID, stored_userid, storedDate, storedPetName;

            getline(ss, stored_B_ID, ',');
            getline(ss, stored_userid, ',');
            getline(ss, storedDate, ',');
            getline(ss, storedPetName, ',');

            if (stored_userid == entered_userid) {
                int comparableDate = convertDateToComparableFormat(storedDate);
                q.enqueue(comparableDate, storedDate);
                cout << "Queue Front (queue): " << q.getFrontDate() << endl;
                cout << "Queue Rear (queue): " << q.getRearDate() << endl;
                cout << "Pet Name: " << storedPetName << " Date: " << storedDate << endl;
            }
        }

        // Dequeue elements with dates earlier than the current date
        string currentDateString = Time().currentDay(); // Get current date
        int currentDate = convertDateToComparableFormat(currentDateString);

        cout << "Current Date: " << currentDateString << " (" << currentDate << ")" << endl;
        while (!q.isEmpty() && isEarlierDate(q.getFrontDate(), currentDate)) {
            cout << "Dequeueing element with date: " << q.getFrontDateString() << endl;
            q.dequeue();

            if (!q.isEmpty()) {
            cout << "Queue Front (dequeue): " << q.getFrontDate() << endl;
            cout << "Queue Rear (dequeue): " << q.getRearDate() << endl;
            } else {
                cout << "nothing else" << endl;
            }
        }

        // Display remaining queue
        if (!q.isEmpty()) {
            cout << "Remaining Queue Front: " << q.getFrontDateString() << endl;
            cout << "Remaining Queue Rear: " << q.getRearDateString() << endl;
        } else {
            cout << "Queue is empty after processing." << endl;
        }

        readfile.close();
    }
};
