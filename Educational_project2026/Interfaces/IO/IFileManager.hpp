#pragma once
#include <string>

namespace nsInterfaces {

    /**
     * Interface for file management operations
     * واجهة عمليات إدارة الملفات
     */
    class IFileManager {
    public:
        virtual ~IFileManager() = default;

        virtual bool WriteFile(const std::string& path,
            const std::string& content) = 0;

        virtual std::string ReadFile(const std::string& path) = 0;

        virtual bool FileExists(const std::string& path) = 0;

        virtual bool AppendToFile(const std::string& path,
            const std::string& content) = 0;

        virtual std::string FormatID(int id, int width = 2) = 0;
    };

} // namespace nsInterfaces