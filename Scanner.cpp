#include "Scanner.h"
#include <iostream>
#include <iomanip>

Scanner::Scanner(const string& name, int res) 
    : PeripheralDevice(name), resolution(res) {}

void Scanner::displayInfo() const {
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

    // Отображение разрешения сканера
    cout << "Scanner Resolution: " << resolution << " DPI" << endl;
}

void Scanner::setResolution(int res) {
    if (res > 0) {
        resolution = res;
    } else {
        cout << "Resolution must be positive!" << endl;
    }
}
