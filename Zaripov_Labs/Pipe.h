#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <vector>


class Pipe {
private:
    int id;
    double length;
    double diameter;
    bool inRepair;
    void setId(int newId);
    friend void loadPipe(std::ifstream& file, std::vector<Pipe>& pipes);

public:
    static int maxId;
    std::string name;

    Pipe();
    int getId() const;
    std::string getName() const;
    double getLength() const;
    double getDiameter() const;
    bool getInRepair() const;
    void readData();
    void displayData() const;
    void setLength(double newLength);
    void setDiameter(double newDiameter);
    void setRepairStatus(bool inRepairStatus);
    static int getNextId();
    void toggleRepairStatus();
};

#endif // PIPE_H
