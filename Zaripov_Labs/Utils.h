#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Pipe.h"
#include "CompressorStation.h"


using namespace std;
void clearInput();
void logInput(const std::string& input);
void showPipes(const std::unordered_map<int, Pipe>& pipes);
void showStations(const std::unordered_map<int, CompressorStation>& stations);
void addPipeFilter(std::unordered_map<int, Pipe>& pipes);
void addStationFilter(std::unordered_map<int, CompressorStation>& stations);
void showObjectsWithFilters(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations);
void editPipeStatus(std::unordered_map<int, Pipe>& pipes);
void editWorkshop(CompressorStation& station);
void editWorkshopStatus(std::unordered_map<int, CompressorStation>& stations);
void savePipe(const Pipe& pipe, std::ofstream& file);
void saveStation(const CompressorStation& station, std::ofstream& file);
void saveData(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations);
void calculateMaxId(const std::unordered_map<int, Pipe>& pipes);
void loadPipe(std::ifstream& file, std::unordered_map<int, Pipe>& pipes);
void calculateMaxStationsId(const std::unordered_map<int, CompressorStation>& stations);
void loadStation(std::ifstream& file, std::unordered_map<int, CompressorStation>& stations);
void updateMaxPipeId(const std::unordered_map<int, Pipe>& pipes);
void updateMaxStationId(const std::unordered_map<int, CompressorStation>& stations);
void loadData(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations);
void deletePipes(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations,
    const std::unordered_map<int, bool>& pipeIds);
void deleteStations(std::unordered_map<int, CompressorStation>& stations, std::unordered_map<int, Pipe>& pipes,
    const std::unordered_map<int, bool>& stationIds);
void deleteObject(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations);
void connectPipeToStations(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations);
void connectStationsAndUpdatePipe(std::unordered_map<int, Pipe>& pipes, CompressorStation& inputStation, CompressorStation& outputStation, int pipeId);
void decreaseConnectedToInput(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, int pipeId);

#endif // UTILS_H
