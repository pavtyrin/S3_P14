#ifndef PERIPHERALDEVICE_H
#define PERIPHERALDEVICE_H

#include <string>
using namespace std;

class PeripheralDevice {
protected:
    string deviceName;   // Название устройства
    double* prices;      // Динамический массив цен
    int priceCount;      // Количество цен

public:
    PeripheralDevice(const string& name);
    void addPrice(double price);
    virtual double calculateAveragePrice() const;
    virtual void displayInfo() const;
    virtual ~PeripheralDevice();
};

#endif // PERIPHERALDEVICE_H