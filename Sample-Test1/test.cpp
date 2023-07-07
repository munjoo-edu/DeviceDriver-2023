#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../project1/DeviceDriver.cpp"
using namespace testing;
using namespace std;

// make r/w mock function
class MockFlashDD : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(FlashTest, TestWriteNormal)
{
	MockFlashDD mock{};
	DeviceDriver dd{ &mock };

	EXPECT_CALL(mock, write)
		.Times(1);

	EXPECT_CALL(mock, read)
		.WillRepeatedly(Return(0xFF));

	dd.write(0x00, 'A');
}

TEST(FlashTest, TestWriteAbnormal)
{
	MockFlashDD mock{};
	DeviceDriver dd{ &mock };

	EXPECT_CALL(mock, read)
		.WillRepeatedly(Return(0x0));

	EXPECT_THROW(dd.write(0x00, 'A'), WriteFailException);
}
