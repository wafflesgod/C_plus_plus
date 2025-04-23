#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include "user.hpp"
#include <iomanip>


using namespace std;


    void addPets(int uid) {
    int numPets;
    cout << "How many pets do you want to add? ";
    cin >> numPets;

    ofstream petfile("pet.txt", ios::app);

    for (int i = 0; i < numPets; ++i) {
        int PetID = getPetID();

        string type, name, age, gender;
        cout << "Enter details for pet " << i + 1 << ":\n";
        cout << "Type: ";
        cin >> type;
        cout << "Name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;
        cout << "Gender: ";
        cin >> gender;

        petfile << PetID << "," << uid << "," << name << "," << type << "," << age << "," << gender << "\n";

    }
        petfile.close();
        cout << "Pet Saved Successfully" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("pause");
        system("cls");

    }

    void newuser() {
    string uname, passwd, gender, tel;
    int uid;
    int getid();

    cout << "Enter Your Name Please: ";
    cin.ignore();
    getline(cin, uname);
    cout << "Enter Password: ";
    cin >> passwd;
    cout << "What is your Gender?(M for Male /F for Female): ";
    cin >> gender;
     if ((gender != "M")&&(gender != "m")&&(gender != "F")&&(gender != "f")){
        cout << "Please Enter Valid Gender \n";
        newuser();
     }
    cout << "Your Phone Number: ";
    cin >> tel;

    uid = getid();

    ofstream file("users.txt", ios::app); //app mean append, prevent overwritting

    if (file.is_open()) {
        file << uid << "," << uname << "," << passwd << "," << gender << "," << tel << "\n";
        file.close();
        cout << "\nWelcome to Pet Hotel Management System!\n" << endl;
        cout << endl;
        cout << "Your ID is " << uid << endl;
        system("pause");
        system("cls");
    } else {
        cout << "Some error occurs" << endl;
    }
}

   int getid() {
    static int lastUid = 1000;

    ifstream userFile("users.txt");
    if (!userFile.is_open()) {
        return lastUid++;
    }

    string line;
    while (getline(userFile, line)) {
        stringstream ss(line);
        string storedUid;
        getline(ss, storedUid, ',');
        lastUid = stoi(storedUid);
    }


    userFile.close();

     return ++lastUid;
}

   int getPetID() {
    static int lastPetid = 0;

    ifstream petFile("pet.txt");
    if (!petFile.is_open()) {
        return lastPetid++;  // If the file does not exist, return the current ID and increment it
    }

    string line;
    while (getline(petFile, line)) {
        stringstream ss(line);
        string storedPetid;
        getline(ss, storedPetid, ',');

        // Compare and keep track of the highest Pet ID
        int currentPetId = stoi(storedPetid);
        if (currentPetId > lastPetid) {
            lastPetid = currentPetId;
        }
    }

    petFile.close();

    return ++lastPetid;  // Return the next Pet ID (incremented)
}

   bool login(int &uid, string &username) {
    string inputUid;
    string inputPasswd;

    cout << "Enter UID or Username: ";
    cin >> inputUid;
    cout << "Enter Password: ";
    cin >> inputPasswd;

    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open users.txt file.\n";
        return false;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string storedUid, storedUname, storedPasswd, storedGender, storedTel;

        getline(ss, storedUid, ',');
        getline(ss, storedUname, ',');
        getline(ss, storedPasswd, ',');
        getline(ss, storedGender, ',');
        getline(ss, storedTel, ',');

        if ((storedUid == inputUid && storedPasswd == inputPasswd) ||
            (storedUname == inputUid && storedPasswd == inputPasswd)) {
            uid = stoi(storedUid);
            username = storedUname;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void dispet(int uid) {
    ifstream petFile("pet.txt");
    if (!petFile.is_open()) {
        cout << "Error: Unable to open pet file." << endl;
        return;
    }

    cout << "Pets for User ID: " << uid << endl;
    cout << "----------------------------------------" << endl;

    string line;

    bool found = false;

    while (getline(petFile, line)) {
        stringstream ss(line);
        string petId, storeduid, type, name, age, gender, nextPtr;

        getline(ss, petId, ',');
        getline(ss, storeduid, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');

        if (stoi(storeduid) == uid) {
            found = true;
            cout << "Pet ID: " << petId << " | Name: " << name << " | Type: " << type
                 << " | Age: " << age << " | Gender: " << gender << endl;
        }
    }

    if (!found) {
        cout << "No pets found for User ID: " << uid << endl;
    }

    petFile.close();

}

void delPet(int uid) {
    dispet(uid);
    cout << "Enter the Pet ID you want to delete: ";
    int delPetId;
    cin >> delPetId;

    ofstream tempPetFile("temp_pet.txt", ios::app);
    if (!tempPetFile.is_open()) {
        cout << "Cannot open temp_pet.txt" << endl;
        return;
    }

    ifstream petFile("pet.txt");
    if (!petFile.is_open()) {
        cout << "Cannot access pet.txt" << endl;
        return;
    }

    string line;
    while (getline(petFile, line)) {
        stringstream petSS(line);
        string storedpetID, storedUID, storedName, storedType, storedAge, storedGender;

        getline(petSS, storedpetID, ',');
        getline(petSS, storedUID, ',');
        getline(petSS, storedName, ',');
        getline(petSS, storedType, ',');
        getline(petSS, storedAge, ',');
        getline(petSS, storedGender, ',');

        if (stoi(storedpetID) != delPetId) {
            tempPetFile << line << "\n";
        }
    }
    petFile.close();
    tempPetFile.close();

    remove("pet.txt");
    rename("temp_pet.txt", "pet.txt");

    cout << "Pet with ID " << delPetId << " has been deleted." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("pause");
    system("cls");
}

void editPet(int uid) {
    dispet(uid);
    cout << "Enter the Pet ID you want to edit: ";
    int editPetId;
    cin >> editPetId;
    cin.ignore(); // Clears the input buffer

    ofstream tempPetFile("temp_pet.txt", ios::out); // Temporary file for pet updates
    if (!tempPetFile.is_open()) {
        cout << "Cannot access temp_pet.txt" << endl;
        return;
    }

    ifstream petFile("pet.txt");
    if (!petFile.is_open()) {
        cout << "Cannot access pet.txt" << endl;
        return;
    }

    bool petFound = false;
    string line, storedPetID, storedUID, storedName, storedType, storedAge, storedGender;

    // Update pet.txt
    while (getline(petFile, line)) {
        stringstream petSS(line);
        getline(petSS, storedPetID, ',');
        getline(petSS, storedUID, ',');
        getline(petSS, storedName, ',');
        getline(petSS, storedType, ',');
        getline(petSS, storedAge, ',');
        getline(petSS, storedGender, ',');

        if (stoi(storedPetID) == editPetId && stoi(storedUID) == uid) {
            petFound = true;

            string newName, newType, newAge, newGender;

            cout << "Editing details for Pet ID " << editPetId << ":\n";

            cout << "Current Name: " << storedName << "\n";
            cout << "Enter New Name (or press Enter to skip): ";
            getline(cin, newName);

            cout << "Current Type: " << storedType << "\n";
            cout << "Enter New Type (or press Enter to skip): ";
            getline(cin, newType);

            cout << "Current Age: " << storedAge << "\n";
            cout << "Enter New Age (or press Enter to skip): ";
            getline(cin, newAge);

            cout << "Current Gender: " << storedGender << "\n";
            cout << "Enter New Gender (or press Enter to skip): ";
            getline(cin, newGender);

            // Replace empty inputs with current values
            if (newName.empty()) newName = storedName;
            if (newType.empty()) newType = storedType;
            if (newAge.empty()) newAge = storedAge;
            if (newGender.empty()) newGender = storedGender;

            tempPetFile << storedPetID << "," << storedUID << "," << newName << "," << newType << "," << newAge << "," << newGender << "\n";

            // update booking.txt
            ifstream bookingFile("booking.txt");
            ofstream tempBookingFile("temp_booking.txt", ios::out);

            if (!bookingFile.is_open() || !tempBookingFile.is_open()) {
                cout << "Cannot open!" << endl;
                return;
            }

            string bookingLine, storedBookingID, storedBookingUID, storedBookingDate, storedPetName;

            while (getline(bookingFile, bookingLine)) {
                stringstream bookingSS(bookingLine);
                getline(bookingSS, storedBookingID, ',');
                getline(bookingSS, storedBookingUID, ',');
                getline(bookingSS, storedBookingDate, ',');
                getline(bookingSS, storedPetName, ',');

                if (stoi(storedBookingUID) == uid && storedPetName == storedName) {
                    tempBookingFile << storedBookingID << "," << storedBookingUID << "," << storedBookingDate << "," << newName << "\n";
                } else {
                    tempBookingFile << bookingLine << "\n";
                }
            }

            bookingFile.close();
            tempBookingFile.close();

            remove("booking.txt");
            rename("temp_booking.txt", "booking.txt");

        } else {
            tempPetFile << line << "\n";
        }
    }

    petFile.close();
    tempPetFile.close();

    remove("pet.txt");
    rename("temp_pet.txt", "pet.txt");

    if (petFound) {
        cout << "Update Pending\n";
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Done Update!\n";
    } else {
        cout << "Pet ID not found.\n";
    }

    system("pause");
    PetEditMenu(uid);
}

void PetEditMenu(int uid) {
    system("cls");
    int petChoice;
    cout << "==============\n";
    cout << "Manage Pets:\n";
    cout << "==============\n";
    cout << "1. Add Pet\n";
    cout << "2. Remove Pet\n";
    cout << "3. Edit Pet\n";
    cout << "4. Back\n";
    cout << "Enter your choice: ";
    cin >> petChoice;

    if (petChoice == 1) {
        cout << endl;
        addPets(uid);
    } else if (petChoice == 2) {
        cout << endl;
        delPet(uid);
    } else if (petChoice == 3) {
        cout << endl;
        editPet(uid);
    } else if (petChoice == 4) {
        system("cls");
        UserMenu(uid);
    } else {
        cout << "Invalid choice in Manage Pets.\n";
    }
}
