#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

int main() {
    string eventName;
    int eventHour, eventMinute;

    cout << "Enter event name: ";
    getline(cin, eventName);

    cout << "Enter event hour (24-hour format): ";
    cin >> eventHour;

    cout << "Enter event minute: ";
    cin >> eventMinute;

    cout << "\nEvent reminder set for: " << eventHour << ":" 
         << (eventMinute < 10 ? "0" : "") << eventMinute 
         << " -> " << eventName << endl;

    while (true) {
        // Get current system time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int currentHour = ltm->tm_hour;
        int currentMinute = ltm->tm_min;

        // Check if current time matches the event time
        if (currentHour == eventHour && currentMinute == eventMinute) {
            cout << "\n🔔 Reminder: " << eventName << " is happening now!" << endl;
            break;
        }

        // Sleep for 30 seconds to avoid busy waiting
        this_thread::sleep_for(chrono::seconds(30));
    }

    return 0;
}
