#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <unordered_map>


class Pipe {
private:
    int id;
    static int maxId;
    double length;
    bool inRepair;
    void setId(int newId);
    static void setMaxId(int NewMaxId);
    friend void loadPipe(std::ifstream& file, std::unordered_map<int, Pipe>& pipes);
    friend void calculateMaxId(const std::unordered_map<int, Pipe>& pipes);
    friend void updateMaxPipeId(const std::unordered_map<int, Pipe>& pipes);

public:
    std::string name;
    Pipe();
    int inputStationId;
    int outputStationId;
    double diameter;
    int getId() const;
    static int getMaxId();
    std::string getName() const;
    double getLength() const;
    double getDiameter() const;
    bool getInRepair() const;
    void readData(int* pdiameter = nullptr);
    void displayData() const;
    void setLength(double newLength);
    void setDiameter(double newDiameter);
    void setRepairStatus(bool inRepairStatus);
    void toggleRepairStatus();
    bool isConnected() const;
    bool isConnected(int stId) const;
    void disconnect();
};

#endif // PIPE_H
