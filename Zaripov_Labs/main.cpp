#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include "Pipe.h"
#include "CompressorStation.h"
#include "Utils.h"


int main() {
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, CompressorStation> stations;

    while (true) {
        std::cout << std::endl;
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add a pipe" << std::endl;
        std::cout << "2. Add a compressor station" << std::endl;
        std::cout << "3. View all objects" << std::endl;
        std::cout << "4. Editing the operation status of pipes" << std::endl;
        std::cout << "5. Starting and stopping workshops" << std::endl;
        std::cout << "6. Save" << std::endl;
        std::cout << "7. Load" << std::endl;
        std::cout << "8. Delete object" << std::endl;
        std::cout << "9. Connection stations" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << std::endl;

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            clearInput();
            continue;
        }
        logInput(std::to_string(choice));
        std::cout << std::endl;

        switch (choice) {
        case 1: {
            Pipe pipe;
            pipe.readData();
            pipes.insert(std::make_pair(pipes.size() + 1, pipe));
            break;
        }
        case 2: {
            CompressorStation station;
            station.readData();
            stations.insert(std::make_pair(stations.size() + 1, station));
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
        case 9: {
            connectPipeToStations(pipes, stations);
            break;
        }
        case 0: {
            std::cout << "Exiting the program." << std::endl;
            return 0;
        }
        default: {
            std::string action = "Invalid choice entered. Please try again.";
            std::cout << action << std::endl;
            break;
        }
        }
    }

    return 0;
}
