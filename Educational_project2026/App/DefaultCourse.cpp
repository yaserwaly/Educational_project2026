#include "DefaultCourse.hpp"
#include <fstream>
#include <filesystem>

namespace nsDefaultCourse {

    // Constructor to initialize default course handler with file path – مُنشئ لتهيئة مدير الدورة الافتراضية بمسار الملف
    clsDefaultCourse::clsDefaultCourse(const std::string& path)
        : StoragePath(path) {
    }

    // Load the default course code from file – تحميل كود الدورة الافتراضية من الملف
    int clsDefaultCourse::Load() const {
        std::ifstream file(StoragePath);
        if (!file) return -1;

        int code;
        file >> code;
        return code;
    }

    // Save the default course code to file – حفظ كود الدورة الافتراضية في الملف
    void clsDefaultCourse::Save(int code) const {
        std::ofstream file(StoragePath);
        file << code;
    }

    // Clear the contents of the default course file – مسح محتويات ملف الدورة الافتراضية
    void clsDefaultCourse::Clear() const {
        std::ofstream file(StoragePath, std::ios::trunc);
    }

    // Remove the default course file from disk – حذف ملف الدورة الافتراضية من القرص
    void clsDefaultCourse::Remove() const {
        std::filesystem::remove(StoragePath);
    }

    // Check if the default course file exists – التحقق من وجود ملف الدورة الافتراضية
    bool clsDefaultCourse::Exists() const {
        return std::filesystem::exists(StoragePath);
    }

}
