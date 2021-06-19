
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
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

struct CSV
{
    string Partition, Project, Machine, CPUModel, NumofCPU, memory, flow, RunTime;
    struct tm StartDate, FinishDate;
    struct tm* CalcStartTime;
    struct tm* Duration ;
};
double differenceStart(const CSV& d1, const CSV& d2)
{
    struct tm date_1 = d1.StartDate;
    struct tm date_2 = d2.StartDate;
    return difftime(mktime(&date_1), mktime(&date_2));
}
bool dates_increase(const CSV& d1, const CSV& d2)
{
    if (d1.RunTime == "Aborted")
        return false;
    if (d2.RunTime == "Aborted")
        return true;

    return differenceStart(d1, d2) < 0;
}
class csvDates
{
    vector<CSV> date;
public:
    void readCSV(string fileName)
    {
        fstream file;
        file.open("test.csv", ios::in);
        CSV temp;
        string  StartDate, FinishDate;
        const char* in_buffer;
        const char* in_buffer1;
        while (getline(file, temp.Partition, ',')) {

            getline(file, temp.Project, ',');

            getline(file, temp.Machine, ',');

            getline(file, temp.CPUModel, ',');

            getline(file, temp.NumofCPU, ',');

            getline(file, temp.memory, ',');

            getline(file, temp.flow, ',');

            getline(file, temp.RunTime, ',');

            getline(file, StartDate, ',');
            in_buffer = StartDate.c_str();
            memset(&temp.StartDate, 0, sizeof(struct tm));
            strptime(in_buffer, "%a %b %d %T IST %Y", &temp.StartDate);


            getline(file, FinishDate);
            in_buffer1 = FinishDate.c_str();
            memset(&temp.FinishDate, 0, sizeof(struct tm));
            strptime(in_buffer1, "%a %b %d %T IST %Y", &temp.FinishDate);
            date.push_back(temp);

        }
        sort(date.begin(), date.end(), dates_increase);
        
    }
    /*void sortCSV()
    {
        sort(date.begin(), date.end(),csvDates:: dates_increase);
    }*/
    void countDuration()
    {
        time_t CalcStart, sec;
        double diff;
        for (int i = 0; i < date.size(); ++i)
        {
            if (date[i].RunTime != "Aborted")
            {
               /* //CalcStart = differenceStart(date[i], date[0]);
                date[i].CalcStartTime = localtime(new time_t(differenceStart(date[i], date[0])));
                //sec = differenceDur(date[i]);
                date[i].Duration = localtime(new time_t(differenceDur(date[i])));*/
                diff=differenceStart(date[i], date[0]);
            }
        }

    }
    void secTohours(int total)
    {
        int  seconds, hours, minutes;
        minutes = total / 60;
        seconds = total % 60;
        hours = minutes / 60;
        minutes = minutes % 60;
        return "" + hours + "" + minutes + ":" + seconds;
    }

    double differenceDur(const CSV& d1)
    {
        struct tm date_2 = d1.StartDate;
        struct tm date_1 = d1.FinishDate;
        return difftime(mktime(&date_1), mktime(&date_2));
    }

    void printIntoCSV(string fileName)
    {
        fstream fout;
        char out_buffer[120];
        time_t t;

        fout.open("reportcard.csv", ios::out | ios::app);
        for (int i = 0; i < date.size(); ++i)
        {
            fout << date[i].Partition << ","
                << date[i].Project << ","
                << date[i].Machine << ","
                << date[i].CPUModel << ","
                << date[i].NumofCPU << ","
                << date[i].memory << ","
                << date[i].flow << ","
                << date[i].RunTime << ",";
            t = mktime(&date[i].StartDate);
            strftime(out_buffer, 120, "%a %b %d %T IST %Y",
                localtime(&t));
            fout << out_buffer << ",";
            if (date[i].RunTime != "Aborted")
            {
                
                t = mktime(&date[i].FinishDate);
                strftime(out_buffer, 120, "%a %b %d %T IST %Y",
                    localtime(&t));
                fout << out_buffer << ",";
                t = mktime(date[i].CalcStartTime);
                strftime(out_buffer, 120, "%T",
                    localtime(&t));
                fout << out_buffer << ",";
                t = mktime(date[i].Duration);
                strftime(out_buffer, 120, "%T",
                    localtime(&t));
                fout << out_buffer << "\n";
            }
            else
            {
                fout << "Failed,Failed,0\n";
            }


        }
        fout.close();
    }

};


int main(void)
{
    
    csvDates temp;
    temp.readCSV("");
    //temp.sortCSV();
    temp.countDuration();
    temp.printIntoCSV("");
    //struct tm my_tm;
    /*struct tm testArray[3];
    string test = "Thu Mar 11 21:04:09 IST 2021";
    const char* in_buffer = test.c_str();    
        string test1 = "Thu Mar 11 21:04:02 IST 2021";
    const char* in_buffer1 = test1.c_str();   
    string test2 = "Thu Mar 11 21:04:20 IST 2021";
    const char* in_buffer2 = test2.c_str();
    char out_buffer[80];
        time_t t;

    /* Convert the string to a struct tm.     
            memset(&testArray[0], 0, sizeof(struct tm));
            strptime(in_buffer, "%a %b %d %T IST %Y", &testArray[0]);
            memset(&testArray[1], 0, sizeof(struct tm));
            strptime(in_buffer1, "%a %b %d %T IST %Y", &testArray[1]); 
            memset(&testArray[2], 0, sizeof(struct tm));
            strptime(in_buffer2, "%a %b %d %T IST %Y", &testArray[2]);
       

            qsort(testArray,3, sizeof * testArray, dates_increase);

    /* Convert the struct tm to a time_t (to fill in the
     * missing fields). 
    t = mktime(&testArray[0]);

    /* Convert the time back to a string. 
    strftime(out_buffer, 80, "That's %D (a %A), at %T",
        localtime(&t));
    printf("%s\n", out_buffer);

    return EXIT_SUCCESS;*/
}