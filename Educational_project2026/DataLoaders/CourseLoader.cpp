#include "CourseLoader.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

namespace nsCourseLoader {

    // Load course metadata from its folder – تحميل بيانات الدورة من مجلدها
    nsCourseData::sCourseData clsCourseLoader::LoadCourse(const std::string& CourseFolder) const {
        nsCourseData::sCourseData Course;
        std::ifstream file(CourseFolder + "/Course.txt"); // Open course metadata file – فتح ملف بيانات الدورة
        std::string line;

        // Read each line and extract key-value pairs – قراءة كل سطر واستخراج القيم
        while (std::getline(file, line)) {
            size_t colonPos = line.find(':');
            if (colonPos == std::string::npos) continue; // Skip lines without colon – تجاهل الأسطر التي لا تحتوي على نقطتين

            std::string value = line.substr(colonPos + 1);
            value.erase(0, value.find_first_not_of(" \t")); // Trim leading spaces – إزالة الفراغات من البداية

            // Match line prefix and assign value – مطابقة بداية السطر وتعيين القيمة
            if (line.starts_with("ID:"))
                Course.ID = std::stoi(value);
            else if (line.starts_with("Name:"))
                Course.Name = value;
            else if (line.starts_with("Description:"))
                Course.Description = value;
            else if (line.starts_with("FullDescription:"))
                Course.FullDescription = value;
        }

        return Course;
    }

}
