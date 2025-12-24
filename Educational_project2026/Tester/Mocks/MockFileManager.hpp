#pragma once
#include "../../Interfaces/IO/IFileManager.hpp"
#include <gmock/gmock.h>

namespace nsMock {
    class clsMockFileManager : public nsInterfaces::IFileManager {
    public:
        MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& content), (override));
        MOCK_METHOD(std::string, ReadFile, (const std::string& path), (override));
        MOCK_METHOD(bool, FileExists, (const std::string& path), (override));
        MOCK_METHOD(bool, AppendToFile, (const std::string& path, const std::string& content), (override));
        MOCK_METHOD(std::string, FormatID, (int id, int width), (override));
    };
}
