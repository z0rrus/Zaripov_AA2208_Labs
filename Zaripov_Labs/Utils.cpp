#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_map>
#include <string>
#include <unordered_set>  
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
        logfile << input << endl;
        logfile.flush(); 
    }
    else {
        cerr << "Unable to open log file." << endl;
    }
}

void showPipes(const std::unordered_map<int, Pipe>& pipes) {
    std::cout << "PIPES:" << std::endl;
    std::cout << std::endl;

    if (pipes.empty()) {
        std::cout << "There are no pipes." << std::endl;
        std::cout << std::endl;
    }
    else {
        for (const auto& pipeEntry : pipes) {
            const Pipe& pipe = pipeEntry.second; 
            pipe.displayData();
            std::cout << std::endl;
        }
    }
}

void showStations(const std::unordered_map<int, CompressorStation>& stations) {
    std::cout << "COMPRESSOR STATIONS:" << std::endl;
    std::cout << std::endl;
    if (stations.empty()) {
        std::cout << "There are no compressor stations." << std::endl;
        std::cout << std::endl;
    }
    else {
        for (const auto& stationEntry : stations) {
            const CompressorStation& station = stationEntry.second;
            station.displayData();
            std::cout << std::endl;
        }
    }
}

void addPipeFilter(unordered_map<int, Pipe>& pipes) {
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
    logInput(to_string(filterChoice));

    switch (filterChoice) {
    case 1: {
        string filterName;
        cout << "" << endl;
        cout << "Enter the name for filtering: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, filterName);
        logInput(filterName);

        unordered_map<int, Pipe> filteredPipes;
        for (const auto& pipeEntry : pipes) {
            const Pipe& pipe = pipeEntry.second;
            if (pipe.name.find(filterName) != std::string::npos) {
                filteredPipes.emplace(pipeEntry.first, pipe);
            }
        }
        pipes = filteredPipes;
        cout << "" << endl;
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
            logInput(to_string(statusChoice));
            return;
        }
        logInput(to_string(statusChoice));

        bool filterStatus = (statusChoice == 1);

        unordered_map<int, Pipe> filteredPipes;
        for (const auto& pipeEntry : pipes) {
            const Pipe& pipe = pipeEntry.second;
            bool inRepair = pipe.getInRepair();
            if (inRepair == filterStatus) {
                filteredPipes.emplace(pipeEntry.first, pipe);
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

void addStationFilter(unordered_map<int, CompressorStation>& stations) {
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
    logInput(to_string(filterChoice));

    switch (filterChoice) {
    case 1: {
        string filterName;
        cout << "" << endl;
        cout << "Enter the name for filtering: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, filterName);
        logInput(filterName);

        static unordered_map<int, CompressorStation> filteredStations;
        for (const auto& stationEntry : stations) {
            const CompressorStation& station = stationEntry.second;
            if (station.name.find(filterName) != std::string::npos) {
                filteredStations.emplace(station.getId(), station);
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
        logInput(input);


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

        static unordered_map<int, CompressorStation> filteredStations;
        filteredStations.clear();
        for (const auto& stationEntry : stations) {
            const CompressorStation& station = stationEntry.second;
            double st_percentage = station.getNonOperationalPercentage();
            if ((comparisonOperator == "<" && st_percentage < nonOperationalPercentage) ||
                (comparisonOperator == ">" && st_percentage > nonOperationalPercentage) ||
                (comparisonOperator == "<=" && st_percentage <= nonOperationalPercentage) ||
                (comparisonOperator == ">=" && st_percentage >= nonOperationalPercentage) ||
                (comparisonOperator == "==" && std::abs(st_percentage - nonOperationalPercentage) < 0.01) ||
                (comparisonOperator == "=" && std::abs(st_percentage - nonOperationalPercentage) < 0.01)) {
                filteredStations.emplace(station.getId(), station);
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


void showObjectsWithFilters(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations) {
    static unordered_map<int, CompressorStation> filteredStations;
    filteredStations = stations;
    static unordered_map<int, Pipe> filteredPipes;
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
            logInput(to_string(choice));
            continue;
        }
        logInput(to_string(choice));
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


void editPipeStatus(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "There are no pipes." << endl;
        return;
    }

    static unordered_map<int, Pipe> filteredPipes;
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
            logInput(to_string(editChoice));
            continue;
        }
        logInput(to_string(editChoice));
        switch (editChoice) {
        case 1: {
            std::cout << "" << std::endl;
            std::cout << "Enter the IDs of the pipes to edit (separated by space): ";
            std::cout << "" << std::endl;

            std::string input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::getline(std::cin, input);
            logInput(input);
            
            std::istringstream iss(input);
            std::unordered_map<int, bool> pipeIds;
            std::string pipeId;

            bool validIdFound = false;

            while (iss >> pipeId) {
                try {
                    int id = std::stoi(pipeId);
                    if (id < 1 || id > Pipe::getMaxId()) {
                        std::cout << "Invalid ID " << id << ". Skipping..." << std::endl;
                    }
                    else {
                        validIdFound = true;
                        pipeIds.emplace(id, true);
                    }
                }
                catch (std::invalid_argument&) {
                    std::cout << "Invalid ID " << pipeId << ". Skipping..." << std::endl;
                }
                catch (std::out_of_range&) {
                    std::cout << "Invalid ID " << pipeId << ". Skipping..." << std::endl;
                }
            }

            if (!validIdFound) {
                std::cout << "No valid IDs entered. Exiting..." << std::endl;
                break; 
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
                logInput(to_string(repairChoice));
                break;
            }
            logInput(to_string(repairChoice));
            bool newStatus = (repairChoice == 1);

            unordered_map<int, bool> modifiedPipeIds;
            for (auto it = pipes.begin(); it != pipes.end(); ++it) {
                const Pipe& pipe = it->second;
                int pipe_id = pipe.getId();
                auto idIt = pipeIds.find(pipe_id);
                if (idIt != pipeIds.end()) {
                    pipes[pipe_id].setRepairStatus(newStatus);
                    modifiedPipeIds.emplace(pipe_id, newStatus);
                }
            }
            filteredPipes = pipes;

            if (!modifiedPipeIds.empty()) {
                std::cout << "\nStatus of pipes with IDs ";
                bool first = true;
                for (const auto& pipeId : modifiedPipeIds) {
                    if (!first) {
                        std::cout << ", ";
                    }
                    std::cout << pipeId.first;  
                    first = false;
                }

                std::cout << " changed to '" << (newStatus ? "Under repair" : "Operational") << "'\n";
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
                logInput(to_string(repairChoice));
                break;
            }
            logInput(to_string(repairChoice));

            bool newStatus = (repairChoice == 1);

            unordered_map<int, bool> modifiedPipeIds;
            for (auto& pipeEntry : pipes) {
                int pipe_id = pipeEntry.first;
                Pipe& pipe = pipeEntry.second;
                auto filteredPipeIt = filteredPipes.find(pipe_id);
                if (filteredPipeIt != filteredPipes.end()) {
                    modifiedPipeIds.emplace(pipe_id, newStatus);
                    pipe.setRepairStatus(newStatus);
                }
            }
            filteredPipes = pipes;
            cout << "" << endl;
            cout << "Status of pipes with IDs ";
            for (auto i = 0u; i < modifiedPipeIds.size(); ++i) {
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
    logInput(to_string(workshopChoice));

    station.workshopStatus[workshopChoice - 1] = !station.workshopStatus[workshopChoice - 1];
    station.updateNonOperationalPercentage();
    cout << "Workshop " << workshopChoice << " status changed to '" << (station.workshopStatus[workshopChoice - 1] ? "Operational" : "Not Operational") << "'" << endl;

    double st_percent;
    st_percent = station.getNonOperationalPercentage();
    cout << "Updated non-operational workshop percentage: " << st_percent << "%" << endl;
}

void editWorkshopStatus(std::unordered_map<int, CompressorStation>& stations) {
    if (stations.empty()) {
        std::cout << "No compressor stations added to the database." << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    showStations(stations);
    std::cout << "Enter the ID of the compressor station to edit: ";
    int stationId;
    if (!(std::cin >> stationId)) {
        std::cout << "Invalid ID. Please try again." << std::endl;
        clearInput();
        logInput(std::to_string(stationId));
        return;
    }
    logInput(std::to_string(stationId));

    auto it = std::find_if(
        stations.begin(),
        stations.end(),
        [stationId](const std::pair<int, CompressorStation>& pair) { return pair.second.getId() == stationId; }
    );

    if (it == stations.end()) {
        std::cout << "Compressor Station with ID " << stationId << " not found." << std::endl;
        return;
    }

    CompressorStation& station = it->second;

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
    for (const auto& statusEntry : station.workshopStatus) {
        file << statusEntry.second << "\n";
    }
    file << station.getEfficiency() << "\n";
    file << station.getNonOperationalPercentage() << "\n";
}

void saveData(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations) {
    cout << "Enter the filename for saving: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    getline(cin, filename);
    logInput(filename);
    filename = filename + ".txt";

    ifstream fileExists(filename);
    if (fileExists) {
        cout << "A file with the name '" << filename << "' already exists. Its data will be overwritten. Are you sure? (Y/N) ";
        char choice;
        cin >> choice;
        logInput(to_string(choice));
        if (choice != 'Y' && choice != 'y') {
            cout << "Cancelled. Data not saved." << endl;
            return;
        }
    }

    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& pipeEntry : pipes) {
            const Pipe& pipe = pipeEntry.second;
            savePipe(pipe, file);
        }
        for (const auto& stationEntry : stations) {
            const CompressorStation& station = stationEntry.second;
            saveStation(station, file);
        }
        file.close();
        std::cout << "Data successfully saved to the file " << filename << std::endl;
    }
    else {
        std::cout << "Error opening the file for saving." << std::endl;
    }
}

void calculateMaxId(const std::unordered_map<int, Pipe>& pipes) {
    int max_Id = 0;
    for (const auto& pipeEntry : pipes) {
        const Pipe& pipe = pipeEntry.second;
        int pipe_id = pipe.getId();
        if (pipe_id > max_Id) {
            max_Id = pipe_id;
        }
    }
    Pipe::setMaxId(max_Id);
}

void loadPipe(ifstream& file, unordered_map<int, Pipe>& pipes) {
    string line;
    Pipe pipe;
    string temp;
    int id;
    file >> id;
    pipe.setId(id);
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
    pipes.emplace(id, pipe);
    calculateMaxId(pipes);
}

void calculateMaxStationsId(const std::unordered_map<int, CompressorStation>& stations) {
    int maxId = 0;
    for (const auto& stationEntry : stations) {
        const CompressorStation& station = stationEntry.second;
        int st_id = station.getId();
        if (st_id > maxId) {
            maxId = st_id;
        }
    }
    CompressorStation::setMaxId(maxId);
}

void loadStation(ifstream& file, unordered_map<int, CompressorStation>& stations) {
    CompressorStation station;
    string temp;
    int id, workshopCount;
    file >> id;
    station.setId(id);
    getline(file, temp);
    getline(file, station.name);
    file >> workshopCount;
    station.setWorkshopCount(workshopCount);
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
    stations.emplace(id, station);
    calculateMaxStationsId(stations);
}

void updateMaxPipeId(const std::unordered_map<int, Pipe>& pipes) {
    int maxId = 0;
    for (const auto& pipeEntry : pipes) {
        const Pipe& pipe = pipeEntry.second;
        int pipe_id = pipe.getId();
        if (pipe_id > maxId) {
            maxId = pipe_id;
        }
    }
    Pipe::setMaxId(maxId);
}


void updateMaxStationId(const std::unordered_map<int, CompressorStation>& stations) {
    int maxId = 0;
    for (const auto& stationEntry : stations) {
        const CompressorStation& station = stationEntry.second;
        int st_id = station.getId();
        if (st_id > maxId) {
            maxId = st_id;
        }
    }
    CompressorStation::setMaxId(maxId);
}

void loadData(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations) {
    cout << "Enter the filename to load: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filename;
    getline(cin, filename);
    logInput(filename);
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



void deletePipe(std::unordered_map<int, Pipe>& pipes, int pipeId) {
    auto it = pipes.find(pipeId);

    if (it != pipes.end()) {
        pipes.erase(it);
        std::cout << "Pipe with ID " << pipeId << " has been deleted." << std::endl;
        calculateMaxId(pipes);
    }
    else {
        std::cout << "Pipe with ID " << pipeId << " not found." << std::endl;
    }
}


void deleteCompressorStation(std::unordered_map<int, CompressorStation>& stations, int stationId) {
    auto it = stations.find(stationId);

    if (it != stations.end()) {
        stations.erase(it);
        std::cout << "Compressor Station with ID " << stationId << " has been deleted." << std::endl;
        calculateMaxStationsId(stations);
    }
    else {
        std::cout << "Compressor Station with ID " << stationId << " not found." << std::endl;
    }
}


void deleteObject(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations) {
    cout << "What do you want to delete?" << endl;
    cout << "1. Pipe" << endl;
    cout << "2. Compressor Station" << endl;
    int deleteChoice;
    if (!(cin >> deleteChoice)) {
        cout << "Invalid choice. Please try again." << endl;
        clearInput();
        logInput(to_string(deleteChoice));
        return;
    }
    logInput(to_string(deleteChoice));

    if (deleteChoice == 1) {
        static unordered_map<int, Pipe> filteredPipes;
        filteredPipes = pipes;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            cout << "" << endl;
            showPipes(filteredPipes);
            if (filteredPipes.size() < 1) {
                break;
            }
            else {
                cout << "" << endl;
                cout << "Choose an option: " << endl;
                cout << "1. Enter pipes ID for deleting" << endl;
                cout << "2. Delete all pipes in this list" << endl;
                cout << "3. Add filter" << endl;
                cout << "0. Back to main menu (all filters will be reset)" << endl;
                int editChoice;
                if (!(cin >> editChoice)) {
                    cout << "" << endl;
                    cout << "Invalid choice. Please try again." << endl;
                    logInput(to_string(editChoice));
                    continue;
                }
                logInput(to_string(editChoice));
                switch (editChoice) {
                case 1: {
                    std::cout << "" << std::endl;
                    std::cout << "Enter the IDs of the pipes to delete (separated by space): ";
                    std::cout << "" << std::endl;

                    std::string input;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    std::getline(std::cin, input);
                    logInput(input);

                    std::istringstream iss(input);
                    std::unordered_map<int, bool> pipeIds;
                    std::string pipeId;

                    bool validIdFound = false;

                    while (iss >> pipeId) {
                        try {
                            int id = std::stoi(pipeId);
                            if (id < 1 || id > Pipe::getMaxId()) {
                                std::cout << "Invalid ID " << id << ". Skipping..." << std::endl;
                            }
                            else {
                                validIdFound = true;
                                pipeIds.emplace(id, true);
                            }
                        }
                        catch (std::invalid_argument&) {
                            std::cout << "Invalid ID " << pipeId << ". Skipping..." << std::endl;
                        }
                        catch (std::out_of_range&) {
                            std::cout << "Invalid ID " << pipeId << ". Skipping..." << std::endl;
                        }
                    }

                    if (!validIdFound) {
                        std::cout << "No valid IDs entered. Exiting..." << std::endl;
                        break;
                    }

                    cout << "" << endl;
                    unordered_map<int, bool> modifiedPipeIds;
                    for (auto it = pipes.begin(); it != pipes.end();) {
                        int pipe_id = it->second.getId();

                        if (pipeIds.find(pipe_id) != pipeIds.end()) {
                            it = pipes.erase(it);
                            modifiedPipeIds.emplace(pipe_id, true);
                        }
                        else {
                            ++it;
                        }
                    }
                    filteredPipes = pipes;

                    if (!modifiedPipeIds.empty()) {
                        std::cout << "\nPipes with IDs ";
                        bool first = true;
                        for (const auto& pipeId : modifiedPipeIds) {
                            if (!first) {
                                std::cout << ", ";
                            }
                            std::cout << pipeId.first; 
                            first = false;
                        }

                        std::cout << " have been deleted." << "\n";
                    }

                    return;
                }
                case 2: {
                    unordered_map<int, bool> modifiedPipeIds;
                    for (auto it = pipes.begin(); it != pipes.end();) {
                        int pipe_id = it->second.getId();

                        if (filteredPipes.find(pipe_id) != filteredPipes.end()) {
                            it = pipes.erase(it);
                            modifiedPipeIds.emplace(pipe_id, true);
                        }
                        else {
                            ++it;
                        }
                    }
                    filteredPipes = pipes;
                    cout << "" << endl;
                    cout << "Pipes with IDs ";
                    bool first = true;
                    for (const auto& pipeId : modifiedPipeIds) {
                        if (!first) {
                            std::cout << ", ";
                        }
                        std::cout << pipeId.first;
                        first = false;
                    }
                    cout << " have been deleted." << "\n";
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
    }
    else if (deleteChoice == 2) {
        static unordered_map<int, CompressorStation> filteredStations;
        filteredStations = stations;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            cout << "" << endl;
            showStations(filteredStations);
            if (filteredStations.size() < 1) {
                break;
            }
            else {
                cout << "" << endl;
                cout << "Choose an option: " << endl;
                cout << "1. Enter stationss ID for deleting" << endl;
                cout << "2. Delete all stations in this list" << endl;
                cout << "3. Add filter" << endl;
                cout << "0. Back to main menu (all filters will be reset)" << endl;
                int editChoice;
                if (!(cin >> editChoice)) {
                    cout << "" << endl;
                    cout << "Invalid choice. Please try again." << endl;
                    logInput(to_string(editChoice));
                    continue;
                }
                logInput(to_string(editChoice));
                switch (editChoice) {
                case 1: {
                    std::cout << "" << std::endl;
                    std::cout << "Enter the IDs of the stations to delete (separated by space): ";
                    std::cout << "" << std::endl;

                    std::string input;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    std::getline(std::cin, input);
                    logInput(input);

                    std::istringstream iss(input);
                    std::unordered_map<int, bool> stationIds;
                    std::string stationId;

                    bool validIdFound = false;

                    while (iss >> stationId) {
                        try {
                            int id = std::stoi(stationId);
                            if (id < 1 || id > CompressorStation::getMaxId()) {
                                std::cout << "Invalid ID " << id << ". Skipping..." << std::endl;
                            }
                            else {
                                validIdFound = true;
                                stationIds.emplace(id, true);
                            }
                        }
                        catch (std::invalid_argument&) {
                            std::cout << "Invalid ID " << stationId << ". Skipping..." << std::endl;
                        }
                        catch (std::out_of_range&) {
                            std::cout << "Invalid ID " << stationId << ". Skipping..." << std::endl;
                        }
                    }

                    if (!validIdFound) {
                        std::cout << "No valid IDs entered. Exiting..." << std::endl;
                        break;
                    }

                    cout << "" << endl;
                    unordered_map<int, bool> modifiedStationIds;
                    for (auto it = stations.begin(); it != stations.end();) {
                        int station_id = it->second.getId();
                        if (stationIds.find(station_id) != stationIds.end()) {
                            it = stations.erase(it);
                            modifiedStationIds.emplace(station_id, true);
                        }
                        else {
                            ++it;
                        }
                    }
                    filteredStations = stations;

                    if (!modifiedStationIds.empty()) {
                        std::cout << "\nStations with IDs ";


                        bool first = true;
                        for (const auto& stationId : modifiedStationIds) {
                            if (!first) {
                                std::cout << ", ";
                            }
                            std::cout << stationId.first;  
                            first = false;
                        }

                        std::cout << " have been deleted." << "\n";
                    }

                    return;
                }
                case 2: {
                    unordered_map<int, bool> modifiedStationIds;
                    for (auto it = stations.begin(); it != stations.end();) {
                        int station_id = it->second.getId();
                        if (filteredStations.find(station_id) != filteredStations.end()) {
                            it = stations.erase(it);
                            modifiedStationIds.emplace(station_id, true);
                        }
                        else {
                            ++it;
                        }
                    }
                    filteredStations = stations;
                    cout << "" << endl;
                    cout << "Stations with IDs ";
                    bool first = true;
                    for (const auto& stationId : modifiedStationIds) {
                        if (!first) {
                            std::cout << ", ";
                        }
                        std::cout << stationId.first;
                        first = false;
                    }
                    cout << " have been deleted." << "\n";
                    return;
                }
                case 3: {
                    addStationFilter(filteredStations);
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
        }
}
