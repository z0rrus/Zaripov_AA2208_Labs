#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>


using namespace std;


void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void logInput(const string& input) {
    static bool firstTime = true;
    static ofstream logfile("log.txt", ios::app);
    if (logfile.is_open()) {
        if (firstTime) {
            time_t now = time(0);
            tm ltm;
            localtime_s(&ltm, &now);
            char buffer[32];
            logfile << endl;
            strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", &ltm);
            logfile << buffer << " - Program started" << endl;
            firstTime = false;
        }
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);
        char buffer[32];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", &ltm);
        logfile << buffer << " - " << input << endl;
        logfile.flush(); // Принудительная запись буфера в файл
    }
    else {
        cerr << "Unable to open log file." << endl;
    }
}

class Pipe {
private:
    double length;
    double diameter;
    bool inRepair;
    int id;

public:
    string name;

    Pipe() : name(""), length(0.0), diameter(0.0), inRepair(false) {
        id = getNextId();
    }

    double getLength() const {
        return length;
    }

    void setLength(double newLength) {
        length = newLength;
    }

    void setId(int pipeId) {
        id = pipeId;
    }

    double getDiameter() const {
        return diameter;
    }

    void setDiameter(double newDiameter) {
        diameter = newDiameter;
    }

    void setRepairStatus(bool status) {
        inRepair = status;
    }

    bool getInRepair() const {
        return inRepair;
    }

    void toggleRepairStatus() {
        inRepair = !inRepair;
    }

    int getId() const {
        return id;
    }

    static int maxId;

    void readData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter pipe name: ";
        getline(cin, name);
        logInput("User input: " + name);

        while (true) {
            cout << "Enter pipe length (km): ";
            if (cin >> length && length >= 0) {
                logInput("User input: " + to_string(length));
                break;
            }
            else {
                logInput("User input: " + to_string(length));
                cout << "Invalid input. Please enter a non-negative number for length." << endl;
                clearInput();
            }
        }

        while (true) {
            cout << "Enter pipe diameter (cm): ";
            if (cin >> diameter && diameter >= 0) {
                logInput("User input: " + to_string(diameter));
                break;
            }
            else {
                logInput("User input: " + to_string(diameter));
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
    

    static int getNextId() {
        maxId = maxId + 1;
        return maxId;
    }
};

class CompressorStation {
private:
    double efficiency;
    double nonOperationalPercentage;
    int id;

public:
    string name;
    int workshopCount;
    vector<bool> workshopStatus;

    CompressorStation() : name(""), workshopCount(0), efficiency(0.0), nonOperationalPercentage(0.0) {
        id = getNextId();
    }

    double getEfficiency() const {
        return efficiency;
    }

    void setEfficiency(double newEfficiency) {
        efficiency = newEfficiency;
    }

    void setId(int stationId) {
        id = stationId;
    }

    void setWorkshopCount(int workshopCount) {
        this->workshopCount = workshopCount;
    }

    void setWorkshopStatus(int i, bool status) {
        if (i >= 0 && i < workshopCount) {
            workshopStatus[i] = status;
        }
        else {
            throw std::out_of_range("Недопустимый индекс цеха");
        }
    }

    double getNonOperationalPercentage() const {
        return nonOperationalPercentage;
    }

    void setNonOperationalPercentage(double newPercentage) {
        nonOperationalPercentage = newPercentage;
    }

    int getId() const {
        return id;
    }

    static int maxId;

    void readData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter station name: ";
        getline(cin, name);
        logInput("User input: " + name);

        while (true) {
            cout << "Enter workshop count: ";
            if (cin >> workshopCount && workshopCount > 0) {
                logInput("User input: " + to_string(workshopCount));
                break;
            }
            else {
                logInput("User input: " + to_string(workshopCount));
                cout << "Invalid input. Please enter a non-negative integer for workshop count." << endl;
                clearInput();
            }
        }

        while (true) {
            cout << "Enter the number of operational workshops: ";
            int operationalWorkshops;
            if (cin >> operationalWorkshops && operationalWorkshops >= 0 && operationalWorkshops <= workshopCount) {
                logInput("User input: " + to_string(operationalWorkshops));
                workshopStatus.resize(workshopCount, false); 
                for (int i = 0; i < operationalWorkshops; i++) {
                    workshopStatus[i] = true; 
                }
                break;
            }
            else {
                logInput("User input: " + to_string(operationalWorkshops));
                cout << "Invalid input. Please enter a non-negative integer no greater than workshop count." << endl;
                clearInput();
            }
        }

        while (true) {
            cout << "Enter efficiency rating: ";
            if (cin >> efficiency && efficiency >= 0) {
                logInput("User input: " + to_string(efficiency));
                break;
            }
            else {
                logInput("User input: " + to_string(efficiency));
                cout << "Invalid input. Please enter a non-negative number for efficiency rating." << endl;
                clearInput();
            }
        }
        updateNonOperationalPercentage();
    }


    
    void displayData() const {
        cout << "ID: " << id << endl;
        cout << "Station name: " << name << endl;
        cout << "Workshop count: " << workshopCount << endl;
        cout << "Workshop status:" << endl;
        for (int i = 0; i < workshopCount; i++) {
            cout << "Workshop " << i + 1 << ": " << (workshopStatus[i] ? "Operational" : "Not operational") << endl;
        }
        cout << "Efficiency rating: " << efficiency << endl;
        cout << "Non-operational workshops: " << nonOperationalPercentage << "%" << endl;
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

void addPipeFilter(vector<Pipe>& pipes) {
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
    logInput("User input: " + to_string(filterChoice));

    switch (filterChoice) {
    case 1: {
        string filterName;
        cout << "" << endl;
        cout << "Enter the name for filtering: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        getline(cin, filterName);
        logInput("User input: " + filterName);

        vector<Pipe> filteredPipes;
        for (const Pipe& pipe : pipes) {
            if (pipe.name.find(filterName) != string::npos) {
                filteredPipes.push_back(pipe);
            }
        }
        pipes = filteredPipes;
        cout << "" << endl;
        break;
    }
    case 2: {
        bool in_repair;
        cout << "" << endl;
        cout << "Choose operational status for filtering: 1. Under repair  2. Operational" << endl;
        int statusChoice;
        if (!(cin >> statusChoice) || (statusChoice != 1 && statusChoice != 2)) {
            cout << "" << endl;
            cout << "Invalid choice. Please try again." << endl;
            clearInput();
            logInput("User input: " + to_string(statusChoice));
            return;
        }
        logInput("User input: " + to_string(statusChoice));

        bool filterStatus = (statusChoice == 1);

        vector<Pipe> filteredPipes;
        for (const Pipe& pipe : pipes) {
            in_repair = pipe.getInRepair();
            if (in_repair == filterStatus) {
                filteredPipes.push_back(pipe);
            }
        }
        pipes = filteredPipes;
        cout << "" << endl;
        break;
    }
    case 0: {
        return;
    }
    default: {
        cout << "" << endl;
        cout << "Invalid choice. Please try again." << endl;
        addPipeFilter(pipes);
        break;
    }
    }
}

void addStationFilter(vector<CompressorStation>& stations) {
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
    logInput("User input: " + to_string(filterChoice));

    switch (filterChoice) {
    case 1: {
        string filterName;
        cout << "" << endl;
        cout << "Enter the name for filtering: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, filterName);
        logInput("User input: " + filterName);

        static vector<CompressorStation> filteredStations;
        for (const CompressorStation& station : stations) {
            if (station.name.find(filterName) != string::npos) {
                filteredStations.push_back(station);
            }
        }
        stations = filteredStations;
        cout << "" << endl;
        break;
    }
    case 2: {
        string input;
        cout << "" << endl;
        cout << "Enter comparison operator and the percentage value for filtering (e.g., '>56' or '<=40'): ";
        cin >> input;

        string comparisonOperator;
        double nonOperationalPercentage;
        logInput("User input: " + input);


        if (input.find_first_not_of("0123456789.") == string::npos) {
            nonOperationalPercentage = stod(input);
            comparisonOperator = "=";
        }
        else {
            comparisonOperator = input.substr(0, 2);
            if (comparisonOperator != "<=" && comparisonOperator != ">=" && comparisonOperator != "<" && comparisonOperator != ">" && comparisonOperator != "==") {
                comparisonOperator = input.substr(0, 1);
            }
            string percentageString = input.substr(comparisonOperator.length());

            try {
                nonOperationalPercentage = stod(percentageString);
            }
            catch (...) {
                cout << "" << endl;
                cout << "Invalid input format. Please try again." << endl;
                clearInput();
                return;
            }
        }

        if ((comparisonOperator != "<" && comparisonOperator != ">" && comparisonOperator != "<=" && comparisonOperator != ">=" && comparisonOperator != "==")) {
            cout << "" << endl;
            cout << "Invalid comparison operator. Please try again." << endl;
            clearInput();
            return;
        }

        if (nonOperationalPercentage < 0 || nonOperationalPercentage > 100) {
            cout << "" << endl;
            cout << "Invalid percentage. Please try again." << endl;
            clearInput();
            return;
        }

        static vector<CompressorStation> filteredStations;
        filteredStations.clear();
        double st_percentage;
        for (const CompressorStation& station : stations) {
            st_percentage = station.getNonOperationalPercentage();
            if ((comparisonOperator == "<" && st_percentage < nonOperationalPercentage) ||
                (comparisonOperator == ">" && st_percentage > nonOperationalPercentage) ||
                (comparisonOperator == "<=" && st_percentage <= nonOperationalPercentage) ||
                (comparisonOperator == ">=" && st_percentage >= nonOperationalPercentage) ||
                (comparisonOperator == "==" && abs(st_percentage - nonOperationalPercentage) < 0.01) ||
                (comparisonOperator == "=" && abs(st_percentage - nonOperationalPercentage) < 0.01)) {
                filteredStations.push_back(station);
            }
        }
        stations = filteredStations;
        cout << "" << endl;
        break;
    }
    case 0: {
        return;
    }
    default: {
        cout << "" << endl;
        cout << "Invalid choice. Please try again." << endl;
        addStationFilter(stations);
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
        showPipes(filteredPipes);
        showStations(filteredStations);
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
            logInput("User input: " + to_string(choice));
            continue;
        }
        logInput("User input: " + to_string(choice));
        switch (choice) {
        case 1: {
            addPipeFilter(filteredPipes);
            break;
        }
        case 2: {
            addStationFilter(filteredStations);
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


void editPipeStatus(vector<Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "There are no pipes." << endl;
        return;
    }

    static vector<Pipe> filteredPipes;
    filteredPipes = pipes;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "" << endl;
        showPipes(filteredPipes);
        cout << "" << endl;
        cout << "Choose an option: " << endl;
        cout << "1. Enter pipes ID for editing" << endl;
        cout << "2. Edit all pipes in this list" << endl;
        cout << "3. Add filter" << endl;
        cout << "0. Back to main menu (all filters will be reset)" << endl;
        int editChoice;
        if (!(cin >> editChoice)) {
            cout << "" << endl;
            cout << "Invalid choice. Please try again." << endl;
            logInput("User input: " + to_string(editChoice));
            continue;
        }
        logInput("User input: " + to_string(editChoice));
        switch (editChoice) {
        case 1: {
            cout << "" << endl;
            cout << "Enter the IDs of the pipes to edit (separated by space): ";
            cout << "" << endl;
            vector<int> pipeIds;
            int pipeId;
            bool validIdFound = false;
            while (cin >> pipeId) {
                logInput("User input: " + to_string(pipeId));
                if (pipeId < 1 || pipeId > Pipe::maxId) {
                    cout << "Invalid ID " << pipeId << ". Skipping..." << endl;
                }
                else {
                    validIdFound = true;
                    pipeIds.push_back(pipeId);
                }
                if (cin.peek() == '\n') {
                    break;
                }
            }

            if (!validIdFound) {
                editPipeStatus(filteredPipes);
                break;
            }

            cout << "" << endl;
            cout << "Choose action: 1. Under repair 2. Operational" << endl;
            int repairChoice;
            if (!(cin >> repairChoice) || (repairChoice != 1 && repairChoice != 2)) {
                cout << "" << endl;
                cout << "INVALID ACTION CHOICE. PLEASE TRY AGAIN." << endl;
                logInput("User input: " + to_string(repairChoice));
                break;
            }
            logInput("User input: " + to_string(repairChoice));
            bool newStatus = (repairChoice == 1);

            vector<int> modifiedPipeIds;
            int pipe_id;
            for (auto& pipe : pipes) {
                pipe_id = pipe.getId();
                for (int id : pipeIds) {
                    if (pipe_id == id) {
                        pipe.setRepairStatus(newStatus);
                        modifiedPipeIds.push_back(id);
                    }
                }
            }
            filteredPipes = pipes;

            if (!modifiedPipeIds.empty()) {
                cout << "" << endl;
                cout << "Status of pipes with IDs ";
                for (size_t i = 0; i < modifiedPipeIds.size(); ++i) {
                    if (i != 0) {
                        cout << ", ";
                    }
                    cout << modifiedPipeIds[i];
                }
                cout << " changed to '" << (newStatus ? "Under repair" : "Operational") << "'" << endl;
            }
            return;
        }
        case 2: {
            cout << "" << endl;
            cout << "Choose action: 1. Under repair 2. Operational" << endl;
            int repairChoice;
            if (!(cin >> repairChoice) || (repairChoice != 1 && repairChoice != 2)) {
                cout << "" << endl;
                cout << "INVALID ACTION CHOICE. PLEASE TRY AGAIN." << endl;
                break;
            }
            logInput("User input: " + to_string(repairChoice));

            bool newStatus = (repairChoice == 1);
            bool pipe_id;
            bool fil_pipe_id;

            vector<int> modifiedPipeIds;
            for (auto& pipe : pipes) {
                pipe_id = pipe.getId();
                for (auto& filteredPipe : filteredPipes) {
                    fil_pipe_id = filteredPipe.getId();
                    if (pipe_id == fil_pipe_id) {
                        modifiedPipeIds.push_back(pipe_id);
                        pipe.setRepairStatus(newStatus);
                    }
                }
            }
            filteredPipes = pipes;
            cout << "" << endl;
            cout << "Status of pipes with IDs ";
            for (size_t i = 0; i < modifiedPipeIds.size(); ++i) {
                if (i != 0) {
                    cout << ", ";
                }
                cout << modifiedPipeIds[i];
            }
            cout << " changed to '" << (newStatus ? "Under repair" : "Operational") << "'" << endl;
            return;
        }
        case 3: {
            addPipeFilter(filteredPipes);
            break;
        }
        case 0: {
            return;
        }
        default: {
            cout << "" << endl;
            cout << "INVALID ACTION CHOICE. PLEASE TRY AGAIN." << endl;
            break;
        }
    }
    }
}

void editWorkshop(CompressorStation& station) {
    cout << "Choose workshop to edit (1-" << station.workshopCount << "): ";
    int workshopChoice;
    if (!(cin >> workshopChoice) || workshopChoice < 1 || workshopChoice > station.workshopCount) {
        cout << "Invalid workshop choice. Please try again." << endl;
        clearInput();
        return;
    }
    logInput("User input: " + to_string(workshopChoice));

    station.workshopStatus[workshopChoice - 1] = !station.workshopStatus[workshopChoice - 1];
    station.updateNonOperationalPercentage();
    cout << "Workshop " << workshopChoice << " status changed to '" << (station.workshopStatus[workshopChoice - 1] ? "Operational" : "Not Operational") << "'" << endl;
    
    double st_percent;
    st_percent = station.getNonOperationalPercentage();
    cout << "Updated non-operational workshop percentage: " << st_percent << "%" << endl;
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
    if (!(cin >> stationId)) {
        cout << "Invalid ID. Please try again." << endl;
        clearInput();
        return;
    }
    logInput("User input: " + to_string(stationId));

    auto it = find_if(stations.begin(), stations.end(), [stationId](const CompressorStation& s) { return s.getId() == stationId; });
    if (it == stations.end()) {
        cout << "Compressor Station with ID " << stationId << " not found." << endl;
        return;
    }

    CompressorStation& station = *it;

    editWorkshop(station);
}




void savePipe(const Pipe& pipe, ofstream& file) {
    file << "Pipe\n";
    file << pipe.getId() << "\n";
    file << pipe.name << "\n";
    file << pipe.getLength() << "\n";
    file << pipe.getDiameter() << "\n";
    file << pipe.getInRepair() << "\n";
}

void saveStation(const CompressorStation& station, ofstream& file) {
    file << "Station\n";
    file << station.getId() << "\n";
    file << station.name << "\n";
    file << station.workshopCount << "\n";
    for (bool status : station.workshopStatus) {
        file << status << "\n";
    }
    file << station.getEfficiency() << "\n";
    file << station.getNonOperationalPercentage() << "\n";
}

void saveData(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "Enter the filename for saving: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    getline(cin, filename);
    logInput("User input: " + filename);
    filename = filename + ".txt";

    ifstream fileExists(filename);
    if (fileExists) {
        cout << "A file with the name '" << filename << "' already exists. Its data will be overwritten. Are you sure? (Y/N) ";
        char choice;
        cin >> choice;
        logInput("User input: " + to_string(choice));
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
    int pipe_id;
    for (const auto& pipe : pipes) {
        pipe_id = pipe.getId();
        if (pipe_id > maxId) {
            maxId = pipe_id;
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
    pipe.setId(id);
    file.ignore();
    getline(file, temp);
    getline(file, pipe.name);
    double length, diameter;
    file >> length;
    file >> diameter;
    pipe.setLength(length);
    pipe.setDiameter(diameter);
    int repairStatus;
    file >> repairStatus;
    pipe.setRepairStatus(repairStatus != 0);
    pipes.push_back(pipe);

    calculateMaxId(pipes);
}

void calculateMaxStationsId(const vector<CompressorStation>& stations) {
    int maxId = 0;
    int st_id;
    for (const auto& station : stations) {
        st_id = station.getId();
        if (st_id > maxId) {
            maxId = st_id;
        }
    }
    CompressorStation::maxId = maxId;
}

void loadStation(ifstream& file, vector<CompressorStation>& stations) {
    CompressorStation station;
    string temp;
    int id, workshopCount;
    file >> id;
    station.setId(id);
    getline(file, temp);
    getline(file, station.name);
    file >> workshopCount;
    station.setWorkshopCount(workshopCount);
    station.workshopStatus.resize(workshopCount);
    for (int i = 0; i < workshopCount; i++) {
        int status;
        file >> status;
        station.setWorkshopStatus(i, static_cast<bool>(status));
    }
    double efficiency, nonOperationalPercentage;
    file >> efficiency;
    file >> nonOperationalPercentage;
    station.setEfficiency(efficiency);
    station.setNonOperationalPercentage(nonOperationalPercentage);
    stations.push_back(station);

    calculateMaxStationsId(stations);
}

void updateMaxPipeId(const vector<Pipe>& pipes) {
    int maxId = 0;
    int pipe_id;
    for (const auto& pipe : pipes) {
        pipe_id = pipe.getId();
        if (pipe_id > maxId) {
            maxId = pipe_id;
        }
    }
    Pipe::maxId = maxId;
}


void updateMaxStationId(const vector<CompressorStation>& stations) {
    int maxId = 0;
    int st_id;
    for (const auto& station : stations) {
        st_id = station.getId();
        if (st_id > maxId) {
            maxId = st_id;
        }
    }
    CompressorStation::maxId = maxId;
}

void loadData(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    cout << "Enter the filename to load: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    getline(cin, filename);
    logInput("User input: " + filename);
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

        updateMaxPipeId(pipes);
        updateMaxStationId(stations);

        cout << "Data successfully loaded from the file " << filename << endl;
    }
    else {
        cout << "File '" << filename << "' not found in the directory." << endl;
    }
}



void deletePipe(vector<Pipe>& pipes, int pipeId) {
    bool found = false;
    for (auto it = pipes.begin(); it != pipes.end(); ++it) {
        if (it->getId() == pipeId) { 
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
        if (it->getId() == stationId) {
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
        logInput("User input: " + to_string(deleteChoice));
        return;
    }
    logInput("User input: " + to_string(deleteChoice));

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
        logInput("User input: " + to_string(choice));
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
            string action = "Invalid choice entered. Please try again.";
            cout << action << endl;
            break;
        }
        }
    }

    return 0;
}
