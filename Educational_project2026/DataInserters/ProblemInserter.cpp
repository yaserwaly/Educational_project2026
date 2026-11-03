#include "pch.h"
#include "ProblemInserter.hpp"
// #include <filesystem>  // مكرر: موجود أصلاً بـ pch.h
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include "../Adapters/IO/FileManagerAdapter.hpp"
#include "../Models/CourseData.hpp"

namespace fs = std::filesystem;

namespace nsProblemInserter {

    /**
     * Create full structure for a new problem inside a course – إنشاء الهيكل الكامل لمشكلة جديدة داخل دورة
     *
     * This includes:
     * - Folder creation – إنشاء مجلدات
     * - Header and source file generation – توليد ملفات .hpp و .cpp
     * - Dispatcher registration – تسجيل الدالة في نظام التنفيذ
     * - Metadata updates – تحديث ملفات البيانات النصية
     * - Project file update (.vcxproj) – تعديل ملف المشروع لإضافة الملفات
     */
    bool clsProblemInserter::CreateProblemStructureOnDisk(int courseID, const nsProblemData::sProblemData& Problem, int problemIndex, int idWidth) const {
        // 🔢 Format course and problem IDs – تنسيق المعرفات
        nsAdapters::clsFileManagerAdapter FileManager;
        const std::string courseIdText = FileManager.FormatID(courseID, idWidth - 1);
        const std::string problemIndexText = FileManager.FormatID(problemIndex, idWidth);

        // 📁 Prepare folder paths – تجهيز مسارات المجلدات
        const std::string baseFolder = "Courses/Course" + courseIdText;
        const std::string problemsFolder = baseFolder + "/Problems";
        fs::create_directories(problemsFolder);

        // 🧩 Generate file and class names – توليد أسماء الملفات والكلاسات
        const std::string shortName = "c" + courseIdText + "Problem" + problemIndexText;
        const std::string className = "clsProblem" + problemIndexText;
        const std::string headerName = shortName + ".hpp";
        const std::string cppName = shortName + ".cpp";
        const std::string headerPath = problemsFolder + "/" + headerName;
        const std::string cppPath = problemsFolder + "/" + cppName;

        // 📄 Generate header file content – توليد محتوى ملف الهيدر
        std::string headerContent;
        headerContent += "#pragma once\n\n";
        headerContent += "namespace " + shortName + " {\n\n";
        headerContent += "    class " + className + " {\n";
        headerContent += "    public:\n";
        headerContent += "        static void Run();\n";
        headerContent += "    };\n\n";
        headerContent += "}\n";

        if (!FileManager.WriteFile(headerPath, headerContent)) return false;

        // 🧠 Generate cpp file content – توليد محتوى ملف cpp
        // ملاحظة: لم يعد هذا الملف يُضاف لمشروع Visual Studio الرئيسي، ولا يحتاج
        // تسجيل نفسه بـ DispatcherRegistrar — يُبنى ويُشغَّل لحاله عبر ProblemCompiler
        // (باستخدام التوقيع المخزّن بـ Logic_Files.txt مباشرة).
        std::string cppContent;
        cppContent += "#include <iostream>\n";
        cppContent += "#include \"" + headerName + "\"\n\n";
        cppContent += "namespace " + shortName + " {\n\n";
        cppContent += "    void " + className + "::Run() {\n";
        cppContent += "        std::cout << \"Hello from " + Problem.Name + "!\\n\";\n";
        cppContent += "    }\n\n";
        cppContent += "}\n";

        if (!FileManager.WriteFile(cppPath, cppContent)) return false;

        // 🗂️ Update metadata files – تحديث ملفات البيانات النصية
        const std::string namesPath = problemsFolder + "/Names.txt";
        const std::string descPath = problemsFolder + "/Descriptions.txt";
        const std::string fullDescPath = problemsFolder + "/Full_Descriptions.txt";
        const std::string logicFilesPath = problemsFolder + "/Logic_Files.txt";

        const std::string problemKey = shortName;
        const std::string logicSignature = shortName + "::" + className + "::Run";

        const std::string nameLine = problemKey + ": " + Problem.Name;
        const std::string descLine = problemKey + ": " + Problem.Description;
        const std::string fullDescLine = problemKey + ": " + Problem.FullDescription;
        const std::string logicLine = problemKey + ": " + logicSignature + ", Courses/Course" + courseIdText + "/Problems/" + headerName;

        if (!FileManager.AppendToFile(namesPath, nameLine)) return false;
        if (!FileManager.AppendToFile(descPath, descLine)) return false;
        if (!FileManager.AppendToFile(fullDescPath, fullDescLine)) return false;
        if (!FileManager.AppendToFile(logicFilesPath, logicLine)) return false;

        // 🛠️ Exercises are intentionally NOT added to the main .vcxproj anymore.
        // ملفات التمارين لا تُضاف لملف المشروع الرئيسي بعد الآن –
        // تبقى على القرص فقط، ويتم بناؤها وتشغيلها لحالها عبر ProblemCompiler
        // (Logic_Files.txt يوثّق مسارها وتوقيعها، وهذا كافٍ للتشغيل).
        // هذا ما يمنع تضخّم وقت البناء مع ازدياد عدد التمارين.
        //
        // const std::string vcxprojPath = "Educational_project2026.vcxproj";
        // const std::string ccppPath = "Courses\\Course" + courseIdText + "\\Problems\\" + cppName;
        // const std::string chppPath = "Courses\\Course" + courseIdText + "\\Problems\\" + headerName;
        // std::vector<std::string> newFiles = { ccppPath, chppPath };
        // nsVcxprojUpdater::clsVcxprojUpdater::AppendFiles(vcxprojPath, newFiles);

        return true;
    }

}
