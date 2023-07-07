#include "DeviceDriver.h"
#include <stdexcept>
using namespace std;

class WriteFailException : public exception {};
DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    checkBlockReady(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::checkBlockReady(long address)
{
	if (m_hardware->read(address) != 0xFF)
		throw WriteFailException();
}
