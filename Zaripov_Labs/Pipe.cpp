#include "Pipe.h"
#include "Utils.h"
#include <iostream>


using namespace std;
int Pipe::maxId = 0;

Pipe::Pipe() : id(++maxId), name(""), length(0), diameter(0), inRepair(false), inputStationId(0), outputStationId(0) {}

int Pipe::getId() const {
    return id;
}

int Pipe::getMaxId() {
    return maxId;
}

std::string Pipe::getName() const {
    return name;
}

double Pipe::getLength() const {
    return length;
}

double Pipe::getDiameter() const {
    return diameter;
}

bool Pipe::getInRepair() const {
    return inRepair;
}

void Pipe::setId(int newId) {
    if (newId > maxId) {
        maxId = newId;
    }
    id = newId;
}

void Pipe::setMaxId(int newMaxId) {
    maxId = newMaxId;
}

void Pipe::readData(int* pdiameter /*= nullptr*/) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter pipe name: ";
    getline(cin, name);
    logInput(name);

    while (true) {
        cout << "Enter pipe length (km): ";
        if (cin >> length && length >= 0) {
            logInput(to_string(length));
            break;
        }
        else {
            logInput(to_string(length));
            cout << "Invalid input. Please enter a non-negative number for length." << endl;
            clearInput();
        }
    }

    if (pdiameter == nullptr || *pdiameter == 0) {
        while (true) {
            cout << "Enter pipe diameter (choose from 500, 700, 1000, 1400 mm): ";
            if (cin >> diameter && (diameter == 500 || diameter == 700 || diameter == 1000 || diameter == 1400)) {
                logInput(to_string(diameter));
                break;
            }
            else {
                logInput(to_string(diameter));
                cout << "Invalid input. Please enter one of the allowed diameters: 500, 700, 1000, 1400." << endl;
                clearInput();
            }
        }
    }
    else {
        diameter = *pdiameter;
    }
    cout << "The pipe has been successfully created." << endl;
}

void Pipe::displayData() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Length: " << length << " km" << endl;
    cout << "Diameter: " << diameter << " mm" << endl;
    cout << "Repair status: " << (inRepair ? "Under repair" : "Operational") << endl;
    std::cout << "Connection status: " << (inputStationId != 0 && outputStationId != 0
        ? std::to_string(inputStationId) + " -> " + std::to_string(outputStationId)
        : "Not connected") << std::endl;
}

void Pipe::setLength(double newLength) {
    length = newLength;
}

void Pipe::setDiameter(double newDiameter) {
    diameter = newDiameter;
}

void Pipe::setRepairStatus(bool inRepairStatus) {
    inRepair = inRepairStatus;
}

void Pipe::toggleRepairStatus() {
    inRepair = !inRepair;
}

bool Pipe::isConnected() const {
    return inputStationId != 0 && outputStationId != 0;
}
bool Pipe::isConnected(int stId) const {
    return inputStationId != stId || outputStationId != stId;
}

void Pipe::disconnect()
{
    inputStationId = outputStationId = 0;
}
