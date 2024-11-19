#include "Keyboard.h"
#include <iostream>
#include <iomanip>

Keyboard::Keyboard(const string& name, const string& type)
    : PeripheralDevice(name), keyboardType(type) {}

void Keyboard::displayInfo() const
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
    cout << "Тип клавиатуры: " << keyboardType << endl;
}

void Keyboard::setKeyboardType(const string& type)
{
    keyboardType = type;
}