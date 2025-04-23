#ifndef BOOKING_HPP
#define BOOKING_HPP

#include <string>

/*class Calendar {
private:
    int year, month;
    int bookings[31];

    bool isLeapYear(int year);
    int getStartDay(int month, int year);

public:
    Calendar(int year, int month);
    int getDaysInMonth(int month, int year);
    void displayCalendar();
    bool bookDay(int day);
};
*/

int generateBookId();
void addBooking(int uid);
void disBooking(int uid);
void delbooking(int uid);
void sortAndSaveBookings();

#endif
