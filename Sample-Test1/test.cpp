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

	dd.write(0x00, 'A');
}
