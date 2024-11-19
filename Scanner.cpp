#include "Scanner.h"
#include <iostream>
#include <iomanip>

Scanner::Scanner(const string& name, int res) 
    : PeripheralDevice(name), resolution(res) {}

void Scanner::displayInfo() const
{
    cout << setw(20) << left << "Name of device" 
         << setw(25) << left << "Price range" 
         << setw(20) << left << "Average price" << endl;
    cout << setfill('-') << setw(65) << "-" << endl;
    cout << setfill(' ') << setw(20) << left << deviceName;

    for (int i = 0; i < priceCount; i++)
    {
        cout << "$" << setw(10) << fixed << setprecision(2) << prices[i] << " ";
    }

    cout << "$" << setw(18) << fixed << setprecision(2) << calculateAveragePrice() << endl;

    cout << endl;
    cout << "Разрешение сканера: " << resolution << " DPI" << endl;
}

void Scanner::setResolution(int res)
{
    if (res > 0)
    {
        resolution = res;
    }
    
    else
    {
        cout << endl;
        cout << "Разрешение сканера -- положительное число." << endl;
        cout << endl;
        cout << "Свойство устройства не изменено." << endl;
    }
}