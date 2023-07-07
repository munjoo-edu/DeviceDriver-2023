#include "DeviceDriver.h"
#include <stdexcept>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

unsigned char DeviceDriver::read_from_device(long address)
{
	return m_hardware->read(address);
}

void DeviceDriver::check_data_4times(long address, unsigned char ret)
{
	for(int i= 0; i<4; i++)
	{
		if (ret != m_hardware->read(address))
			throw exception("HW fault");
	}
}

int DeviceDriver::read(long address)
{
    unsigned char ret;

    ret = read_from_device(address);
    check_data_4times(address, ret);

    return (int)ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
