#include "FileManagerAdapter.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

namespace fs = std::filesystem;

namespace nsAdapters {

    bool clsFileManagerAdapter::WriteFile(const std::string& path,
        const std::string& content) {
        // نستخدم الدالة الموجودة في FileHelpers مع تعديل بسيط
        /*std::ofstream file(path);
        if (!file) return false;
        file << content;
        return true;*/
		//return nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(path, content);
        try {
            if (!fs::exists(path)) {
                std::ofstream ofs(path);
                if (!ofs) return false;
                ofs << content;
            }
            return true;
        }
        catch (...) {
            return false;
        }
    }

    std::string clsFileManagerAdapter::ReadFile(const std::string& path) {
        std::ifstream file(path);
        if (!file) return "";

        std::string content((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        return content;
    }

    bool clsFileManagerAdapter::FileExists(const std::string& path) {
        return std::filesystem::exists(path);
    }

    bool clsFileManagerAdapter::AppendToFile(const std::string& path,
        const std::string& content) {
        // نستخدم الدالة الموجودة في FileHelpers
        //return nsFileHelpers::clsFileHelpers::AppendLineToFileIfMissing(path, content);
        try {
            const size_t sep = content.find(':');
            if (sep == std::string::npos) return false; // Invalid format – تنسيق غير صالح

            const std::string key = content.substr(0, sep);

            // Ensure file exists – التأكد من وجود الملف
            if (!fs::exists(path)) {
                std::ofstream ofs(path);
                if (!ofs) return false;
            }

            // Check if key already exists – التحقق من وجود المفتاح مسبقًا
            std::ifstream ifs(path);
            std::string existing;
            while (std::getline(ifs, existing)) {
                size_t existingSep = existing.find(':');
                if (existingSep == std::string::npos) continue;

                std::string existingKey = existing.substr(0, existingSep);
                if (existingKey == key) return true;
            }

            // Append line – إضافة السطر
            std::ofstream ofs(path, std::ios::app);
            if (!ofs) return false;
            ofs << content << "\n";
            return true;
        }
        catch (...) {
            return false;
        }
    }

    std::string clsFileManagerAdapter::FormatID(int id, int width) {
        //return nsFileHelpers::clsFileHelpers::FormatID(id, width);
        std::ostringstream oss;
        oss << std::setw(width) << std::setfill('0') << id;
        return oss.str();
    }

} // namespace nsAdapters