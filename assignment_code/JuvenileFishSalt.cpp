#include <iostream>
using namespace std;

char response;

void error(){
    while (response != 'Y' && response != 'y' && response != 'N' && response != 'n') {
            cout << "\nYou could only enter 'Y' or 'N'. Please enter again: ";
            cin >> response;
        }
}

void jun_salt(){
    double tank[3];

    cout << "\t\t\t\t\t\t*Juvenile Fish Stock Calculator (Salt Water)* " << endl;
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

int main() {
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
                    //main menu void
            }
        }
    }while (response == 'Y' || response == 'y');

    cout << endl <<"\n\nHope we've been able to help you out!\n\n";
    //main menu void

    return 0;
}
