#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> // Include cstdlib for atof

using namespace std;

struct Workout {
    string type;
    double duration; // in minutes
    double calories; // burned
};

class FitnessTracker {
private:
    vector<Workout> workouts;

public:
    void logWorkout(const string type, double duration, double calories) {
        Workout w;
        w.type = type;
        w.duration = duration;
        w.calories = calories;
        workouts.push_back(w);
    }

    void viewWorkouts() const {
        for (size_t i = 0; i < workouts.size(); ++i) {
            cout << "Workout: " << workouts[i].type 
                 << ", Duration: " << workouts[i].duration 
                 << " mins, Calories: " << workouts[i].calories << endl;
        }
    }

    double getTotalCaloriesBurned() const {
        double total = 0;
        for (size_t i = 0; i < workouts.size(); ++i) {
            total += workouts[i].calories;
        }
        return total;
    }

    void saveToFile(const string filename) const {
        ofstream file(filename.c_str());
        if (file.is_open()) {
            for (size_t i = 0; i < workouts.size(); ++i) {
                file << workouts[i].type << "," 
                     << workouts[i].duration << "," 
                     << workouts[i].calories << endl;
            }
            file.close();
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

    void loadFromFile(const string filename) {
        ifstream file(filename.c_str());
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    string type = line.substr(0, pos1);
                    double duration = atof(line.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
                    double calories = atof(line.substr(pos2 + 1).c_str());
                    logWorkout(type, duration, calories);
                }
            }
            file.close();
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }
};

int main() {
    FitnessTracker tracker;
    tracker.loadFromFile("workouts.txt");

    int choice;
    do {
        cout << "1. Log Workout\n2. View Workouts\n3. Total Calories Burned\n4. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string type;
            double duration, calories;
            cout << "Enter workout type: ";
            cin.ignore();
            getline(cin, type);
            cout << "Enter duration (in minutes): ";
            cin >> duration;
            cout << "Enter calories burned: ";
            cin >> calories;
            tracker.logWorkout(type, duration, calories);
        } else if (choice == 2) {
            tracker.viewWorkouts();
        } else if (choice == 3) {
            cout << "Total Calories Burned: " << tracker.getTotalCaloriesBurned() << endl;
        }
    } while (choice != 4);

    tracker.saveToFile("workouts.txt");
    return 0;
}
