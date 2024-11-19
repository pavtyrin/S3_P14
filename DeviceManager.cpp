#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "DeviceManager.h"

using namespace std;

PeripheralDevice* devices[MAX_DEVICES];
int deviceCount = 0;

void addDefaultDevices()
{
    devices[deviceCount++] = new Keyboard("Office Keyboard", "Mechanical");
    devices[deviceCount - 1]->addPrice(50);
    devices[deviceCount - 1]->addPrice(60);

    devices[deviceCount++] = new Scanner("Office Scanner", 600);
    devices[deviceCount - 1]->addPrice(200);
    devices[deviceCount - 1]->addPrice(250);

    devices[deviceCount++] = new Keyboard("Gaming Keyboard", "RGB Mechanical");
    devices[deviceCount - 1]->addPrice(120);
    devices[deviceCount - 1]->addPrice(150);

    devices[deviceCount++] = new Scanner("High-Res Scanner", 1200);
    devices[deviceCount - 1]->addPrice(350);
    devices[deviceCount - 1]->addPrice(400);

    cout << endl;
    cout << endl;
    cout << "Устройства по умолчанию добавлены в программу.\n";
    cout << endl;
}

void displayAllDevices()
{
    if (deviceCount == 0)
    {
        cout << endl;
        cout << "Нет доступных устройств.\n";
        return;
    }

    for (int i = 0; i < deviceCount; i++)
    {
        cout << endl;
        cout << "\nУстройство №" << (i + 1) << ":\n";
        cout << endl;
        devices[i]->displayInfo();
    }
}

void addNewDevice()
{
    PeripheralDevice* newDevice = createDevice();

    if (newDevice)
    {
        if (deviceCount < MAX_DEVICES)
        {
            devices[deviceCount++] = newDevice;
        }
        
        else
        {
            cout << endl;
            cout << "Достигнут предел для количества устройств." << endl;
            delete newDevice;
        }
    }
}

void modifyDevice()
{
    if (deviceCount == 0)
    {
        cout << endl;
        cout << "Нет устройств, которые можно было бы изменить.\n";
        return;
    }

    cout << endl;
    cout << "Введите номер устройства для изменения: ";

    int index;
    cin >> index;
    if (index < 1 || index > deviceCount)
    {
        cout << endl;
        cout << "Неверный номер устройства.\n";
        cout << endl;
        cout << "Свойство устройства не изменено." << endl;
        return;
    }

    PeripheralDevice* device = devices[index - 1];
    Keyboard* kb = dynamic_cast<Keyboard*>(device);
    Scanner* sc = dynamic_cast<Scanner*>(device);

    if (kb)
    {
        string newType;
        cout << endl;
        cout << "Введите новый тип клавиатуры: ";
        cin.ignore();
        getline(cin, newType);
        kb->setKeyboardType(newType);
    }
    
    else if (sc)
    {
        int newResolution;
        cout << endl;
        cout << "Введите новое разрешение сканера: ";
        cin >> newResolution;
        sc->setResolution(newResolution);
    }
}

void calculateOverallAveragePrice()
{
    if (deviceCount == 0)
    {
        cout << endl;
        cout << "Нет устройств для расчета средней цены.\n";
        return;
    }

    double totalSum = 0;
    int totalCount = 0;
    for (int i = 0; i < deviceCount; i++)
    {
        totalSum += devices[i]->calculateAveragePrice();
        totalCount++;
    }
    cout << endl;
    cout << "Общая средняя цена: " << "$" << fixed << setprecision(2)
         << (totalSum / totalCount) << endl;
}

PeripheralDevice* createDevice()
{
    cout << endl;
    cout << "Выберите тип устройства (1 -- Клавиатура, 2 -- Сканер): ";
    int choice;
    cin >> choice;

    PeripheralDevice* newDevice = nullptr;

    if (choice == 1)
    {
        string name, type;
        cout << endl;
        cout << "Введите название клавиатуры: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите тип клавиатуры: ";
        getline(cin, type);
        newDevice = new Keyboard(name, type);
    }
    
    else if (choice == 2)
    {
        string name;
        int resolution;
        cout << endl;
        cout << "Введите название сканера: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите разрешение сканера (DPI): ";
        cin >> resolution;
        if (resolution > 0)
        {
            newDevice = new Scanner(name, resolution);
        }
    
        else
        {
            cout << endl;
            cout << "Разрешение сканера -- положительное число." << endl;
            cout << endl;
            cout << "Устройство не добавлено." << endl;
            return nullptr;
        }
    }
    
    else
    {
        cout << endl;
        cout << "Неверный выбор." << endl;
        return nullptr;
    }

    cout << endl;
    cout << "Сколько цен вы хотели бы добавить в диапазон? ";
    int numPrices;
    cin >> numPrices;

    for (int i = 0; i < numPrices; i++)
    {
        cout << endl;
        cout << "Введите цену " << (i + 1) << ": ";
        double price;
        cin >> price;
        newDevice->addPrice(price);
    }

    cout << endl;
    cout << "Устройство добавлено." << endl;
    return newDevice;
}

void menu()
{
    string choice;

    while (true)
    {
        cout << "\nМеню:\n";
        cout << "1. Отображение всех устройств\n";
        cout << "2. Добавить новое устройство\n";
        cout << "3. Изменить свойство устройства\n";
        cout << "4. Рассчитать среднюю цену на все устройства\n";
        cout << "0. Выход\n";
        cout << endl;
        cout << "Введите свой выбор: ";
        cin >> choice;

        if (choice == "1")
        {
            displayAllDevices();
            continue;
        }

        if (choice == "2")
        {
            addNewDevice();
            displayAllDevices();
            continue;
        }

        if (choice == "3")
        {
            modifyDevice();
            displayAllDevices();
            continue;
        }

        if (choice == "4")
        {
            calculateOverallAveragePrice();
            continue;
        }

        if (choice == "0")
        {
            cout << endl;
            cout << "Выход из программы...\n";
            cout << endl;
            exit (0);
        }

        else
        {
            cout << endl;
            cout << "Неверный выбор. Пробуйте снова.\n";
            continue;
        }
    }
}