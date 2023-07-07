#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    unsigned char read_from_device(long address);
    void check_data_4times(long address, unsigned char ret);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice *m_hardware;
};
