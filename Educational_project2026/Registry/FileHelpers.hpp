//#pragma once
//#include <string>
//
//namespace nsFileHelpers {
//
//    /**
//     * Utility class for file operations – كلاس أدوات لمهام التعامل مع الملفات
//     */
//    class clsFileHelpers {
//    public:
//        /**
//         * Format an integer ID with leading zeros – تنسيق المعرف بإضافة أصفار بادئة
//         *
//         * @param id the number to format – الرقم المطلوب تنسيقه
//         * @param width total width of the formatted string – العرض الكامل للناتج
//         * @return formatted string like "03" – سلسلة منسّقة مثل "03"
//         */
//        static std::string FormatID(int id, int width = 2);
//
//        /**
//         * Write content to file only if it doesn't already exist – كتابة محتوى إلى ملف إذا لم يكن موجودًا
//         *
//         * @param path file path – مسار الملف
//         * @param content content to write – المحتوى المطلوب كتابته
//         * @return true if file was created or already exists – يرجع true إذا تم الإنشاء أو الملف موجود مسبقًا
//         */
//        static bool WriteFileIfNotExists(const std::string& path, const std::string& content = "");
//
//        /**
//         * Append a line to file only if a line with the same key doesn't exist – إضافة سطر إلى الملف إذا لم يكن موجودًا مسبقًا
//         *
//         * @param path file path – مسار الملف
//         * @param line line to append (must contain ':') – السطر المطلوب إضافته (يجب أن يحتوي على ':')
//         * @return true if line was added or already exists – يرجع true إذا تم الإضافة أو السطر موجود مسبقًا
//         */
//        static bool AppendLineToFileIfMissing(const std::string& path, const std::string& line);
//    };
//
//}
