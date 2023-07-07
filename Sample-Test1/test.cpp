#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../project1/DeviceDriver.cpp"
using namespace testing;
using namespace std;

// make r/w mock function
class MockFlashDD : public FlashMemoryDevice
{
public:
	//virtual unsigned char read(long address) = 0;
	//virtual void write(long address, unsigned char data) = 0;
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, TestReadNormal) {
	MockFlashDD mock{};
	EXPECT_CALL(mock, read(0x01))
		.Times(5)
		.WillRepeatedly(Return('A'));

	DeviceDriver dd{ &mock };

	unsigned char actual = dd.read(0x01);
	unsigned char expected = 'A';
	EXPECT_EQ(expected, actual);
}

TEST(TestCaseName, TestReadAbnormal) {
	MockFlashDD mock{};
	EXPECT_CALL(mock, read(0x01))
		.Times(5)
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillOnce(Return('B'));

	DeviceDriver dd{ &mock };
	
	EXPECT_THROW(dd.read(0x01), exception);
}
