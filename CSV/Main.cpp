
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

extern "C" char* strptime(const char* s,
    const char* f,
    struct tm* tm) {
    // Isn't the C++ standard lib nice? std::get_time is defined such that its
    // format parameters are the exact same as strptime. Of course, we have to
    // create a string stream first, and imbue it with the current C locale, and
    // we also have to make sure we return the right things if it fails, or
    // if it succeeds, but this is still far simpler an implementation than any
    // of the versions in any of the C standard libraries.
    std::istringstream input(s);
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, f);
    if (input.fail()) {
        return nullptr;
    }
    return (char*)(s + input.tellg());
}
int dates_increase(const void* d1, const void* d2)
{
    struct tm date_1 = *(const struct tm*)d1;
    struct tm date_2 = *(const struct tm*)d2;
    double d = difftime(mktime(&date_1), mktime(&date_2));
    return (d < 0) - (d > 0);
}
int main(void)
{
   //struct tm my_tm;
    struct tm testArray[3];
    string test = "Thu Mar 11 21:04:09 IST 2021";
    const char* in_buffer = test.c_str();    
     test = "Thu Mar 11 21:04:02 IST 2021";
    const char* in_buffer1 = test.c_str();   
    test = "Thu Mar 11 21:04:20 IST 2021";
    const char* in_buffer2 = test.c_str();
    char out_buffer[80];
        time_t t;

    /* Convert the string to a struct tm. */
      
            memset(&testArray[0], 0, sizeof(struct tm));
            strptime(in_buffer, "%a %b %d %T IST %Y", &testArray[0]);
            memset(&testArray[1], 0, sizeof(struct tm));
            strptime(in_buffer1, "%a %b %d %T IST %Y", &testArray[1]); 
            memset(&testArray[2], 0, sizeof(struct tm));
            strptime(in_buffer2, "%a %b %d %T IST %Y", &testArray[2]);
       

            qsort(testArray,3, sizeof * testArray, dates_increase);

    /* Convert the struct tm to a time_t (to fill in the
     * missing fields). */
    t = mktime(&testArray[0]);

    /* Convert the time back to a string. */
    strftime(out_buffer, 80, "That's %D (a %A), at %T",
        localtime(&t));
    printf("%s\n", out_buffer);

    return EXIT_SUCCESS;
}