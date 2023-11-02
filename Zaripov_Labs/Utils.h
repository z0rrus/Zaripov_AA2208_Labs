#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include "Pipe.h"
#include "CompressorStation.h"

void clearInput();
void logInput(const std::string& input);
void showPipes(const std::vector<Pipe>& pipes);
void showStations(const std::vector<CompressorStation>& stations);
void addPipeFilter(std::vector<Pipe>& pipes);
void addStationFilter(std::vector<CompressorStation>& stations);
void showObjectsWithFilters(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations);
void editPipeStatus(std::vector<Pipe>& pipes);
void editWorkshop(CompressorStation& station);
void editWorkshopStatus(std::vector<CompressorStation>& stations);
void savePipe(const Pipe& pipe, std::ofstream& file);
void saveStation(const CompressorStation& station, std::ofstream& file);
void saveData(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations);
void calculateMaxId(const std::vector<Pipe>& pipes);
void loadPipe(std::ifstream& file, std::vector<Pipe>& pipes);
void calculateMaxStationsId(const std::vector<CompressorStation>& stations);
void loadStation(std::ifstream& file, std::vector<CompressorStation>& stations);
void updateMaxPipeId(const std::vector<Pipe>& pipes);
void updateMaxStationId(const std::vector<CompressorStation>& stations);
void loadData(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations);
void deletePipe(std::vector<Pipe>& pipes, int pipeId);
void deleteCompressorStation(std::vector<CompressorStation>& stations, int stationId);
void deleteObject(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations);

#endif // UTILS_H
