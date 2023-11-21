#include "Pipe.h"
#include "Utils.h"
#include <iostream>


using namespace std;
int Pipe::maxId = 0;

Pipe::Pipe() : id(++maxId), name(""), length(0), diameter(0), inRepair(false) {}

int Pipe::getId() const {
    return id;
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

void Pipe::readData() {
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

    while (true) {
        cout << "Enter pipe diameter (cm): ";
        if (cin >> diameter && diameter >= 0) {
            logInput(to_string(diameter));
            break;
        }
        else {
            logInput(to_string(diameter));
            cout << "Invalid input. Please enter a non-negative number for diameter." << endl;
            clearInput();
        }
    }
}

void Pipe::displayData() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Length: " << length << " km" << endl;
    cout << "Diameter: " << diameter << " cm" << endl;
    cout << "Repair status: " << (inRepair ? "Under repair" : "Operational") << endl;
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
