#include "pch.h"
#include <gtest/gtest.h>
#include "../../Adapters/IO/FileManagerAdapter.hpp"

using namespace nsAdapters;

TEST(FileManagerAdapterTest, FormatIDPadsCorrectly) {
    clsFileManagerAdapter adapter;
    EXPECT_EQ(adapter.FormatID(7), "07");
    EXPECT_EQ(adapter.FormatID(123, 5), "00123");
}
