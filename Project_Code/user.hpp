#ifndef USER_HPP
#define USER_HPP
#include <string>

using namespace std;

void newuser();
bool login(int &uid, string &username);
int getid();
int getPetID();
void dispet(int uid);
void addPets(int uid);
void delPet(int uid);
void editPet(int uid);
void PetEditMenu(int uid);
void UserMenu(int uid);

#endif
