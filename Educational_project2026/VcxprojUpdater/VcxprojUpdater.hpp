#pragma once
#include <string>
#include <vector>

namespace nsVcxprojUpdater {

    /**
     * Utility class for modifying .vcxproj project files – كلاس أدوات لتعديل ملفات مشروع Visual Studio
     *
     * This class supports:
     * - Appending new source/header files – إضافة ملفات مصدر أو ترويسات جديدة
     * - Removing existing files from the project – حذف ملفات موجودة من المشروع
     * - Ensuring safe XML-based updates – ضمان تعديل آمن باستخدام XML
     */
    class clsVcxprojUpdater {
    public:
        /**
         * Append new source/header files to the project – إضافة ملفات جديدة إلى المشروع
         *
         * Automatically detects file type (.cpp/.hpp) and inserts into appropriate <ItemGroup> – يكتشف نوع الملف ويضيفه إلى المجموعة المناسبة
         *
         * @param vcxprojPath path to the .vcxproj file – مسار ملف المشروع
         * @param files list of relative file paths to add – قائمة بالمسارات النسبية للملفات المطلوب إضافتها
         * @return true if project was modified successfully – يرجع true إذا تم تعديل المشروع بنجاح
         */
        static bool AppendFiles(const std::string& vcxprojPath, const std::vector<std::string>& files);

        /**
         * Remove specified files from the project – حذف ملفات محددة من ملف المشروع
         *
         * Searches for matching <ClCompile> or <ClInclude> entries and removes them – يبحث عن العناصر المطابقة ويحذفها
         *
         * @param vcxprojPath path to the .vcxproj file – مسار ملف المشروع
         * @param filesToRemove list of file paths to remove – قائمة الملفات المطلوب حذفها
         * @return true if project was modified successfully – يرجع true إذا تم تعديل المشروع بنجاح
         */
        static bool RemoveFilesFromVcxproj(const std::string& vcxprojPath, const std::vector<std::string>& filesToRemove);
    };

}
