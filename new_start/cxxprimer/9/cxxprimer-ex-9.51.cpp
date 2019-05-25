#include <string>
#include <iostream>

using std::string;
const string letters("ABCDEFGHIJKMLNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;

public:
    Date(const string& date);
    void printer();
};

// convert Month string to Integer
unsigned monthMap(const string& mo) {
    if (mo == "Jan" || mo == "January")
        return 1;
    else if (mo == "Feb" || mo == "February")
        return 2;
    else if (mo == "Mar" || mo == "March")
        return 3;
    else if (mo == "Apr" || mo == "April")
        return 4;
    else if (mo == "May")
        return 5;
    else if (mo == "Jun" || mo == "June")
        return 6;
    else if (mo == "Jul" || mo == "July")
        return 7;
    else if (mo == "Aug" || mo == "August")
        return 8;
    else if (mo == "Sep" || mo == "September")
        return 9;
    else if (mo == "Oct" || mo == "October")
        return 10;
    else if (mo == "Nov" || mo == "November")
        return 11;
    else if (mo == "Dec" || mo == "December")
        return 12;
    else
        throw "BAD MONTH";
}

Date::Date(const string& date) {
    size_t pos = 0;
    // case analysis
    if ((pos = date.find(',')) != string::npos)
    { // case 1
        year = std::stoul(
                date.substr(pos + 1)
                );
        auto mpos0 = date.find_first_of(letters);
        auto mpos1 = date.find_last_of(letters);
        month = monthMap(
                date.substr(mpos0, mpos1 + 1 - mpos0)
                );
        day = std::stoul(
                date.substr(mpos1 + 1, pos - mpos1 - 1)
                );
        // std::cout << "year: " << year
        //     << "\nmonth: " << month
        //     << "\nday: " << day;
    } else if ((pos = date.find('/')) != string::npos)
    { // case 2
        auto pos1 = date.find_last_of('/');
        year = std::stoul(date.substr(pos1 + 1));
        month = std::stoul(
                date.substr(0, pos - 0)
                );
        day = std::stoul(
                date.substr(pos + 1, pos1 - pos - 1)
                );
        // std::cout << "year: " << year
        //     << "\nmonth: " << month
        //     << "\nday: " << day;
    } else { // case 3
        pos = date.find(' ');
        auto pos1 = date.find_last_of(' ');
        year = std::stoul(
                date.substr(pos1 + 1)
                );
        month = monthMap(
                date.substr(0, pos - 0)
                );
        day = std::stoul(
                date.substr(pos + 1, pos1 - pos - 1)
                );
        // std::cout << "year: " << year
        //     << "\nmonth: " << month
        //     << "\nday: " << day;
    }
}

void Date::printer() {
    std::cout << "year: " << year
        << "\nmonth: " << month
        << "\nday: " << day
        << std::endl;
}

// test
int main() {
    Date d1("Feb 03 2019");
    Date d2("Oct 17, 1993");
    Date d3("01/24/1995");
    d1.printer();
    d2.printer();
    d3.printer();
    return 0;
}
