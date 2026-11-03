#include "pch.h"
#include "ProblemRemover.hpp"
#include "../Adapters/IO/FileManagerAdapter.hpp"
// #include <filesystem>  // مكرر: موجود أصلاً بـ pch.h
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
// #include <sstream>  // مكرر: موجود أصلاً بـ pch.h
// #include <fstream>  // مكرر: موجود أصلاً بـ pch.h

namespace fs = std::filesystem;

namespace nsProblemRemover {

    // 🔒 دالة داخلية لحذف سطر بناءً على المفتاح
    namespace {
        /**
         * Remove a line from the file that matches the given key – حذف السطر الذي يحتوي على المفتاح المحدد
         *
         * @param path path to the file – مسار الملف
         * @param key key to match before colon – المفتاح المطلوب مطابقته قبل النقطتين
         * @return true if removal was successful – يرجع true إذا تم الحذف بنجاح
         */
        bool RemoveLineByKey(const std::string& path, const std::string& key) {
            std::ifstream in(path);
            if (!in) return false;

            std::vector<std::string> lines;
            std::string line;
            bool removed = false;

            // Read all lines and skip the matching one – قراءة جميع الأسطر وتجاهل السطر المطابق
            while (std::getline(in, line)) {
                size_t sep = line.find(':');
                if (sep != std::string::npos) {
                    std::string currentKey = line.substr(0, sep);
                    if (currentKey == key) {
                        removed = true;
                        continue;
                    }
                }
                lines.push_back(line);
            }
            in.close();

            if (!removed) return false;

            std::ofstream out(path);
            if (!out) return false;

            for (const auto& l : lines) {
                out << l << "\n";
            }

            return true;
        }
    }

    // Delete problem files and metadata from disk and project – حذف ملفات المشكلة وبياناتها من القرص والمشروع
    bool clsProblemRemover::DeleteProblemStructureFromDiskAndProject(int courseID, int problemIndex, int idWidth, const std::string& vcxprojPath) const {
        // Format identifiers – تنسيق المعرفات
        nsAdapters::clsFileManagerAdapter FileManager;
        const std::string courseIdText = FileManager.FormatID(courseID, idWidth - 1);
        const std::string problemIndexText = FileManager.FormatID(problemIndex, idWidth);
        const std::string shortName = "c" + courseIdText + "Problem" + problemIndexText;

        // Build paths to logic files – بناء مسارات ملفات المنطق
        const std::string problemsFolder = "Courses/Course" + courseIdText + "/Problems";
        const std::string cppPath = problemsFolder + "/" + shortName + ".cpp";
        const std::string hppPath = problemsFolder + "/" + shortName + ".hpp";

        std::vector<std::string> filesToRemove;

        // Collect files to remove from project – جمع الملفات المطلوب حذفها من المشروع
        for (const auto& path : { cppPath, hppPath }) {
            if (fs::exists(path)) {
                std::string relPath = fs::relative(path, fs::current_path()).generic_string();
#ifdef _WIN32
                for (auto& ch : relPath) if (ch == '/') ch = '\\'; // تحويل المسار إلى صيغة ويندوز
#endif
                filesToRemove.push_back(relPath);
            }
        }

        // ملاحظة: التمارين ما عادت تُضاف لملف .vcxproj أصلاً (راجع ProblemInserter.cpp)،
        // فما في داعي نحذفها منه هون كمان - منكمل على حذف الملفات الفعلية من القرص مباشرة.
        // Note: exercises are no longer added to the .vcxproj at all (see ProblemInserter.cpp),
        // so there is nothing to remove there either - we go straight to deleting files on disk.
        (void)vcxprojPath; // parameter kept for interface compatibility – أُبقي الباراميتر للتوافق

        // Delete physical files – حذف الملفات من القرص
        for (const auto& path : { cppPath, hppPath }) {
            try {
                if (fs::exists(path)) {
                    fs::remove(path);
                }
            }
            catch (const fs::filesystem_error& e) {
                std::cerr << "❌ خطأ أثناء حذف الملف: " << e.what() << "\n";
            }
        }

        // Remove metadata entries – حذف الأسطر المرتبطة بالمشكلة من ملفات البيانات
        const std::string logicPath = problemsFolder + "/Logic_Files.txt";
        const std::string namesPath = problemsFolder + "/Names.txt";
        const std::string descPath = problemsFolder + "/Descriptions.txt";
        const std::string fullDescPath = problemsFolder + "/Full_Descriptions.txt";

        bool ok = true;
        ok &= RemoveLineByKey(namesPath, shortName);
        ok &= RemoveLineByKey(descPath, shortName);
        ok &= RemoveLineByKey(fullDescPath, shortName);
        ok &= RemoveLineByKey(logicPath, shortName);

        return ok;
    }

}
