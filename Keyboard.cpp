#include "Keyboard.h"
#include <iostream>
#include <iomanip>

Keyboard::Keyboard(const string& name, const string& type)
    : PeripheralDevice(name), keyboardType(type) {}

void Keyboard::displayInfo() const {
    cout << setw(20) << left << "Device Name" 
         << setw(25) << left << "Prices" 
         << setw(20) << left << "Average Price" << endl;
    cout << setfill('-') << setw(65) << "-" << endl;
    cout << setfill(' ') << setw(20) << left << deviceName;

    // Отображение цен
    for (int i = 0; i < priceCount; i++) {
        cout << setw(10) << fixed << setprecision(2) << prices[i] << " ";
    }

    // Вычисление и отображение средней цены
    cout << setw(20) << fixed << setprecision(2) << calculateAveragePrice() << endl;

    // Отображение типа клавиатуры
    cout << "Keyboard Type: " << keyboardType << endl;
}

void Keyboard::setKeyboardType(const string& type) {
    keyboardType = type;
}
