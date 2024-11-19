#include "PeripheralDevice.h"
#include <iostream>
#include <iomanip>

PeripheralDevice::PeripheralDevice(const string& name)
    : deviceName(name), prices(nullptr), priceCount(0) {}

void PeripheralDevice::addPrice(double price)
{
    double* newPrices = new double[priceCount + 1];
    for (int i = 0; i < priceCount; i++)
    {
        newPrices[i] = prices[i];
    }
    newPrices[priceCount] = price;
    delete[] prices;
    prices = newPrices;
    priceCount++;
}

double PeripheralDevice::calculateAveragePrice() const
{
    if (priceCount == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < priceCount; i++)
    {
        sum += prices[i];
    }
    return sum / priceCount;
}

void PeripheralDevice::displayInfo() const
{
    cout << setw(20) << left << "Device Name" 
         << setw(25) << left << "Prices" 
         << setw(20) << left << "Average Price" << endl;
    cout << setfill('-') << setw(65) << "-" << endl;
    cout << setfill(' ') << setw(20) << left << deviceName;

    for (int i = 0; i < priceCount; i++)
    {
        cout << setw(10) << fixed << setprecision(2) << prices[i] << " ";
    }

    cout << setw(20) << fixed << setprecision(2) << calculateAveragePrice() << endl;
}

PeripheralDevice::~PeripheralDevice()
{
    delete[] prices;
}