#include <iostream>
#include <regex>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
struct parcTime
{
	int hours;
	int minutes;
	int all_hours = 0;
	int all_minutes = 0;
	bool status = 0;
	parcTime(int h, int m)
	{
		hours = h;
		minutes = m;
	}
	parcTime()
	{
		hours = 0;
		minutes = 0;
	}
};
parcTime parcer(string& str)
{
	regex space_re("\\s+");
	str = regex_replace(str, space_re, "");
	regex rgx("[0-9]{1,2}\:[0-9]{1,2}\\*(CAR)[0-9]+");
	if (regex_match(str, rgx)) {
		int hours = stoi(str.substr(0, 2));
		int minutes = stoi(str.substr(str.find(":") + 1, 2));
		str = str.substr(str.find("*") + 1, str.size());
		if (hours > 24 || minutes > 60)
		{
			throw exception("wrong format");
		}
		return { hours,minutes };
	}
	else
	{
		throw exception("wrong format");
	}
}
void timeParcing(parcTime& car, parcTime exits)
{
	int value = exits.hours * 60 + exits.minutes - car.hours * 60 - car.minutes;
	car.hours = 0;
	car.minutes = 0;
	car.all_hours += value / 60;
	car.all_minutes += value % 60;
	if (car.all_minutes > 59)
	{
		car.all_hours += car.all_minutes / 60;
		car.all_minutes = car.all_minutes % 60;
	}
}
string timeOut(parcTime& car)
{
	string out;
	out += to_string(car.all_hours) + ":";
	if (car.all_minutes < 10)
	{
		out += "0" + to_string(car.all_minutes);
	}
	else
	{
		out += to_string(car.all_minutes);

	}
	return out;


}
bool sortbytime(const pair<string, string>& a,
	const pair<string, string>& b)
{
	int hours1 = stoi(a.first.substr(0, 2));
	int minutes1 = stoi(a.first.substr(a.second.find(":") + 1, 2));

	int hours2 = stoi(b.first.substr(0, 2));
	int minutes2 = stoi(b.first.substr(b.second.find(":") + 1, 2));
	if (hours1 > hours2)
	{
		return true;
	}
	else return minutes1 > minutes2;

}
void commands(string str, map<string, parcTime>& parking)
{
	if (str == "0:00=")
	{
		vector<pair<string, string>> sorted;
		for (auto& car : parking)
		{
			if (car.second.status == 1)
			{
				timeParcing(car.second, { 24,0 });
				sorted.push_back(make_pair(timeOut(car.second), "*" + car.first));
			}
			else
			{
				sorted.push_back(make_pair(timeOut(car.second), car.first));
			}
		}
		sort(sorted.begin(), sorted.end(), sortbytime);
		for (auto s : sorted)
		{
			cout << s.second << " " << s.first << endl;
		}

	}
	else
	{
		parcTime newo = parcer(str);
		if (parking[str].status == 1)
		{
			timeParcing(parking[str], newo);
			cout << "Departure, total parking time : " << timeOut(parking[str]) << endl;
			parking[str].status = 0;
		}



		else
		{

			newo.all_hours += parking[str].all_hours;
			newo.all_minutes += parking[str].all_minutes;
			if (newo.all_minutes > 59)
			{
				newo.all_hours += newo.all_minutes / 60;
				newo.all_minutes = newo.all_minutes % 60;
			}
			parking[str] = newo;
			parking[str].status = 1;
			cout << "Arrival" << endl;
		}

	}
}

int main()
{

	try {
		ifstream f;
		f.open("info.txt");
		map<string, parcTime> parcing;
		string str;
		while (!f.eof())
		{
			f >> str;
			commands(str, parcing);
		}
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	return 0;
}