#include "ProblemModifier.hpp"
#include "../Adapters/IO/FileManagerAdapter.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;

namespace nsProblemModifier {

    // 🔒 دالة داخلية لاستبدال سطر بناءً على المفتاح
    namespace {
        /**
         * Replace a line in the file that matches the given key – استبدال السطر الذي يحتوي على المفتاح المحدد
         *
         * @param path path to the file – مسار الملف
         * @param key key to match before colon – المفتاح المطلوب مطابقته قبل النقطتين
         * @param newValue new value to write after the colon – القيمة الجديدة التي ستكتب بعد النقطتين
         * @return true if replacement was successful – يرجع true إذا تم الاستبدال بنجاح
         */
        bool ReplaceLineByKey(const std::string& path, const std::string& key, const std::string& newValue) {
            std::ifstream in(path);
            if (!in) return false;

            std::vector<std::string> lines;
            std::string line;
            bool replaced = false;

            // Read all lines and replace the matching one – قراءة جميع الأسطر واستبدال السطر المطابق
            while (std::getline(in, line)) {
                size_t sep = line.find(':');
                if (sep != std::string::npos) {
                    std::string currentKey = line.substr(0, sep);
                    if (currentKey == key) {
                        lines.push_back(key + ": " + newValue);
                        replaced = true;
                        continue;
                    }
                }
                lines.push_back(line);
            }
            in.close();

            if (!replaced) return false;

            std::ofstream out(path);
            if (!out) return false;

            for (const auto& l : lines) {
                out << l << "\n";
            }

            return true;
        }
    }

    // Modify problem metadata files on disk – تعديل ملفات بيانات المشكلة على القرص
    bool clsProblemModifier::ModifyProblemStructureOnDisk(int courseID, int problemIndex, const nsProblemData::sProblemData& updatedProblem, int idWidth) const {
        // Format identifiers – تنسيق المعرفات
        nsAdapters::clsFileManagerAdapter FileManager;
        const std::string courseIdText = FileManager.FormatID(courseID, idWidth - 1);
        const std::string problemIndexText = FileManager.FormatID(problemIndex, idWidth);
        const std::string shortName = "c" + courseIdText + "Problem" + problemIndexText;

        // Build paths to metadata files – بناء مسارات ملفات البيانات
        const std::string problemsFolder = "Courses/Course" + courseIdText + "/Problems";
        const std::string namesPath = problemsFolder + "/Names.txt";
        const std::string descPath = problemsFolder + "/Descriptions.txt";
        const std::string fullDescPath = problemsFolder + "/Full_Descriptions.txt";

        // Apply modifications – تنفيذ التعديلات
        bool ok = true;
        ok &= ReplaceLineByKey(namesPath, shortName, updatedProblem.Name);
        ok &= ReplaceLineByKey(descPath, shortName, updatedProblem.Description);
        ok &= ReplaceLineByKey(fullDescPath, shortName, updatedProblem.FullDescription);

        return ok;
    }

}
