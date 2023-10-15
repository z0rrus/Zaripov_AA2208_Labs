#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;


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
    static int maxId;

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
    

    static int getNextId() {
        maxId = maxId + 1;
        return maxId;
    }
};

class CompressorStation {
public:
    string name;
    int workshopCount;
    vector<bool> workshopStatus;
    double efficiency;
    double nonOperationalPercentage;
    int id; 
    static int maxId;

    CompressorStation() : name(""), workshopCount(0), efficiency(0.0), nonOperationalPercentage(0.0) {
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
        cout << "Non-operational Workshop Percentage: " << nonOperationalPercentage << "%" << endl;
    }

    void updateNonOperationalPercentage() {
        int nonOperationalCount = 0;
        for (bool status : workshopStatus) {
            if (!status) {
                nonOperationalCount++;
            }
        }
        nonOperationalPercentage = round((nonOperationalCount * 100.0) / workshopCount);
    }


    static int getNextId() {
        maxId = maxId + 1;
        return maxId;
    }
};

void showPipes(const vector<Pipe>& pipes) {
    cout << "PIPES:" << endl;
    cout << "" << endl;
    if (pipes.empty()) {
        cout << "There are no pipes." << endl;
        cout << "" << endl;
    }
    else {
        for (const Pipe& pipe : pipes) {
            pipe.displayData();
            cout << endl;
        }
    }
}

void showStations(const vector<CompressorStation>& stations) {
    cout << "COMPRESSOR STATIONS:" << endl;
    cout << "" << endl;
    if (stations.empty()) {
        cout << "There are no compressor stations." << endl;
        cout << "" << endl;
    }
    else {
        for (const CompressorStation& station : stations) {
            station.displayData();
            cout << endl;
        }
    }
}

void addPipeFilter(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "" << endl;
    cout << "Choose filter option:" << endl;
    cout << "1. Add filter by name" << endl;
    cout << "2. Add filter by operational status" << endl;
    cout << "0. Back" << endl;

    int filterChoice;
    if (!(cin >> filterChoice)) {
        cout << "" << endl;
        cout << "Invalid choice. Please try again." << endl;
        clearInput();
        return;
    }

    switch (filterChoice) {
    case 1: {
        string filterName;
        cout << "" << endl;
        cout << "Enter the name for filtering: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, filterName);


        vector<Pipe> filteredPipes;
        for (const Pipe& pipe : pipes) {
            if (pipe.name == filterName) {
                filteredPipes.push_back(pipe);
            }
        }
        pipes = filteredPipes;
        cout << "" << endl;
        showPipes(pipes);
        showStations(stations);
        break;
    }
    case 2: {
        cout << "" << endl;
        cout << "Choose operational status for filtering: 1. Under repair  2. Operational" << endl;
        int statusChoice;
        if (!(cin >> statusChoice) || (statusChoice != 1 && statusChoice != 2)) {
            cout << "" << endl;
            cout << "Invalid choice. Please try again." << endl;
            clearInput();
            return;
        }

        bool filterStatus = (statusChoice == 1);

        vector<Pipe> filteredPipes;
        for (const Pipe& pipe : pipes) {
            if (pipe.inRepair == filterStatus) {
                filteredPipes.push_back(pipe);
            }
        }
        pipes = filteredPipes;
        cout << "" << endl;
        showPipes(pipes);
        showStations(stations);
        break;
    }
    case 0: {
        cout << "" << endl;
        showPipes(pipes);
        showStations(stations);
        return;
    }
    default: {
        cout << "" << endl;
        cout << "Invalid choice. Please try again." << endl;
        addPipeFilter(pipes, stations);
        break;
    }
    }
}

void addStationFilter(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "" << endl;
    cout << "Choose filter option:" << endl;
    cout << "1. Add filter by station name" << endl;
    cout << "2. Add filter by non-operational workshop %" << endl;
    cout << "0. Back" << endl;

    int filterChoice;
    if (!(cin >> filterChoice)) {
        cout << "" << endl;
        cout << "Invalid choice. Please try again." << endl;
        clearInput();
        return;
    }

    switch (filterChoice) {
    case 1: {
        string filterName;
        cout << "" << endl;
        cout << "Enter the name for filtering: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, filterName);

        static vector<CompressorStation> filteredStations;
        for (const CompressorStation& station : stations) {
            if (station.name == filterName) {
                filteredStations.push_back(station);
            }
        }
        stations = filteredStations;
        cout << "" << endl;
        showPipes(pipes);
        showStations(stations);
        break;
    }
    case 2: {
        double nonOperationalPercentage;
        cout << "" << endl;
        cout << "Enter % of non-operational workshops for filtering: ";
        if (!(cin >> nonOperationalPercentage) || nonOperationalPercentage < 0 || nonOperationalPercentage > 100) {
            cout << "" << endl;
            cout << "Invalid %. Please try again." << endl;
            clearInput();
            return;
        }

        static vector<CompressorStation> filteredStations;
        for (const CompressorStation& station : stations) {
            if (abs(station.nonOperationalPercentage - nonOperationalPercentage) < 0.01) {
                filteredStations.push_back(station);
            }
        }
        stations = filteredStations;
        cout << "" << endl;
        showPipes(pipes);
        showStations(stations);
        break;
    }
    case 0: {
        cout << "" << endl;
        showPipes(pipes);
        showStations(stations);
        return;
    }
    default: {
        cout << "" << endl;
        cout << "Invalid choice. Please try again." << endl;
        addStationFilter(pipes, stations);
        break;
    }
    }
}


void showObjectsWithFilters(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    static vector<CompressorStation> filteredStations;
    filteredStations = stations;
    static vector<Pipe> filteredPipes;
    filteredPipes = pipes;
    while (true) {
        cout << "" << endl;
        cout << "Options:" << endl;
        cout << "1. Add filter for pipes" << endl;
        cout << "2. Add filter for stations" << endl;
        cout << "0. Back to main menu (all filters will be reset)" << endl;
        int choice;
        if (!(cin >> choice)) {
            cout << "" << endl;
            cout << "Invalid choice. Please try again." << endl;
            clearInput();
            continue;
        }

        switch (choice) {
        case 1: {
            addPipeFilter(filteredPipes, filteredStations);
            break;
        }
        case 2: {
            addStationFilter(filteredPipes, filteredStations);
            break;
        }
        case 0: {
            return;
        }
        default: {
            cout << "" << endl;
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
}


void editPipe(vector<Pipe>& pipes, int pipeId) {
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

void editPipeStatus(vector<Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "No pipes added to the database." << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    showPipes(pipes);
    cout << "Enter the ID of the pipe to edit: ";
    int pipeId;
    if (!(cin >> pipeId) || pipeId < 1 || pipeId > pipes.size()) {
        cout << "Invalid ID. Please try again." << endl;
        clearInput();
        return;
    }

    editPipe(pipes, pipeId);
}

void editWorkshop(CompressorStation& station) {
    cout << "Choose workshop to edit (1-" << station.workshopCount << "): ";
    int workshopChoice;
    if (!(cin >> workshopChoice) || workshopChoice < 1 || workshopChoice > station.workshopCount) {
        cout << "Invalid workshop choice. Please try again." << endl;
        clearInput();
        return;
    }

    station.workshopStatus[workshopChoice - 1] = !station.workshopStatus[workshopChoice - 1];
    station.updateNonOperationalPercentage();
    cout << "Workshop " << workshopChoice << " status changed to '" << (station.workshopStatus[workshopChoice - 1] ? "Operational" : "Not Operational") << "'" << endl;
    cout << "Updated non-operational workshop percentage: " << station.nonOperationalPercentage << "%" << endl;
}

void editWorkshopStatus(vector<CompressorStation>& stations) {
    if (stations.empty()) {
        cout << "No compressor stations added to the database." << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    showStations(stations);
    cout << "Enter the ID of the compressor station to edit: ";
    int stationId;
    if (!(cin >> stationId) || stationId < 1 || stationId > stations.size()) {
        cout << "Invalid ID. Please try again." << endl;
        clearInput();
        return;
    }

    CompressorStation& station = stations[stationId - 1];

    editWorkshop(station);
}


void savePipe(const Pipe& pipe, ofstream& file) {
    file << "Pipe\n";
    file << pipe.id << "\n";
    file << pipe.name << "\n";
    file << pipe.length << "\n";
    file << pipe.diameter << "\n";
    file << pipe.inRepair << "\n";
}

void saveStation(const CompressorStation& station, ofstream& file) {
    file << "Station\n";
    file << station.id << "\n";
    file << station.name << "\n";
    file << station.workshopCount << "\n";
    for (bool status : station.workshopStatus) {
        file << status << "\n";
    }
    file << station.efficiency << "\n";
    file << station.nonOperationalPercentage << "\n";
}

void saveData(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "Enter the filename for saving: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    getline(cin, filename);
    filename = filename + ".txt";

    ifstream fileExists(filename);
    if (fileExists) {
        cout << "A file with the name '" << filename << "' already exists. Its data will be overwritten. Are you sure? (Y/N) ";
        char choice;
        cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            cout << "Cancelled. Data not saved." << endl;
            return;
        }
    }

    ofstream file(filename);

    if (file.is_open()) {
        for (const Pipe& pipe : pipes) {
            savePipe(pipe, file);
        }
        for (const CompressorStation& station : stations) {
            saveStation(station, file);
        }
        file.close();
        cout << "Data successfully saved to the file " << filename << endl;
    }
    else {
        cout << "Error opening the file for saving." << endl;
    }
}

void calculateMaxId(const vector<Pipe>& pipes) {
    int maxId = 0;
    for (const auto& pipe : pipes) {
        if (pipe.id > maxId) {
            maxId = pipe.id;
        }
    }
    Pipe::maxId = maxId;
}

void loadPipe(ifstream& file, vector<Pipe>& pipes) {
    string line;
    Pipe pipe;
    string temp;
    int id;
    file >> id;
    pipe.id = id;
    file.ignore(); // ignore the newline character
    getline(file, pipe.name); 
    file >> pipe.length;
    file >> pipe.diameter;
    int repairStatus;
    file >> repairStatus;
    pipe.inRepair = (repairStatus != 0);
    pipes.push_back(pipe);

    calculateMaxId(pipes);
}

void calculateMaxStationsId(const vector<CompressorStation>& stations) {
    int maxId = 0;
    for (const auto& station : stations) {
        if (station.id > maxId) {
            maxId = station.id;
        }
    }
    CompressorStation::maxId = maxId;
}

void loadStation(ifstream& file, vector<CompressorStation>& stations) {
    CompressorStation station;
    string temp; 
    file >> station.id;
    getline(file, temp); 
    getline(file, station.name);
    file >> station.workshopCount;
    station.workshopStatus.resize(station.workshopCount);
    for (int i = 0; i < station.workshopCount; i++) {
        int status;
        file >> status;
        station.workshopStatus[i] = static_cast<bool>(status);
    }
    file >> station.efficiency;
    file >> station.nonOperationalPercentage;
    stations.push_back(station);

    calculateMaxStationsId(stations);
}

void loadData(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "Enter the filename to load: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    getline(cin, filename);
    filename = filename + ".txt";

    ifstream file(filename);

    if (file.is_open()) {
        pipes.clear();
        stations.clear();
        string line;
        while (getline(file, line)) {
            if (line == "Pipe") {
                loadPipe(file, pipes);
            }
            else if (line == "Station") {
                loadStation(file, stations);
            }
        }
        file.close();
        cout << "Data successfully loaded from the file " << filename << endl;
    }
    else {
        cout << "File '" << filename << "' not found in the directory." << endl;
    }
}



void deletePipe(vector<Pipe>& pipes, int pipeId) {
    bool found = false;
    for (auto it = pipes.begin(); it != pipes.end(); ++it) {
        if (it->id == pipeId) {
            pipes.erase(it); 
            found = true;
            cout << "Pipe with ID " << pipeId << " has been deleted." << endl;
            calculateMaxId(pipes);
            break;
        }
    }
    if (!found) {
        cout << "Pipe with ID " << pipeId << " not found." << endl;
    }
}

void deleteCompressorStation(vector<CompressorStation>& stations, int stationId) {
    bool found = false;
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        if (it->id == stationId) {
            stations.erase(it); 
            found = true;
            cout << "Compressor Station with ID " << stationId << " has been deleted." << endl;
            calculateMaxStationsId(stations);
            break;
        }
    }
    if (!found) {
        cout << "Compressor Station with ID " << stationId << " not found." << endl;
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
        showPipes(pipes);
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
        showStations(stations);
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


int Pipe::maxId = 0;
int CompressorStation::maxId = 0;

int main() {
    vector<Pipe> pipes;
    vector<CompressorStation> stations;


    while (true) {
        cout << "" << endl;
        cout << "Menu:" << endl;
        cout << "1. Add a pipe" << endl;
        cout << "2. Add a compressor station" << endl;
        cout << "3. View all objects" << endl;
        cout << "4. Editing the operation status of pipes" << endl;
        cout << "5. Starting and stopping workshops" << endl;
        cout << "6. Save" << endl;
        cout << "7. Load" << endl;
        cout << "8. Delete Object" << endl;
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
            showPipes(pipes);
            showStations(stations);
            showObjectsWithFilters(pipes, stations);
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
            saveData(pipes, stations);
            break;
        }
        case 7: {
            loadData(pipes, stations);
            break;
        }
        case 8: {
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
