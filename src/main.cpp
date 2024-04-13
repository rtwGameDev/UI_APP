#include "homePage.h"
#include <iostream>
#include <string>
#include "slint.h"
using namespace std;
struct dateTime {
	string day;
	string month;
	string year;
	string hour;
	string minute;
    string second;
	dateTime() {}
	dateTime(string day, string month, string year, string hour, string minute, string second) {
		this->day = day;
		this->month = month;
		this->year = year;
		this->hour = hour;
		this->minute = minute;
        this->second = second;
	}
	~dateTime() {}
};
void Format(dateTime& date_time) {
    if ((date_time.day).length() == 1) {
        date_time.day = "0" + date_time.day;
    }
    if ((date_time.month).length() == 1) {
        date_time.month = "0" + date_time.month;
    }
    if ((date_time.hour).length() == 1) {
        date_time.hour = "0" + date_time.hour;
    }
    if ((date_time.minute).length() == 1) {
        date_time.minute = "0" + date_time.minute;
    }
    if ((date_time.second).length() == 1) {
        date_time.second = "0" + date_time.second;
    }
}
dateTime getCurrentTime() {
    // struct tm chua cac dinh dang thoi gian
    tm currentTime;

    // time_t tra lai thoi gian tihnh bang giay ke tu Epoch (01/01/1970)
    time_t now = time(0);

    // chuyen doi tu s sang doi tuong currentTime;
    localtime_s(&currentTime, &now);

    dateTime date_time;
    date_time.day = to_string(currentTime.tm_mday);
    date_time.month = to_string(currentTime.tm_mon + 1);
    date_time.year = to_string(currentTime.tm_year + 1900);
    date_time.hour = to_string(currentTime.tm_hour);
    date_time.minute = to_string(currentTime.tm_min);
    date_time.second = to_string(currentTime.tm_sec);
    Format(date_time);

    return date_time;
}
string getStringDATE_TIME(dateTime date_time) {
	string time_to_string = "";
	time_to_string = time_to_string + date_time.day + "/"
		+ date_time.month + "/"
		+ date_time.year + " "
		+ date_time.hour + ":"
		+ date_time.minute + ":"
        + date_time.second;
	return time_to_string;
}
void callback() {
    cout << 1;
}
int main() {
    dateTime curr = getCurrentTime();
    cout << getStringDATE_TIME(curr);
    auto ui = homePage::create();
    
    ui->global<functionAPP>().on_handleFilterListFlightPassPageByCPP([&] (slint::SharedString a, slint::SharedString b, slint::SharedString c, slint::SharedString d, slint::SharedString e) {
        std::string aa(a);
        std::string bb(b);
        std::string cc(c);
        std::string dd(d);
        std::string ee(e);
        cout << "--" << aa << "--" << bb << "--" << cc << "--" << dd << "--" << ee << "--" << endl; 
        return;
    });
    
    slint::Timer a;
    a.start(slint::cbindgen_private::TimerMode::Repeated, std::chrono::seconds(1), 
        [=]() {
            string currentTime = getStringDATE_TIME(getCurrentTime());
            auto curr = slint::SharedString(currentTime);
            ui->global<functionAPP>().set_currentTime(curr);
        }
    );
    ui->run();
    cout << 1;
    return 0;
}
