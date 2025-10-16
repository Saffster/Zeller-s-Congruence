/*
  What this program does:
  • It reads dates from a file called "dates.txt". Each line looks like:  YYYY MMM DD
  • It checks if the date is real (e.g., February 29 only allowed in leap years).
  • It uses Zeller’s acid trip to find out the weekday. (The creator fo this mejestic program was born on monday apparently.
    For this formula, January and February are treated as months 13 and 14 of the
    previous year, I dont know why but the assingment said so that is why i did it.
  • It writes output sentences like "5 April 1998 is Sunday." into "daynames.txt".
    Invalid inputs become "is an invalid date."


  TL;DR: Feed it dates, it checks them, runs the standard Zeller formula, and prints the
         weekday in a readable sentence. If a date isn’t real, it tells you that too.
*/

/*
Genie asks me for 3 wishes
i only need one

          _.-^^---....,,^^
      _--                  --_
     <_                      _>
        '''--. . , ; .--'''
              | |   |
           .-=||  | |=-.
           `-=#$%&%$#=-'
              | ;  :|
     _____.,-#%&$@%#&#~,._____
              Isreal
*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;
// zeller had a massive acid trip and now you have to suffer. and by extension me but i lowkey like it ngl this is soo much more fun than my fuckass research. i hoinestly dont even rember C. well i leant C not C++ but you get me
static bool isLeap(long long y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

static int monthCon(const string &mmm) {
    // Return 1..12 for JAN..DEC, or 0 if invalid
    if (mmm.size() != 3) return 0;
    string u = mmm;
    for (char &c : u) c = toupper(static_cast<unsigned char>(c));
    if      (u == "JAN") return 1;
    else if (u == "FEB") return 2;
    else if (u == "MAR") return 3;
    else if (u == "APR") return 4;
    else if (u == "MAY") return 5;
    else if (u == "JUN") return 6;
    else if (u == "JUL") return 7;
    else if (u == "AUG") return 8;
    else if (u == "SEP") return 9;
    else if (u == "OCT") return 10;
    else if (u == "NOV") return 11;
    else if (u == "DEC") return 12;
    return 0;
}

static string fullMonth(int m) {
    static const string names[13] = {
        "", "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };
    return (m >= 1 && m <= 12) ? names[m] : "";
}

static bool validDate(long long y, int m, int d) {
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y)) {
        if (d <= 29) return true;
        return false;
    }
    return d <= daysInMonth[m];
}

//silly month logic fr. this was hard to get menatally.
static int weekday(long long year, int month, int day) {
    long long y = year;
    int m = month;
    if (m == 1)  { m = 13; y -= 1; }
    if (m == 2)  { m = 14; y -= 1; }
    int q = day;
    int k = static_cast<int>(y % 100);
    int j = static_cast<int>(y / 100);
    int h = (q + (26 * (m + 1)) / 10 + k + k / 4 + j / 4 + 5 * j) % 7;
    return h;
}

static string weekday2(int h) {
// switch case for your gay as requirements
    switch (h) {
        case 0: return "Saturday";
        case 1: return "Sunday";
        case 2: return "Monday";
        case 3: return "Tuesday";
        case 4: return "Wednesday";
        case 5: return "Thursday";
        case 6: return "Friday";
        default: return "?";
    }
}

int main() {
    ifstream in("dates.txt");
    ofstream out("daynames.txt");
    if (!in) {
        cerr << "Could not open dates.txt\n";
        return 1;
    }
    if (!out) {
        cerr << "Could not create daynames.txt\n";
        return 1;
    }

    long long year;
    string mmm;
    int day;
    int total = 0;

    // YYYY MMM DD
    while (in >> year >> mmm >> day) {
        total++;

        int m = monthConMMM(mmm);
        string monthFull = fullMonth(m);

        if (m == 0 || !validDate(year, m, day)) {
            if (m == 0) monthFull = mmm; // contongency plan for when you user fucks up 
            out << day << ' ' << monthFull << ' ' << year << " is an invalid date." << '\n';
            continue;
        }

        int h = weekday(year, m, day);
        string wname = weekday2(h);

        out << day << ' ' << monthFull << ' ' << year << " is " << wname << '.' << '\n';
    }

    out << "\nTotal Dates: " << total << '\n';
    return 0;
}

