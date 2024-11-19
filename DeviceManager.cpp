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

    string input_index;
    int index = -1;
    cin >> input_index;
    try
    {
        index = stoi(input_index);
        if (index < 1 || index > deviceCount)
        {
            cout << endl;
            cout << "Неверный номер устройства.\n";
            cout << endl;
            cout << "Свойство устройства не изменено." << endl;
            return;
        }
    }
    catch (const invalid_argument&)
    {
        cout << endl;
        cout << "Ошибка: индекс должен быть числом. Возврат в главное меню." << endl;
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
        string input_resolution;
        int newResolution = -1;
        cout << endl;
        cout << "Введите новое разрешение сканера: ";
        cin >> input_resolution;
        try
        {
            newResolution = stoi(input_resolution);
        }
        catch (const invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: разрешение должно быть числом. Возврат в главное меню." << endl;
            return;
        }
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
    string input_choice;
    int choice = -1;
    cout << endl;
    cout << "Выберите тип устройства (1 -- Клавиатура, 2 -- Сканер): ";
    cin >> input_choice;
    try
    {
        choice = stoi(input_choice);
        if (choice != 1 && choice != 2)
        {
            cout << endl;
            cout << "Ошибка: выбор должен быть либо 1 -- Клавиатура, либо 2 -- Сканер." << endl;
        }
    }
    catch (const invalid_argument&)
    {
        cout << endl;
        cout << "Ошибка: выбор должен быть числом. Возврат в главное меню." << endl;
    }

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
        string input_resolution;
        int resolution = -1;
        cout << endl;
        cout << "Введите название сканера: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите разрешение сканера (DPI): ";
        cin >> input_resolution;
        try
        {
            resolution = stoi(input_resolution);
            if (resolution <= 0)
            {
                cout << endl;
                cout << "Разрешение сканера -- положительное число." << endl;
                cout << endl;
                cout << "Устройство не добавлено." << endl;
                return nullptr;
            }
        }
        catch (const invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: разрешение должно быть числом. Возврат в главное меню." << endl;
            return nullptr;
        }
        newDevice = new Scanner(name, resolution);
    }
    
    else
    {
        return nullptr;
    }

    cout << endl;
    cout << "Сколько цен вы хотели бы добавить в диапазон? ";
    string input_numPrices;
    int numPrices = -1;
    cin >> input_numPrices;
    try
    {
        numPrices = stoi(input_numPrices);
        if (numPrices <= 0)
        {
            cout << endl;
            cout << "Ошибка: количество цен должно быть положительным числом." << endl;
            return nullptr;
        }
    }
    catch (const invalid_argument&)
    {
        cout << endl;
        cout << "Ошибка: количество цен должно быть числом. Возврат в главное меню." << endl;
        return nullptr;
    }

    for (int i = 0; i < numPrices; i++)
    {
        cout << endl;
        cout << "Введите цену " << (i + 1) << ": ";
        string input_price;
        double price = -1.0;
        cin >> input_price;
        try
        {
            price = stod(input_price);
            if (price <= 0.0)
            {
                cout << endl;
                cout << "Ошибка: цена должна быть положительным числом. Возврат в главное меню." << endl;
                return nullptr;
            }
        }
        catch (const invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: цена должна быть числом. Возврат в главное меню." << endl;
            return nullptr;
        }
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
            size_t initialDeviceCount = deviceCount;
            addNewDevice();
            if (deviceCount > initialDeviceCount)
            {
                displayAllDevices();
            }
            continue;
        }

        if (choice == "3")
        {
            size_t initialDeviceCount = deviceCount;
            modifyDevice();
            if (deviceCount > initialDeviceCount)
            {
                displayAllDevices();
            }
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