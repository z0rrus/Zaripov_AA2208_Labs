#ifndef COMPRESSORSTATION_H
#define COMPRESSORSTATION_H

#include <string>
#include <unordered_map>

class CompressorStation {
private:
    int id;
    static int maxId;
    double efficiency;
    double nonOperationalPercentage;
    void setId(int newId);
    static void setMaxId(int NewMaxId);
    friend void loadStation(std::ifstream& file, std::unordered_map<int, CompressorStation>& stations);
    friend void updateMaxStationId(const std::unordered_map<int, CompressorStation>& stations);
    friend void calculateMaxStationsId(const std::unordered_map<int, CompressorStation>& stations);

public:
    std::string name;
    int workshopCount;
    std::vector<bool> workshopStatus;
    static int getMaxId();
    //int pipesConnectedToInput; 
    //int pipesConnectedToOutput;
    CompressorStation();
    int getId() const;
    std::string getName() const;
    int getWorkshopCount() const;
    double getEfficiency() const;
    double getNonOperationalPercentage() const;
    void readData();
    void displayData() const;
    void setWorkshopCount(int newCount);
    void setEfficiency(double newEfficiency);
    void setNonOperationalPercentage(double newPercentage);
    void setWorkshopStatus(int index, bool status);
    void updateNonOperationalPercentage();
    bool getWorkshopStatus(int index) const;
}; 

#endif // COMPRESSORSTATION_H
