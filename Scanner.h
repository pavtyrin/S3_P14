#ifndef SCANNER_H
#define SCANNER_H

#include "PeripheralDevice.h"

class Scanner : public PeripheralDevice
{
    private:
        int resolution;

    public:
        Scanner(const string& name, int res);

        void displayInfo() const override;
        void setResolution(int res);
};

#endif // SCANNER_H