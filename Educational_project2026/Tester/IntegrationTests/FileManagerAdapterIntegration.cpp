#include "pch.h"
#include <gtest/gtest.h>
// #include <filesystem>  // مكرر: موجود أصلاً بـ pch.h
#include "../../Adapters/IO/FileManagerAdapter.hpp"

using namespace nsAdapters;
namespace fs = std::filesystem;

TEST(FileManagerAdapterIntegration, WriteAndReadFile) {
    
    clsFileManagerAdapter adapter;
    std::string path = (fs::temp_directory_path() / "test_file.txt").string();

    EXPECT_TRUE(adapter.WriteFile(path, "Hello Yaser"));
    EXPECT_TRUE(adapter.FileExists(path));
    EXPECT_EQ(adapter.ReadFile(path), "Hello Yaser");

    fs::remove(path);  // تنظيف
}

TEST(FileManagerAdapterIntegration, AppendToFileAvoidsDuplicateKeys) {
    clsFileManagerAdapter adapter;
    std::string path = (fs::temp_directory_path() / "test_append.txt").string();

    adapter.WriteFile(path, "");  // إنشاء الملف
    EXPECT_TRUE(adapter.AppendToFile(path, "id:123"));
    EXPECT_TRUE(adapter.AppendToFile(path, "id:123"));  // يجب أن يتجاهل التكرار

    std::string content = adapter.ReadFile(path);
    int count = std::count(content.begin(), content.end(), '\n');
    EXPECT_EQ(count, 1);  // فقط سطر واحد

    fs::remove(path);
}
