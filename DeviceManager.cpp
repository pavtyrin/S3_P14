#include <iostream>
#include <iomanip>
#include <string>
#include "DeviceManager.h"

using namespace std;

PeripheralDevice* devices[MAX_DEVICES];
int deviceCount = 0;

void addDefaultDevices()
{
    devices[deviceCount++] = new Keyboard("Office Keyboard", "Mechanical");
    devices[deviceCount - 1]->addPrice(50);
    devices[deviceCount - 1]->addPrice(60);

    devices[deviceCount++] = new Keyboard("Gaming Keyboard", "RGB Mechanical");
    devices[deviceCount - 1]->addPrice(120);
    devices[deviceCount - 1]->addPrice(150);

    devices[deviceCount++] = new Scanner("Office Scanner", 600);
    devices[deviceCount - 1]->addPrice(200);
    devices[deviceCount - 1]->addPrice(250);

    devices[deviceCount++] = new Scanner("High-Res Scanner", 1200);
    devices[deviceCount - 1]->addPrice(350);
    devices[deviceCount - 1]->addPrice(400);

    cout << "Default devices added to the system.\n";
}

void displayAllDevices()
{
    if (deviceCount == 0)
    {
        cout << "No devices available.\n";
        return;
    }

    for (int i = 0; i < deviceCount; i++)
    {
        cout << "\nDevice #" << (i + 1) << ":\n";
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
            cout << "Device limit reached!" << endl;
            delete newDevice;
        }
    }
}

// Функция изменения свойств устройства
void modifyDevice()
{
    if (deviceCount == 0)
    {
        cout << "No devices to modify.\n";
        return;
    }

    cout << "Enter device number to modify: ";

    int index;
    cin >> index;
    if (index < 1 || index > deviceCount)
    {
        cout << "Invalid device number!\n";
        return;
    }

    PeripheralDevice* device = devices[index - 1];
    Keyboard* kb = dynamic_cast<Keyboard*>(device);
    Scanner* sc = dynamic_cast<Scanner*>(device);

    if (kb)
    {
        string newType;
        cout << "Enter new keyboard type: ";
        cin.ignore();
        getline(cin, newType);
        kb->setKeyboardType(newType);
    }
    
    else if (sc)
    {
        int newResolution;
        cout << "Enter new scanner resolution: ";
        cin >> newResolution;
        sc->setResolution(newResolution);
    }
}

void calculateOverallAveragePrice()
{
    if (deviceCount == 0)
    {
        cout << "No devices to calculate average price.\n";
        return;
    }

    double totalSum = 0;
    int totalCount = 0;
    for (int i = 0; i < deviceCount; i++)
    {
        totalSum += devices[i]->calculateAveragePrice();
        totalCount++;
    }
    cout << "Overall average price: " << fixed << setprecision(2)
         << (totalSum / totalCount) << endl;
}

PeripheralDevice* createDevice()
{
    cout << "Choose device type (1 - Keyboard, 2 - Scanner): ";
    int choice;
    cin >> choice;

    PeripheralDevice* newDevice = nullptr;

    if (choice == 1)
    {
        string name, type;
        cout << "Enter keyboard name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter keyboard type: ";
        getline(cin, type);
        newDevice = new Keyboard(name, type);
    }
    
    else if (choice == 2)
    {
        string name;
        int resolution;
        cout << "Enter scanner name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter scanner resolution (DPI): ";
        cin >> resolution;
        newDevice = new Scanner(name, resolution);
    }
    
    else
    {
        cout << "Invalid choice!" << endl;
        return nullptr;
    }

    cout << "How many prices would you like to add? ";
    int numPrices;
    cin >> numPrices;

    for (int i = 0; i < numPrices; i++)
    {
        cout << "Enter price " << (i + 1) << ": ";
        double price;
        cin >> price;
        newDevice->addPrice(price);
    }

    return newDevice;
}

void menu()
{
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Display all devices\n";
        cout << "2. Add new device\n";
        cout << "3. Modify device property\n";
        cout << "4. Calculate average price of all devices\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayAllDevices();
                break;

            case 2:
                addNewDevice();
                break;

            case 3:
                modifyDevice();
                break;

            case 4:
                calculateOverallAveragePrice();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}