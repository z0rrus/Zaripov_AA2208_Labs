#include "CompressorStation.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>


using namespace std;
int CompressorStation::maxId = 0;

CompressorStation::CompressorStation() {
    id = ++maxId;
    name = "";
    workshopCount = 0;
    efficiency = 0.0;
    nonOperationalPercentage = 0.0;
}

int CompressorStation::getId() const {
    return id;
}

int CompressorStation::getMaxId() {
    return maxId;
}

std::string CompressorStation::getName() const {
    return name;
}

int CompressorStation::getWorkshopCount() const {
    return workshopCount;
}

double CompressorStation::getEfficiency() const {
    return efficiency;
}

double CompressorStation::getNonOperationalPercentage() const {
    return nonOperationalPercentage;
}

void CompressorStation::setId(int newId) {
    id = newId;
    if (newId > maxId) {
        maxId = newId;
    }
}

void CompressorStation::setMaxId(int newMaxId) {
    maxId = newMaxId;
}

void CompressorStation::readData() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter station name: ";
    getline(cin, name);
    logInput(name);

    while (true) {
        cout << "Enter workshop count: ";
        if (cin >> workshopCount && workshopCount > 0) {
            logInput(to_string(workshopCount));
            break;
        }
        else {
            logInput(to_string(workshopCount));
            cout << "Invalid input. Please enter a non-negative integer for workshop count." << endl;
            clearInput();
        }
    }

    while (true) {
        cout << "Enter the number of operational workshops: ";
        int operationalWorkshops;
        if (cin >> operationalWorkshops && operationalWorkshops >= 0 && operationalWorkshops <= workshopCount) {
            logInput(to_string(operationalWorkshops));
            workshopStatus.resize(workshopCount, false);
            for (int i = 0; i < operationalWorkshops; i++) {
                workshopStatus[i] = true;
            }
            break;
        }
        else {
            logInput(to_string(operationalWorkshops));
            cout << "Invalid input. Please enter a non-negative integer no greater than workshop count." << endl;
            clearInput();
        }
    }

    while (true) {
        cout << "Enter efficiency rating: ";
        if (cin >> efficiency && efficiency >= 0) {
            logInput(to_string(efficiency));
            break;
        }
        else {
            logInput(to_string(efficiency));
            cout << "Invalid input. Please enter a non-negative number for efficiency rating." << endl;
            clearInput();
        }
    }
    updateNonOperationalPercentage();
}

void CompressorStation::displayData() const {
    cout << "ID: " << id << endl;
    cout << "Station name: " << name << endl;
    cout << "Workshop count: " << workshopCount << endl;
    cout << "Workshop status:" << endl;
    for (int i = 0; i < workshopCount; i++) {
        cout << "Workshop " << i + 1 << ": " << (workshopStatus[i] ? "Operational" : "Not operational") << endl;
    }
    cout << "Efficiency rating: " << efficiency << endl;
    cout << "Non-operational workshops: " << nonOperationalPercentage << "%" << endl;
   // cout << "   Pipes connected to input: " << pipesConnectedToInput << endl;
    //cout << "   Pipes connected to output: " << pipesConnectedToOutput << endl;
}


void CompressorStation::setWorkshopCount(int newCount) {
    workshopCount = newCount;
}

void CompressorStation::setEfficiency(double newEfficiency) {
    efficiency = newEfficiency;
}

void CompressorStation::setNonOperationalPercentage(double newPercentage) {
    nonOperationalPercentage = newPercentage;
}

void CompressorStation::setWorkshopStatus(int i, bool status) {
    if (i >= 0 && i < workshopCount) {
        workshopStatus[i] = status;
    }
    else {
        throw std::out_of_range("������������ ������ ����");
    }
}

void CompressorStation::updateNonOperationalPercentage() {
    int nonOperationalWorkshops = std::count(workshopStatus.begin(), workshopStatus.end(), false);
    nonOperationalPercentage = (nonOperationalWorkshops / static_cast<double>(workshopStatus.size())) * 100.0;
}


bool CompressorStation::getWorkshopStatus(int index) const {
    if (index >= 0 && index < workshopStatus.size()) {
        return workshopStatus[index];
    }
    else {
        throw std::out_of_range("Invalid workshop index");
    }
}