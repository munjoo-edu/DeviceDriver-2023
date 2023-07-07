#include "DeviceDriver.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class ReadFailException : public exception {};
class WriteFailException : public exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    unsigned char ret;

    ret = read_from_device(address);
    check_data_4times(address, ret);

    return (int)ret;
}

void DeviceDriver::write(long address, int data)
{
    checkBlockReady(address);
    m_hardware->write(address, (unsigned char)data);
}

unsigned char DeviceDriver::read_from_device(long address)
{
	return m_hardware->read(address);
}

void DeviceDriver::check_data_4times(long address, unsigned char ret)
{
	for(int i= 0; i<4; i++)
	{
		if (ret != m_hardware->read(address))
			throw ReadFailException();
	}
}

void DeviceDriver::checkBlockReady(long address)
{
	if (m_hardware->read(address) != 0xFF)
		throw WriteFailException();
}

class flashApp
{
public:
	flashApp(DeviceDriver* tar_dd)
		:dd(tar_dd) {};

	void ReadAndPrint(long startAddr, long endAddr)
	{
		for(long tar_addr = startAddr; tar_addr <= endAddr; tar_addr++)
		{
			cout << dd->read(tar_addr) << " ";
		}
	}

private:
	DeviceDriver* dd = nullptr;
};