#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);

protected:
    unsigned char read_from_device(long address);
    void check_data_4times(long address, unsigned char ret);

	FlashMemoryDevice *m_hardware;
};
