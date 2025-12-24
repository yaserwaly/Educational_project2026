#include "DefaultProblem.hpp"
#include <fstream>
#include <filesystem>
#include "../Adapters/IO/FileManagerAdapter.hpp"

namespace nsDefaultProblem {

    // Constructor to initialize with course ID – مُنشئ لتهيئة الكلاس بمعرّف الدورة
    clsDefaultProblem::clsDefaultProblem(int courseID)
        : CourseID(courseID) {
    }

    // Generate the file path for storing default problem – توليد مسار الملف الخاص بالمشكلة الافتراضية
    std::string clsDefaultProblem::FilePath() const {
        nsAdapters::clsFileManagerAdapter FileManager;
        return "Courses/Course" + FileManager.FormatID(CourseID, 2) + "/DefaultProblem.txt";
    }

    // Load the default problem code from file – تحميل كود المشكلة الافتراضية من الملف
    int clsDefaultProblem::Load() const {
        std::ifstream file(FilePath());
        if (!file) return -1;

        int code;
        file >> code;
        return code;
    }

    // Save the default problem code to file – حفظ كود المشكلة الافتراضية في الملف
    void clsDefaultProblem::Save(int code) const {
        std::ofstream file(FilePath());
        file << code;
    }

    // Clear the contents of the default problem file – مسح محتويات ملف المشكلة الافتراضية
    void clsDefaultProblem::Clear() const {
        std::ofstream file(FilePath(), std::ios::trunc);
    }

    // Remove the default problem file from disk – حذف ملف المشكلة الافتراضية من القرص
    void clsDefaultProblem::Remove() const {
        std::filesystem::remove(FilePath());
    }

    // Check if the default problem file exists – التحقق من وجود ملف المشكلة الافتراضية
    bool clsDefaultProblem::Exists() const {
        return std::filesystem::exists(FilePath());
    }

}
