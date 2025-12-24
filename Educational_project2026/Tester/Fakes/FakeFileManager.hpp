#pragma once
#include "../../Interfaces/IO/IFileManager.hpp"
#include <unordered_map>
#include <sstream>
#include <iomanip>

class FakeFileManager : public nsInterfaces::IFileManager {
    std::unordered_map<std::string, std::string> files;

public:
    bool WriteFile(const std::string& path, const std::string& content) override {
        files[path] = content;
        return true;
    }

    std::string ReadFile(const std::string& path) override {
        return files.count(path) ? files[path] : "";
    }

    bool FileExists(const std::string& path) override {
        return files.count(path);
    }

    bool AppendToFile(const std::string& path, const std::string& content) override {
        files[path] += content;
        return true;
    }

    std::string FormatID(int id, int width = 2) override {
        std::ostringstream oss;
        oss << std::setw(width) << std::setfill('0') << id;
        return oss.str();
    }
};
