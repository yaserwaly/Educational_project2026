#include "CourseInserter.hpp"
#include <filesystem>
#include <string>
//#include "../Registry/FileHelpers.hpp" // ⬅️ قديم
#include "../VcxprojUpdater/VcxprojUpdater.hpp"
#include "../DataInserters/ProblemInserter.hpp"
#include "../Models/CourseData.hpp"
#include "../Models/ProblemData.hpp"
#include "../Adapters/IO/FileManagerAdapter.hpp" // ⬅️ جديد

namespace fs = std::filesystem;

namespace nsCourseInserter {

    /**
     * Helper class to generate default problem data – كلاس مساعد لإنشاء بيانات مشكلة افتراضية
     */
    class Helper {
    public:
        /**
         * Create a default problem with placeholder content – إنشاء مشكلة افتراضية بمحتوى مبدئي
         *
         * @return initialized problem object – يرجع كائن مشكلة جاهز
         */
        static nsProblemData::sProblemData NewProblem() {
            nsProblemData::sProblemData Problem{};
            Problem.Name = "Problem 01";
            Problem.Description = "Problem 01";
            Problem.FullDescription = "Problem 01";
            return Problem;
        }
    };

    /**
     * Create full folder and file structure for a new course – إنشاء هيكل المجلدات والملفات الكامل لدورة جديدة
     *
     * This includes:
     * - Creating course and problems folders – إنشاء مجلد الدورة ومجلد المشاكل
     * - Writing metadata files – كتابة ملفات البيانات
     * - Creating a default problem – إنشاء مشكلة افتراضية داخل الدورة
     *
     * @param course course metadata – بيانات الدورة
     * @param idWidth number of digits used to format course/problem IDs – عدد الخانات لتنسيق المعرفات
     * @return true if course structure was created successfully – يرجع true إذا تم إنشاء الهيكل بنجاح
     */
    bool clsCourseInserter::CreateCourseStructureOnDisk(const nsCourseData::sCourseData& course, int idWidth) const {
        // 🔢 Format course ID and build base folder path – تنسيق معرف الدورة وبناء المسار
        nsAdapters::clsFileManagerAdapter FileManager; // ⬅️ جديد

        const std::string courseIdText = FileManager.FormatID(course.ID, idWidth); // ⬅️ جديد
		//const std::string courseIdText = nsFileHelpers::clsFileHelpers::FormatID(course.ID, idWidth); // ⬅️ قديم
        const std::string baseFolder = "Courses/Course" + courseIdText;

        // 📁 Create course and problems folders – إنشاء مجلد الدورة ومجلد المشاكل
        fs::create_directories(baseFolder);
        fs::create_directories(baseFolder + "/Problems");

        // 📝 Prepare course metadata file – تجهيز ملف بيانات الدورة
        std::string courseFile = baseFolder + "/Course.txt";
        std::string courseTxtContent;
        courseTxtContent += "ID: " + std::to_string(course.ID) + "\n";
        courseTxtContent += "Name: " + course.Name + "\n";
        courseTxtContent += "Description: " + course.Description + "\n";
        courseTxtContent += "FullDescription: " + course.FullDescription + "\n";

        // 💾 Write course file and supporting files – كتابة ملف الدورة والملفات الداعمة
        /*if (!nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(courseFile, courseTxtContent)) return false;
        if (!nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(baseFolder + "/DefaultProblem.txt", "")) return false;
        if (!nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(baseFolder + "/Problems/Names.txt", "")) return false;
        if (!nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(baseFolder + "/Problems/Descriptions.txt", "")) return false;
        if (!nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(baseFolder + "/Problems/Full_Descriptions.txt", "")) return false;
        if (!nsFileHelpers::clsFileHelpers::WriteFileIfNotExists(baseFolder + "/Problems/Logic_Files.txt", "")) return false;*/

        if (!FileManager.WriteFile(courseFile, courseTxtContent)) return false;
        if (!FileManager.WriteFile(baseFolder + "/DefaultProblem.txt", "")) return false;
        if (!FileManager.WriteFile(baseFolder + "/Problems/Names.txt", "")) return false;
        if (!FileManager.WriteFile(baseFolder + "/Problems/Descriptions.txt", "")) return false;
        if (!FileManager.WriteFile(baseFolder + "/Problems/Full_Descriptions.txt", "")) return false;
        if (!FileManager.WriteFile(baseFolder + "/Problems/Logic_Files.txt", "")) return false;

        // 🧩 Create default problem structure inside the course – إنشاء مشكلة افتراضية داخل الدورة
        nsProblemData::sProblemData nProblem = Helper::NewProblem();
        nsProblemInserter::clsProblemInserter problemInserter;
        if (!problemInserter.CreateProblemStructureOnDisk(course.ID, nProblem, 1, idWidth + 1)) return false;

        return true;
    }

}
