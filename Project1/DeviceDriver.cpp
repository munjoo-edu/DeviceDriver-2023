#include "DeviceDriver.h"
#include <stdexcept>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    unsigned char ret;

    ret = m_hardware->read(address);
    for(int i= 0; i<4; i++)
    {
        if (ret != m_hardware->read(address))
            throw exception("HW fault");
    }
    return (int)ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
