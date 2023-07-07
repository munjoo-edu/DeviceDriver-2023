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

class FlashTestFixture : public testing::Test
{
protected:
	void SetUp() override
	{
	}
public:
	MockFlashDD mock{};
	DeviceDriver dd{ &mock };
};

TEST_F(FlashTestFixture, TestReadNormal) {
	EXPECT_CALL(mock, read(0x01))
		.Times(5)
		.WillRepeatedly(Return('A'));

	unsigned char actual = dd.read(0x01);
	unsigned char expected = 'A';
	EXPECT_EQ(expected, actual);
}

TEST_F(FlashTestFixture, TestReadAbnormal) {
	EXPECT_CALL(mock, read(0x01))
		.Times(5)
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillOnce(Return('B'));

	EXPECT_THROW(dd.read(0x01), ReadFailException);
}

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
