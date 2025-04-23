#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "booking.hpp"
#include "user.hpp"

using namespace std;

// Calendar class implementation
class Calendar {
    private:
    int year, month;
    int bookings[31];

    //bool isLeapYear(int year);
    //int getStartDay(int month, int year);

public:

    Calendar(int year, int month) : year(year), month(month) {
    for (int i = 0; i < 31; ++i) {
        bookings[i] = 0;
    }
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getStartDay(int month, int year) {
    int d = 1, m = month, y = year;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    return (d + 2*m + (3*(m+1))/5 + y + y/4 - y/100 + y/400 + 1) % 7;
}

int getDaysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

void displayCalendar() {
    const string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysInMonth = getDaysInMonth(month, year);
    int startDay = getStartDay(month, year);

    cout << "Calendar for " << months[month-1] << " " << year << endl;
    cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

    for (int i = 0; i < startDay; ++i) {
        cout << "    ";
    }

    for (int day = 1; day <= daysInMonth; ++day) {
        cout << setw(3) << day;
        if (bookings[day-1] >= 5) {
            cout << "*";
        } else {
            cout << " ";
        }
        if ((day + startDay) % 7 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

bool bookDay(int day) {
    if (day < 1 || day > getDaysInMonth(month, year)) {
        cout << "Invalid day!" << endl;
        return false;
    }
    if (bookings[day-1] < 5) {
        bookings[day-1]++;
        return true;
    } else {
        cout << "Booking full for day " << day << endl;
        return false;
    }
}
};

int getbookid() {
    int lastbookid = 800;

    ifstream bookFile("booking.txt");
    if (!bookFile.is_open()) {
        return lastbookid++;
    }

    string line;
    while (getline(bookFile, line)) {
        stringstream ss(line);
        string storedbookid;
        getline(ss, storedbookid, ',');
        lastbookid = stoi(storedbookid);
    }

    bookFile.close();

    return ++lastbookid;
}

// Add booking function
void addBooking(int uid) {
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;

    dispet(uid);
    cout << endl;
    cout << "How many pets do you want to put into the Hotel? " << endl;
    cout << "Number of Pets: ";
    int petCount;
    cin >> petCount;

    if (petCount <= 0) {
        cout << "Invalid number of pets. Exiting.\n";
        return;
    }

    // Dynamically allocate an array to store pet names
    string* petNames = new string[petCount];

    ifstream petFile("pet.txt");
    if (!petFile.is_open()) {
        cout << "Error: Unable to open pet file." << endl;
        delete[] petNames; // Free allocated memory before exiting
        return;
    }

    for (int i = 0; i < petCount; i++) {
        cout << "Enter the ID of pet " << (i + 1) << ": ";
        int petId;
        cin >> petId;

        string line;
        bool petFound = false;
        while (getline(petFile, line)) {
            stringstream ss(line);
            string storedpetID, storedUID, storedType, storedName, storedAge, storedGender;

            getline(ss, storedpetID, ',');
            getline(ss, storedUID, ',');
            getline(ss, storedName, ',');
            getline(ss, storedType, ',');
            getline(ss, storedAge, ',');
            getline(ss, storedGender, ',');

            if (stoi(storedpetID) == petId && stoi(storedUID) == uid) {
                petNames[i] = storedName;
                petFound = true;
                break;
            }
        }

        if (!petFound) {
            cout << "Error: Pet ID " << petId << " not found or does not belong to user ID " << uid << ".\n";
            delete[] petNames; // Free allocated memory before exiting
            petFile.close();
            return;
        }

        // Reset file state for the next pet
        petFile.clear();
        petFile.seekg(0, ios::beg);
    }
    petFile.close();

    // Get start and end dates from the user
    cout << "Enter start year (e.g., 2023): ";
    cin >> startYear;
    cout << "Enter start month (1-12): ";
    cin >> startMonth;

    if (startMonth < 1 || startMonth > 12) {
        cout << "Invalid start month. Exiting.\n";
        delete[] petNames; // Free allocated memory before exiting
        return;
    }

    Calendar startCalendar(startYear, startMonth);
    startCalendar.displayCalendar();

    cout << "Enter start day (1-" << startCalendar.getDaysInMonth(startMonth, startYear) << "): ";
    cin >> startDay;

    if (startDay < 1 || startDay > startCalendar.getDaysInMonth(startMonth, startYear)) {
        cout << "Invalid start day. Exiting.\n";
        delete[] petNames; // Free allocated memory before exiting
        return;
    }

    cout << "Enter end year (e.g., 2023): ";
    cin >> endYear;
    cout << "Enter end month (1-12): ";
    cin >> endMonth;

    if (endMonth < 1 || endMonth > 12) {
        cout << "Invalid end month. Exiting.\n";
        delete[] petNames; // Free allocated memory before exiting
        return;
    }

    cout << "Enter end day: ";
    cin >> endDay;

    if (endYear < startYear || (endYear == startYear && endMonth < startMonth) ||
        (endYear == startYear && endMonth == startMonth && endDay < startDay)) {
        cout << "Invalid date range. End date must be after start date.\n";
        delete[] petNames; // Free allocated memory before exiting
        return;
    }

    // Generate booking ID
    int bookId = getbookid();

    ofstream bookingFile("booking.txt", ios::app);
    if (!bookingFile.is_open()) {
        cout << "Error: Unable to open booking.txt for writing.\n";
        delete[] petNames; // Free allocated memory before exiting
        return;
    }

    // Booking loop
    for (int i = 0; i < petCount; i++) {
        int currentYear = startYear;
        int currentMonth = startMonth;
        int currentDay = startDay;

        while (true) {
            Calendar currentCalendar(currentYear, currentMonth);

            if (currentCalendar.bookDay(currentDay)) {
                bookingFile << bookId << "," << uid << "," << currentDay << "-" << currentMonth << "-" << currentYear
                            << "," << petNames[i] << "\n";
            } else {
                cout << "Booking failed for day " << currentDay << "-" << currentMonth << "-" << currentYear << ".\n";
            }

            if (currentYear == endYear && currentMonth == endMonth && currentDay == endDay) {
                break;
            }

            currentDay++;
            if (currentDay > currentCalendar.getDaysInMonth(currentMonth, currentYear)) {
                currentDay = 1;
                currentMonth++;
                if (currentMonth > 12) {
                    currentMonth = 1;
                    currentYear++;
                }
            }
        }
    }

    bookingFile.close();
    sortAndSaveBookings();
    delete[] petNames; // Free allocated memory after use
    cout << "Booking successful! Booking ID: " << bookId << endl;
}

void disBooking(int uid) {
    ifstream bookingFile("booking.txt");
    if (!bookingFile.is_open()) {
        cout << "Cannot access booking.txt" << endl;
        return;
    }

    string line;
    bool found = false;
    cout << "Bookings for User ID: " << uid << endl;
    cout << "------------------------------------------" << endl;
    cout << "Booking ID | Date       | Pet Name" << endl;
    cout << "------------------------------------------" << endl;

    while (getline(bookingFile, line)) {
        stringstream bookingSS(line);
        string bookid, userId, date, petName;
        getline(bookingSS, bookid, ',');
        getline(bookingSS, userId, ',');
        getline(bookingSS, date, ',');
        getline(bookingSS, petName, ',');

        if (stoi(userId) == uid) {
            cout << bookid << "         | " << date << " | " << petName << endl;
            found = true;
        }
    }

    bookingFile.close();

    if (!found) {
        cout << "No bookings found for User ID: " << uid << endl;
    }

    cout << "------------------------------------------" << endl;
}

void delbooking(int uid) {
    cout << "Enter the Booking ID want to delete: ";
    int delbookid;
    cin >> delbookid;

    ofstream tempbooking("temp_booking.txt", ios::app);
    if (!tempbooking.is_open()) {
        cout << "Cannot access temp_booking.txt" << endl;
        return;
    }

    ifstream bookingFile("booking.txt");
    if (!bookingFile.is_open()) {
        cout << "Cannot access booking.txt" << endl;
        return;
    }

    string line;
    while (getline(bookingFile, line)) {
        stringstream bookingSS(line);
        string bookid, userId, date, frontptr;
        getline(bookingSS, bookid, ',');
        getline(bookingSS, userId, ',');
        getline(bookingSS, date, ',');
        getline(bookingSS, frontptr, ',');

        if (stoi(bookid) != delbookid) {
            tempbooking << line << "\n";
        }
    }


    bookingFile.close();
    tempbooking.close();


    remove("booking.txt");
    rename("temp_booking.txt", "booking.txt");

    cout << "Booking with ID " << delbookid << " has been deleted." << endl;
}

void sortAndSaveBookings() {
    const int MAX_ITEMS = 1000;

    struct Item {    //create a structure call Item
        int bookId;
        int uid;
        int day, month, year;
        string petName;
    };

    Item items[MAX_ITEMS]; // the array is called item's'
    int itemCount = 0;


    ifstream inFile("booking.txt");
    if (!inFile.is_open()) {
        cout << "Error: Unable to open booking.txt for reading.\n";
        return;
    }

    string line;
    while (getline(inFile, line) && itemCount < MAX_ITEMS) {
        stringstream iss(line);
        string storedBookID, storedUID, storedDay, storedMonth, storedYear, storedPetName;

        getline(iss, storedBookID, ',');
        getline(iss, storedUID, ',');

        string date;
        getline(iss, date, ',');
        stringstream dateStream(date);
        getline(dateStream, storedDay, '-');
        getline(dateStream, storedMonth, '-');
        getline(dateStream, storedYear, '-');

        getline(iss, storedPetName);

        items[itemCount++] = {   //now write in the date into the item's' array, abit different due to struc
            stoi(storedBookID),
            stoi(storedUID),
            stoi(storedDay),
            stoi(storedMonth),
            stoi(storedYear),
            storedPetName
        };
    }
    inFile.close();


    for (int i = 1; i < itemCount; ++i) {
        Item key = items[i];
        int j = i - 1;


        while (j >= 0 && (   //sorting part here
            items[j].year > key.year ||
            (items[j].year == key.year && items[j].month > key.month) ||
            (items[j].year == key.year && items[j].month == key.month && items[j].day > key.day)
        )) {
            items[j + 1] = items[j];
            j--;
        }
        items[j + 1] = key;
    }


    ofstream tempFile("temp_booking.txt");
    if (!tempFile.is_open()) {
        cout << "Error: Unable to create temporary file for sorting.\n";
        return;
    }

    for (int i = 0; i < itemCount; ++i) {   //enter the array into the temp file
        tempFile << items[i].bookId << ","
                 << items[i].uid << ","
                 << items[i].day << "-" << items[i].month << "-" << items[i].year << ","
                 << items[i].petName << endl;
    }
    tempFile.close();

    remove("booking.txt");  //remove it
    rename("temp_booking.txt", "booking.txt"); //rename it

    cout << "Bookings sorted successfully and saved to booking.txt!\n";
}
