#include "CourseRemover.hpp"
#include "../Adapters/IO/FileManagerAdapter.hpp"
#include "../VcxprojUpdater/VcxprojUpdater.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;

namespace nsCourseRemover {

    // Delete course folder and remove its files from the project – حذف مجلد الدورة وإزالة ملفاته من المشروع
    bool clsCourseRemover::DeleteCourseStructureFromDiskAndProject(int courseID, int idWidth, const std::string& vcxprojPath) const {
        // Format course ID and build folder path – تنسيق معرف الدورة وبناء مسار المجلد
        nsAdapters::clsFileManagerAdapter FileManager;
        const std::string courseIdText = FileManager.FormatID(courseID, idWidth);
        const std::string baseFolder = "Courses/Course" + courseIdText;

        std::vector<std::string> filesToRemove;

        // Collect all .cpp/.hpp/.h files for removal – جمع جميع الملفات المطلوب حذفها من المشروع
        if (fs::exists(baseFolder)) {
            for (const auto& entry : fs::recursive_directory_iterator(baseFolder)) {
                if (!entry.is_regular_file()) continue;
                std::string ext = entry.path().extension().string();
                if (ext == ".cpp" || ext == ".hpp" || ext == ".h") {
                    std::string relPath = fs::relative(entry.path(), fs::current_path()).generic_string();
#ifdef _WIN32
                    for (auto& ch : relPath) if (ch == '/') ch = '\\'; // تحويل المسار إلى صيغة ويندوز
#endif
                    filesToRemove.push_back(relPath);
                }
            }
        }

        // Remove files from .vcxproj – حذف الملفات من ملف المشروع
        if (!nsVcxprojUpdater::clsVcxprojUpdater::RemoveFilesFromVcxproj(vcxprojPath, filesToRemove)) {
            std::cerr << "فشل حذف الملفات من vcxproj.\n";
            return false;
        }

        // Delete course folder from disk – حذف مجلد الدورة من القرص
        try {
            if (fs::exists(baseFolder)) {
                fs::remove_all(baseFolder);
                std::cout << "✅ تم حذف المجلد بنجاح.\n";
            }
            else {
                std::cout << "⚠️ المجلد غير موجود مسبقًا: " << baseFolder << "\n";
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "❌ خطأ أثناء محاولة الحذف: " << e.what() << "\n";
            return false;
        }

        return true;
    }

}
