#ifndef COMPRESSORSTATION_H
#define COMPRESSORSTATION_H

#include <string>
#include <vector>

class CompressorStation {
private:
    int id;
    double efficiency;
    double nonOperationalPercentage;
    void setId(int newId);
    friend void loadStation(std::ifstream& file, std::vector<CompressorStation>& stations);

public:
    static int maxId;
    std::string name;
    int workshopCount;
    std::vector<bool> workshopStatus;

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
};

#endif // COMPRESSORSTATION_H
