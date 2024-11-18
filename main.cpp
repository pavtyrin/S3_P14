#include <iostream>
#include <string>
#include "Keyboard.h"
#include "Scanner.h"
#include "PeripheralDevice.h"
#include <iomanip>

using namespace std;

PeripheralDevice* createDevice() {
    cout << "Choose device type (1 - Keyboard, 2 - Scanner): ";
    int choice;
    cin >> choice;

    PeripheralDevice* newDevice = nullptr;

    if (choice == 1) {
        string name, type;
        cout << "Enter keyboard name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter keyboard type: ";
        getline(cin, type);
        newDevice = new Keyboard(name, type);
    } else if (choice == 2) {
        string name;
        int resolution;
        cout << "Enter scanner name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter scanner resolution (DPI): ";
        cin >> resolution;
        newDevice = new Scanner(name, resolution);
    } else {
        cout << "Invalid choice!" << endl;
        return nullptr;
    }

    // Добавление цен для нового устройства
    cout << "How many prices would you like to add? ";
    int numPrices;
    cin >> numPrices;

    for (int i = 0; i < numPrices; i++) {
        cout << "Enter price " << (i + 1) << ": ";
        double price;
        cin >> price;
        newDevice->addPrice(price);
    }

    return newDevice;
}

int main() {
    PeripheralDevice* devices[4];
    int deviceCount = 4;

    devices[0] = new Keyboard("Office Keyboard", "Membrane");
    devices[0]->addPrice(30.99);
    devices[0]->addPrice(35.49);

    devices[1] = new Keyboard("Gaming Keyboard", "Mechanical");
    devices[1]->addPrice(50.99);
    devices[1]->addPrice(60.99);

    devices[2] = new Scanner("Office Scanner", 1200);
    devices[2]->addPrice(100.0);
    devices[2]->addPrice(110.5);

    devices[3] = new Scanner("Photo Scanner", 2400);
    devices[3]->addPrice(150.0);
    devices[3]->addPrice(170.0);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display all devices\n";
        cout << "2. Add new device\n";
        cout << "3. Modify device property\n";
        cout << "4. Calculate average price of all devices\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Отображение устройств
                for (int i = 0; i < deviceCount; i++) {
                    cout << "\nDevice #" << (i + 1) << ":\n";
                    devices[i]->displayInfo();
                }
                break;

            case 2: { // Добавление нового устройства
                PeripheralDevice* newDevice = createDevice();
                if (newDevice) {
                    if (deviceCount < 4) {
                        devices[deviceCount++] = newDevice;
                    } else {
                        cout << "Device limit reached!" << endl;
                    }
                }
                break;
            }

            case 3: { // Изменение свойств устройства
                cout << "Enter device number to modify: ";
                int index;
                cin >> index;
                if (index < 1 || index > deviceCount) {
                    cout << "Invalid device number!\n";
                    break;
                }
                PeripheralDevice* device = devices[index - 1];
                Keyboard* kb = dynamic_cast<Keyboard*>(device);
                Scanner* sc = dynamic_cast<Scanner*>(device);

                if (kb) {
                    string newType;
                    cout << "Enter new keyboard type: ";
                    cin.ignore();
                    getline(cin, newType);
                    kb->setKeyboardType(newType);
                } else if (sc) {
                    int newResolution;
                    cout << "Enter new scanner resolution: ";
                    cin >> newResolution;
                    sc->setResolution(newResolution);
                }
                break;
            }

            case 4: { // Вычисление средней цены
                double totalSum = 0;
                int totalCount = 0;
                for (int i = 0; i < deviceCount; i++) {
                    totalSum += devices[i]->calculateAveragePrice();
                    totalCount++;
                }
                cout << "Overall average price: " << fixed << setprecision(2) 
                     << (totalSum / totalCount) << endl;
                break;
            }

            case 5: // Выход
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    // Освобождение памяти
    for (int i = 0; i < deviceCount; i++) {
        delete devices[i];
    }

    return 0;
}
