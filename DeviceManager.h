#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "PeripheralDevice.h"
#include "Keyboard.h"
#include "Scanner.h"

// Константы
const int MAX_DEVICES = 100;

// Глобальные переменные
extern PeripheralDevice* devices[MAX_DEVICES];
extern int deviceCount;

// Функции
void displayAllDevices();
void addNewDevice();
void modifyDevice();
void calculateOverallAveragePrice();
PeripheralDevice* createDevice();
void addDefaultDevices();
void menu();

#endif // DEVICEMANAGER_H
