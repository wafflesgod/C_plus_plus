#include "utilities.hpp"
#include <sstream> // For stringstream
#include <string>  // For string
#include <cstdlib> // For std::stoi

// Function definitions
int convertDateToComparableFormat(const std::string& date) {
    std::stringstream ss(date);
    std::string day, month, year;
    getline(ss, day, '-');
    getline(ss, month, '-');
    getline(ss, year, '-');
    return std::stoi(year + month + day); // Combine year, month, and day into YYYYMMDD format
}

bool isEarlierDate(int date1, int date2) {
    return date1 < date2;
}
