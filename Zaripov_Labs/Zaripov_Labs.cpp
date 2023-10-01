#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;
bool flag = false;


void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


class Pipe {
public:
    string name;
    double length;
    double diameter;
    bool inRepair;
    int id; 

    Pipe() : name(""), length(0.0), diameter(0.0), inRepair(false) {
        id = getNextId();
    }

    void readData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter pipe name: ";
        getline(cin, name);

        while (true) {
            cout << "Enter pipe length (km): ";
            if (cin >> length && length >= 0) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a non-negative number for length." << endl;
                clearInput();
            }
        }

        while (true) {
            cout << "Enter pipe diameter (cm): ";
            if (cin >> diameter && diameter >= 0) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a non-negative number for diameter." << endl;
                clearInput();
            }
        }
    }

    void displayData() const {
        cout << "ID: " << id << endl; 
        cout << "Name: " << name << endl;
        cout << "Length: " << length << " km" << endl;
        cout << "Diameter: " << diameter << " cm" << endl;
        cout << "Repair status: " << (inRepair ? "Under repair" : "Operational") << endl;
    }

    void toggleRepairStatus() {
        inRepair = !inRepair;
    }
    
    static void recalculateIds(vector<Pipe>& pipes) {
        for (int i = 0; i < pipes.size(); i++) {
            pipes[i].id = i + 1;
        }
    }

    static int getNextId() {
        static int nextId = 1; 
        return nextId++;
    }
};

class CompressorStation {
public:
    string name;
    int workshopCount;
    vector<bool> workshopStatus;
    double efficiency;
    int id; 

    CompressorStation() : name(""), workshopCount(0), efficiency(0.0) {
        id = getNextId();
    }

    void readData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter station name: ";
        getline(cin, name);

        while (true) {
            cout << "Enter workshop count: ";
            if (cin >> workshopCount && workshopCount >= 0) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a non-negative integer for workshop count." << endl;
                clearInput();
            }
        }

        while (true) {
            cout << "Enter efficiency rating: ";
            if (cin >> efficiency && efficiency >= 0) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a non-negative number for efficiency rating." << endl;
                clearInput();
            }
        }

        workshopStatus.resize(workshopCount, true);
    }

    void displayData() const {
        cout << "ID: " << id << endl;
        cout << "Station Name: " << name << endl;
        cout << "Workshop Count: " << workshopCount << endl;
        cout << "Workshop Status:" << endl;
        for (int i = 0; i < workshopCount; i++) {
            cout << "Workshop " << i + 1 << ": " << (workshopStatus[i] ? "Operational" : "Not Operational") << endl;
        }
        cout << "Efficiency Rating: " << efficiency << endl;
    }

    static void recalculateIds(vector<CompressorStation>& stations) {
        for (int i = 0; i < stations.size(); i++) {
            stations[i].id = i + 1;
        }
    }

    static int getNextId() {
        static int nextId = 1; 
        return nextId++;
    }
};


void editPipeStatus(vector<Pipe>& pipes) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter the ID of the pipe to edit: ";
    int pipeId;
    if (!(cin >> pipeId) || pipeId < 1 || pipeId > pipes.size()) {
        cout << "Invalid ID. Please try again." << endl;
        clearInput();
        return;
    }

    Pipe& pipe = pipes[pipeId - 1]; 

    cout << "Choose action: 1. Under repair 2. Operational" << endl;
    int repairChoice;
    if (!(cin >> repairChoice)) {
        cout << "Invalid action choice. Please try again." << endl;
        clearInput();
        return;
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
}

void editWorkshopStatus(vector<CompressorStation>& stations) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter the ID of the compressor station to edit: ";
    int stationId;
    if (!(cin >> stationId) || stationId < 1 || stationId > stations.size()) {
        cout << "Invalid ID. Please try again." << endl;
        clearInput();
        return;
    }

    CompressorStation& station = stations[stationId - 1]; 

    cout << "Choose workshop to edit (1-" << station.workshopCount << "): ";
    int workshopChoice;
    if (!(cin >> workshopChoice) || workshopChoice < 1 || workshopChoice > station.workshopCount) {
        cout << "Invalid workshop choice. Please try again." << endl;
        clearInput();
        return;
    }

    station.workshopStatus[workshopChoice - 1] = !station.workshopStatus[workshopChoice - 1];
    cout << "Workshop " << workshopChoice << " status changed to '" << (station.workshopStatus[workshopChoice - 1] ? "Operational" : "Not Operational") << "'" << endl;
}

void saveData(const vector<Pipe>& pipes, const vector<CompressorStation>& stations, const string& filename) {
    ofstream file;
    if (flag) {
        file.open(filename);
    }
    else {
        file.open(filename, ios::app);
    }

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
                file << status << "\n";
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
    flag = true;
    ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();
        string line;
        while (getline(file, line)) {
            if (line == "Pipe") {
                Pipe pipe;
                pipe.id = pipes.size() + 1; 
                getline(file, pipe.name);
                file >> pipe.length;
                file >> pipe.diameter;
                file >> pipe.inRepair;
                pipes.push_back(pipe);
            }
            else if (line == "Station") {
                CompressorStation station;
                station.id = stations.size() + 1; 
                getline(file, station.name);
                file >> station.workshopCount;
                station.workshopStatus.resize(station.workshopCount);
                for (int i = 0; i < station.workshopCount; i++) {
                    int status;
                    file >> status;
                    station.workshopStatus[i] = (status != 0);
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


void deletePipe(vector<Pipe>& pipes, int pipeId) {
    bool found = false;
    for (auto it = pipes.begin(); it != pipes.end(); ++it) {
        if (it->id == pipeId) {
            pipes.erase(it); 
            found = true;
            cout << "Pipe with ID " << pipeId << " has been deleted." << endl;
            break;
        }
    }
    if (!found) {
        cout << "Pipe with ID " << pipeId << " not found." << endl;
    }
    else {
        Pipe::recalculateIds(pipes); 
    }
}

void deleteCompressorStation(vector<CompressorStation>& stations, int stationId) {
    bool found = false;
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        if (it->id == stationId) {
            stations.erase(it); 
            found = true;
            cout << "Compressor Station with ID " << stationId << " has been deleted." << endl;
            break;
        }
    }
    if (!found) {
        cout << "Compressor Station with ID " << stationId << " not found." << endl;
    }
    else {
        CompressorStation::recalculateIds(stations); 
    }
}


void deleteObject(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "What do you want to delete?" << endl;
    cout << "1. Pipe" << endl;
    cout << "2. Compressor Station" << endl;
    int deleteChoice;
    if (!(cin >> deleteChoice)) {
        cout << "Invalid choice. Please try again." << endl;
        clearInput();
        return;
    }

    if (deleteChoice == 1) {
        cout << "Enter the ID of the pipe to delete: ";
        int pipeId;
        if (!(cin >> pipeId)) {
            cout << "Invalid ID. Please try again." << endl;
            clearInput();
            return;
        }
        deletePipe(pipes, pipeId);
    }
    else if (deleteChoice == 2) {
        cout << "Enter the ID of the compressor station to delete: ";
        int stationId;
        if (!(cin >> stationId)) {
            cout << "Invalid ID. Please try again." << endl;
            clearInput();
            return;
        }
        deleteCompressorStation(stations, stationId);
    }
    else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

int main() {
    vector<Pipe> pipes;
    vector<CompressorStation> stations;

    loadData(pipes, stations, "data.txt");

    while (true) {
        cout << "" << endl;
        cout << "Menu:" << endl;
        cout << "1. Add a pipe" << endl;
        cout << "2. Add a compressor station" << endl;
        cout << "3. View all objects" << endl;
        cout << "4. Editing the operation status of pipes" << endl;
        cout << "5. Starting and stopping workshops" << endl;
        cout << "6. Save" << endl;
        cout << "7. Delete Object" << endl;
        cout << "0. Exit" << endl;
        cout << "" << endl;

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please try again." << endl;
            clearInput();
            continue;
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
            cout << "" << endl;
            for (const Pipe& pipe : pipes) {
                pipe.displayData();
                cout << endl;
            }
            cout << "Compressor Stations:" << endl;
            cout << "" << endl;
            for (const CompressorStation& station : stations) {
                station.displayData();
                cout << endl;
            }
            break;
        }
        case 4: {
            editPipeStatus(pipes);
            break;
        }
        case 5: {
            editWorkshopStatus(stations);
            break;
        }
        case 6: {
            saveData(pipes, stations, "data.txt");
            break;
        }
        case 7: {
            deleteObject(pipes, stations);
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
