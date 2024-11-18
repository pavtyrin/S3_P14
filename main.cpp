#include "DeviceManager.h"

int main() {
    addDefaultDevices(); // Добавление устройств по умолчанию
    menu();              // Вызов меню
    // Освобождение памяти
    for (int i = 0; i < deviceCount; i++) {
        delete devices[i];
    }
    return 0;
}
