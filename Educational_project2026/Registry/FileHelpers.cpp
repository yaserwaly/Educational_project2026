//#include "FileHelpers.hpp"
//#include <filesystem>
//#include <fstream>
//#include <sstream>
//#include <iomanip>
//#include <string>
//
//namespace fs = std::filesystem;
//
//namespace nsFileHelpers {
//
//    /**
//     * Format an integer ID with leading zeros – تنسيق المعرف بإضافة أصفار بادئة
//     *
//     * @param id the number to format – الرقم المطلوب تنسيقه
//     * @param width total width of the formatted string – العرض الكامل للناتج
//     * @return formatted string like "003" – سلسلة منسّقة مثل "003"
//     */
//    std::string clsFileHelpers::FormatID(int id, int width) {
//        std::ostringstream oss;
//        oss << std::setw(width) << std::setfill('0') << id;
//        return oss.str();
//    }
//
//    /**
//     * Write content to file only if it doesn't already exist – كتابة محتوى إلى ملف إذا لم يكن موجودًا
//     *
//     * @param path file path – مسار الملف
//     * @param content content to write – المحتوى المطلوب كتابته
//     * @return true if file was created or already exists – يرجع true إذا تم الإنشاء أو الملف موجود مسبقًا
//     */
//    bool clsFileHelpers::WriteFileIfNotExists(const std::string& path, const std::string& content) {
//        try {
//            if (!fs::exists(path)) {
//                std::ofstream ofs(path);
//                if (!ofs) return false;
//                ofs << content;
//            }
//            return true;
//        }
//        catch (...) {
//            return false;
//        }
//    }
//
//    /**
//     * Append a line to file only if a line with the same key doesn't exist – إضافة سطر إلى الملف إذا لم يكن موجودًا مسبقًا
//     *
//     * @param path file path – مسار الملف
//     * @param line line to append (must contain ':') – السطر المطلوب إضافته (يجب أن يحتوي على ':')
//     * @return true if line was added or already exists – يرجع true إذا تم الإضافة أو السطر موجود مسبقًا
//     */
//    bool clsFileHelpers::AppendLineToFileIfMissing(const std::string& path, const std::string& line) {
//        try {
//            const size_t sep = line.find(':');
//            if (sep == std::string::npos) return false; // Invalid format – تنسيق غير صالح
//
//            const std::string key = line.substr(0, sep);
//
//            // Ensure file exists – التأكد من وجود الملف
//            if (!fs::exists(path)) {
//                std::ofstream ofs(path);
//                if (!ofs) return false;
//            }
//
//            // Check if key already exists – التحقق من وجود المفتاح مسبقًا
//            std::ifstream ifs(path);
//            std::string existing;
//            while (std::getline(ifs, existing)) {
//                size_t existingSep = existing.find(':');
//                if (existingSep == std::string::npos) continue;
//
//                std::string existingKey = existing.substr(0, existingSep);
//                if (existingKey == key) return true;
//            }
//
//            // Append line – إضافة السطر
//            std::ofstream ofs(path, std::ios::app);
//            if (!ofs) return false;
//            ofs << line << "\n";
//            return true;
//        }
//        catch (...) {
//            return false;
//        }
//    }
//
//}
