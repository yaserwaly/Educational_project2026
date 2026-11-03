#include "pch.h"
#include <gtest/gtest.h>
#include "../Mocks/MockFileManager.hpp"
//#include "../../Adapters/IO/FileManagerAdapter.hpp"

using namespace nsMock;
//using namespace nsAdapters;
using ::testing::Return;
using ::testing::_;
using ::testing::StrEq;

class FileManagerFixture : public ::testing::Test {
protected:
    clsMockFileManager mock;

    void SetUp() override {
        EXPECT_CALL(mock, FileExists(StrEq("test.txt"))).WillRepeatedly(Return(true));
        EXPECT_CALL(mock, ReadFile(StrEq("test.txt"))).WillRepeatedly(Return("id:123\n"));
    }
};

TEST_F(FileManagerFixture, ReadFileReturnsExpectedContent) {
    EXPECT_EQ(mock.ReadFile("test.txt"), "id:123\n");
}

//TEST(FileManagerAdapterTest, FormatIDPadsCorrectly) {
//    clsFileManagerAdapter adapter;
//    EXPECT_EQ(adapter.FormatID(7), "07");
//    EXPECT_EQ(adapter.FormatID(123, 5), "00123");
//}
