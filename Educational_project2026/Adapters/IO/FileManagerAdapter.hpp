#pragma once
#include "../../Interfaces/IO/IFileManager.hpp"
#include "../../Registry/FileHelpers.hpp"
#include <filesystem>
#include <fstream>

namespace nsAdapters {

    /**
     * Adapter for FileHelpers to implement IFileManager interface
     * محول لـ FileHelpers لتنفيذ واجهة IFileManager
     */
    class clsFileManagerAdapter : public nsInterfaces::IFileManager {
    public:
        bool WriteFile(const std::string& path,
            const std::string& content) override;

        std::string ReadFile(const std::string& path) override;

        bool FileExists(const std::string& path) override;

        bool AppendToFile(const std::string& path,
            const std::string& content) override;

        std::string FormatID(int id, int width = 2) override;
    };

} // namespace nsAdapters