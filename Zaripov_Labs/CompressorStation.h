#ifndef COMPRESSORSTATION_H
#define COMPRESSORSTATION_H

#include <string>
#include <vector>

class CompressorStation {
private:
    int id;
    double efficiency;
    double nonOperationalPercentage;

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
    void setId(int newId);
    void readData();
    void displayData() const;
    void setWorkshopCount(int newCount);
    void setEfficiency(double newEfficiency);
    void setNonOperationalPercentage(double newPercentage);
    void setWorkshopStatus(int index, bool status);
    void updateNonOperationalPercentage();
};

#endif // COMPRESSORSTATION_H
