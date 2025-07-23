
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Event {
    string date;
    string time;
    string description;
};

void addEvent(vector<Event>& events) {
    Event newEvent;
    cout << "Enter event date (YYYY-MM-DD): ";
    cin >> newEvent.date;
    cout << "Enter event time (HH:MM): ";
    cin >> newEvent.time;
    cin.ignore();
    cout << "Enter event description: ";
    getline(cin, newEvent.description);
    events.push_back(newEvent);
    cout << "Event added successfully!\n";
}

void showEvents(const vector<Event>& events) {
    if (events.empty()) {
        cout << "No events scheduled.\n";
        return;
    }
    cout << "\nUpcoming Events:\n";
    for (const auto& e : events) {
        cout << e.date << " " << e.time << " - " << e.description << endl;
    }
}

void saveEventsToFile(const vector<Event>& events, const string& filename) {
    ofstream file(filename);
    for (const auto& e : events) {
        file << e.date << "," << e.time << "," << e.description << endl;
    }
    file.close();
}

void loadEventsFromFile(vector<Event>& events, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Event e;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            e.date = line.substr(0, pos1);
            e.time = line.substr(pos1 + 1, pos2 - pos1 - 1);
            e.description = line.substr(pos2 + 1);
            events.push_back(e);
        }
    }
    file.close();
}

int main() {
    vector<Event> events;
    string filename = "events.txt";
    loadEventsFromFile(events, filename);
    int choice;
    do {
        cout << "\nEvent Reminder Menu:\n";
        cout << "1. Add Event\n";
        cout << "2. Show Events\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEvent(events);
                break;
            case 2:
                showEvents(events);
                break;
            case 3:
                saveEventsToFile(events, filename);
                cout << "Exiting... Events saved.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
