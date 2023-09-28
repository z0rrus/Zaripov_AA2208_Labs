#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Pipe {
public:
    string name;
    double length;
    double diameter;
    bool inRepair;

    Pipe() : name(""), length(0.0), diameter(0.0), inRepair(false) {}

    void readData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter pipe name: ";
        getline(cin, name);
        cout << "Enter pipe length (km): ";
        cin >> length;
        cout << "Enter pipe diameter (cm): ";
        cin >> diameter;
    }

    void displayData() const {
        cout << "Name: " << name << endl;
        cout << "Length: " << length << " km" << endl;
        cout << "Diameter: " << diameter << " cm" << endl;
        cout << "Repair status: " << (inRepair ? "Under repair" : "Operational") << endl;
    }

    void toggleRepairStatus() {
        inRepair = !inRepair;
    }
};

class CompressorStation {
public:
    string name;
    int workshopCount;
    vector<bool> workshopStatus; // Vector to store the operational status of workshops
    double efficiency;

    CompressorStation() : name(""), workshopCount(0), efficiency(0.0) {}

    void readData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter station name: ";
        getline(cin, name);
        cout << "Enter workshop count: ";
        cin >> workshopCount;

        // Initialize the workshopStatus vector with default values (all operational)
        workshopStatus.resize(workshopCount, true);

        cout << "Enter efficiency rating: ";
        cin >> efficiency;
    }

    void displayData() const {
        cout << "Station Name: " << name << endl;
        cout << "Workshop Count: " << workshopCount << endl;

        // Display the operational status of each workshop
        cout << "Workshop Status:" << endl;
        for (int i = 0; i < workshopCount; i++) {
            cout << "Workshop " << i + 1 << ": " << (workshopStatus[i] ? "Operational" : "Not Operational") << endl;
        }

        cout << "Efficiency Rating: " << efficiency << endl;
    }
};

void saveData(const vector<Pipe>& pipes, const vector<CompressorStation>& stations, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Pipe& pipe : pipes) {
            file << "Pipe\n";
            file << pipe.name << "\n";
            file << pipe.length << "\n";
            file << pipe.diameter << "\n";
            file << pipe.inRepair << "\n";
        }
        for (const CompressorStation& station : stations) {
            file << "Station\n";
            file << station.name << "\n";
            file << station.workshopCount << "\n";

            for (bool status : station.workshopStatus) {
                file << status << "\n"; // Сохраняем статус каждого цеха
            }

            file << station.efficiency << "\n";
        }
        file.close();
        cout << "Data successfully saved to the file " << filename << endl;
    }
    else {
        cout << "Error opening the file for saving." << endl;
    }
}

void loadData(vector<Pipe>& pipes, vector<CompressorStation>& stations, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();
        string line;
        while (getline(file, line)) {
            if (line == "Pipe") {
                Pipe pipe;
                getline(file, pipe.name);
                file >> pipe.length;
                file >> pipe.diameter;
                file >> pipe.inRepair;
                pipes.push_back(pipe);
            }
            else if (line == "Station") {
                CompressorStation station;
                getline(file, station.name);
                file >> station.workshopCount;
                station.workshopStatus.resize(station.workshopCount);
                for (int i = 0; i < station.workshopCount; i++) {
                    int status;
                    file >> status; // Загружаем статус каждого цеха
                    station.workshopStatus[i] = (status != 0); // Преобразуем int в bool
                }
                file >> station.efficiency;
                stations.push_back(station);
            }
        }
        file.close();
        cout << "Data successfully loaded from the file " << filename << endl;
    }
    else {
        cout << "Error opening the file for loading." << endl;
    }
}


int main() {
    vector<Pipe> pipes;
    vector<CompressorStation> stations;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add a pipe" << endl;
        cout << "2. Add a compressor station" << endl;
        cout << "3. View all objects" << endl;
        cout << "4. Edit a pipe" << endl;
        cout << "5. Edit a compressor station" << endl;
        cout << "6. Save" << endl;
        cout << "7. Load" << endl;
        cout << "0. Exit" << endl;
        cout << "" << endl;

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please try again." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            continue; // Skip the rest of the loop
        }
        cout << "" << endl;

        switch (choice) {
        case 1: {
            Pipe pipe;
            pipe.readData();
            pipes.push_back(pipe);
            break;
        }
        case 2: {
            CompressorStation station;
            station.readData();
            stations.push_back(station);
            break;
        }
        case 3: {
            cout << "Pipes:" << endl;
            for (const Pipe& pipe : pipes) {
                pipe.displayData();
                cout << endl;
            }
            cout << "Compressor Stations:" << endl;
            for (const CompressorStation& station : stations) {
                station.displayData();
                cout << endl;
            }
            break;
        }
        case 4: {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the name of the pipe to edit: ";
            string pipeName;
            getline(cin, pipeName);
            for (Pipe& pipe : pipes) {
                if (pipe.name == pipeName) {
                    cout << "Choose action: 1. Under repair 2. Operational" << endl;
                    int repairChoice;
                    if (!(cin >> repairChoice)) {
                        cout << "Invalid action choice. Please try again." << endl;
                        cin.clear(); // Clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                        break; // Exit the loop
                    }
                    if (repairChoice == 1) {
                        pipe.inRepair = true;
                        cout << "Status changed to 'Under repair'" << endl;
                    }
                    else if (repairChoice == 2) {
                        pipe.inRepair = false;
                        cout << "Status changed to 'Operational'" << endl;
                    }
                    else {
                        cout << "Invalid action choice." << endl;
                    }
                    break;
                }
            }
            break;
        }
        case 5: {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the name of the compressor station to edit: ";
            string stationName;
            getline(cin, stationName);
            for (CompressorStation& station : stations) {
                if (station.name == stationName) {
                    cout << "Choose workshop to edit (1-" << station.workshopCount << "): ";
                    int workshopChoice;
                    if (!(cin >> workshopChoice) || workshopChoice < 1 || workshopChoice > station.workshopCount) {
                        cout << "Invalid workshop choice. Please try again." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    // Toggle the status of the selected workshop
                    station.workshopStatus[workshopChoice - 1] = !station.workshopStatus[workshopChoice - 1];
                    cout << "Workshop " << workshopChoice << " status changed to '" << (station.workshopStatus[workshopChoice - 1] ? "Operational" : "Not Operational") << "'" << endl;
                    break;
                }
            }
            break;
        }
        case 6: {
            saveData(pipes, stations, "data.txt");
            break;
        }
        case 7: {
            loadData(pipes, stations, "data.txt");
            break;
        }
        case 0: {
            cout << "Exiting the program." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
