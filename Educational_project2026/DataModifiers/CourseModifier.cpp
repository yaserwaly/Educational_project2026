#include "CourseModifier.hpp"
#include "../Adapters/IO/FileManagerAdapter.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;

namespace nsCourseModifier {

    // Modify the course metadata file on disk – تعديل ملف بيانات الدورة على القرص
    bool clsCourseModifier::ModifyCourseStructureOnDisk(const nsCourseData::sCourseData& updatedCourse, int idWidth) const {
        // Format course ID and build file path – تنسيق معرف الدورة وبناء مسار الملف
        nsAdapters::clsFileManagerAdapter FileManager;
        const std::string courseIdText = FileManager.FormatID(updatedCourse.ID, idWidth);
        const std::string baseFolder = "Courses/Course" + courseIdText;
        const std::string courseFile = baseFolder + "/Course.txt";

        // Check if course file exists – التحقق من وجود ملف الدورة
        if (!fs::exists(courseFile)) {
            std::cerr << "Course.txt not found for Course" << courseIdText << "\n";
            return false;
        }

        // Prepare updated content – تجهيز المحتوى الجديد
        std::string courseTxtContent;
        courseTxtContent += "ID: " + std::to_string(updatedCourse.ID) + "\n";
        courseTxtContent += "Name: " + updatedCourse.Name + "\n";
        courseTxtContent += "Description: " + updatedCourse.Description + "\n";
        courseTxtContent += "FullDescription: " + updatedCourse.FullDescription + "\n";

        // Write to file – كتابة المحتوى إلى الملف
        std::ofstream out(courseFile);
        if (!out) {
            std::cerr << "Failed to open Course.txt for writing.\n";
            return false;
        }

        out << courseTxtContent;
        return true;
    }

}
