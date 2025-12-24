#include <gtest/gtest.h>
#include "FakeFileManager.hpp"

TEST(FileManagerFakeTest, WriteAndReadWorksInMemory) {
    FakeFileManager fake;
    EXPECT_TRUE(fake.WriteFile("virtual.txt", "Hello"));
    EXPECT_TRUE(fake.FileExists("virtual.txt"));
    EXPECT_EQ(fake.ReadFile("virtual.txt"), "Hello");
}

TEST(FileManagerFakeTest, FormatIDWorksCorrectly) {
    FakeFileManager fake;
    EXPECT_EQ(fake.FormatID(42), "42");
    EXPECT_EQ(fake.FormatID(7, 3), "007");
}
