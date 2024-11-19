#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "PeripheralDevice.h"

class Keyboard : public PeripheralDevice
{
    private:
        string keyboardType;

    public:
        Keyboard(const string& name, const string& type);

        void displayInfo() const override;
        void setKeyboardType(const string& type);
};

#endif // KEYBOARD_H