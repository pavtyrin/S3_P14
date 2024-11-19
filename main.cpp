#include "DeviceManager.h"

int main()
{
    addDefaultDevices();
    menu();

    for (int i = 0; i < deviceCount; i++)
    {
        delete devices[i];
    }
    return 0;
}