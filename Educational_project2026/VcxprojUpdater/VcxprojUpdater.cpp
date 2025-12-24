#include "VcxprojUpdater.hpp"
#include "../tinyxml2/tinyxml2.h"
#include <filesystem>
#include <set>
#include <iostream>

namespace fs = std::filesystem;
using namespace tinyxml2;

namespace nsVcxprojUpdater {

    /**
     * Append new source/header files to a .vcxproj file – إضافة ملفات جديدة إلى ملف المشروع
     */
    bool clsVcxprojUpdater::AppendFiles(const std::string& vcxprojPath, const std::vector<std::string>& files) {
        XMLDocument doc;
        if (doc.LoadFile(vcxprojPath.c_str()) != XML_SUCCESS) {
            std::cerr << "Failed to load vcxproj.\n";
            return false;
        }

        // 🛡️ Backup original project file – إنشاء نسخة احتياطية
        fs::copy_file(vcxprojPath, vcxprojPath + ".bak", fs::copy_options::overwrite_existing);

        std::set<std::string> existing;
        XMLElement* root = doc.RootElement();

        // 📦 Collect all existing file entries – جمع الملفات الموجودة
        for (XMLElement* group = root->FirstChildElement("ItemGroup"); group; group = group->NextSiblingElement("ItemGroup")) {
            for (XMLElement* cl = group->FirstChildElement(); cl; cl = cl->NextSiblingElement()) {
                const char* inc = cl->Attribute("Include");
                if (inc) {
                    std::string norm = inc;
                    for (auto& ch : norm) if (ch == '/') ch = '\\';
                    existing.insert(norm);
                }
            }
        }

        // 🔍 Locate or create compile/include groups
        XMLElement* compileGroup = nullptr;
        XMLElement* includeGroup = nullptr;
        for (XMLElement* group = root->FirstChildElement("ItemGroup"); group; group = group->NextSiblingElement("ItemGroup")) {
            if (!compileGroup && group->FirstChildElement("ClCompile")) compileGroup = group;
            if (!includeGroup && group->FirstChildElement("ClInclude")) includeGroup = group;
        }
        if (!compileGroup) {
            compileGroup = doc.NewElement("ItemGroup");
            root->InsertEndChild(compileGroup);
        }
        if (!includeGroup) {
            includeGroup = doc.NewElement("ItemGroup");
            root->InsertEndChild(includeGroup);
        }

        bool modified = false;

        // ➕ Add new files if not already present
        for (const auto& file : files) {
            std::string normalized = file;
            for (auto& ch : normalized) if (ch == '/') ch = '\\';

            if (existing.count(normalized)) continue;

            fs::path path(normalized);
            std::string ext = path.extension().string();

            XMLElement* elem = nullptr;
            if (ext == ".cpp" || ext == ".c") {
                elem = doc.NewElement("ClCompile");
                compileGroup->InsertEndChild(elem);
            }
            else if (ext == ".hpp" || ext == ".h") {
                elem = doc.NewElement("ClInclude");
                includeGroup->InsertEndChild(elem);
            }
            else {
                std::cerr << "Skipping unsupported file type: " << normalized << '\n';
                continue;
            }

            elem->SetAttribute("Include", normalized.c_str());
            modified = true;
        }

        // 💾 Save changes
        if (modified && doc.SaveFile(vcxprojPath.c_str()) != XML_SUCCESS) {
            std::cerr << "Failed to save vcxproj.\n";
            return false;
        }

        return true;
    }

    /**
     * Remove specified files from a .vcxproj file – حذف ملفات محددة من ملف المشروع
     */
    bool clsVcxprojUpdater::RemoveFilesFromVcxproj(const std::string& vcxprojPath, const std::vector<std::string>& filesToRemove) {
        XMLDocument doc;
        if (doc.LoadFile(vcxprojPath.c_str()) != XML_SUCCESS) {
            std::cerr << "فشل تحميل vcxproj.\n";
            return false;
        }

        // 🛡️ Backup before deletion
        fs::copy_file(vcxprojPath, vcxprojPath + ".bak", fs::copy_options::overwrite_existing);

        XMLElement* root = doc.RootElement();
        if (!root) return false;

        std::set<std::string> targets;
        for (auto& f : filesToRemove) {
            std::string norm = f;
            for (auto& ch : norm) if (ch == '/') ch = '\\';
            targets.insert(norm);
        }

        bool modified = false;

        // 🧹 Traverse and remove matching entries
        for (XMLElement* group = root->FirstChildElement("ItemGroup"); group; group = group->NextSiblingElement("ItemGroup")) {
            for (XMLElement* elem = group->FirstChildElement(); elem;) {
                const char* inc = elem->Attribute("Include");
                if (inc && targets.count(inc)) {
                    XMLElement* toDelete = elem;
                    elem = elem->NextSiblingElement();
                    group->DeleteChild(toDelete);
                    modified = true;
                }
                else {
                    elem = elem->NextSiblingElement();
                }
            }
        }

        // 💾 Save changes
        if (modified && doc.SaveFile(vcxprojPath.c_str()) != XML_SUCCESS) {
            std::cerr << "فشل حفظ vcxproj بعد الحذف.\n";
            return false;
        }

        return true;
    }

}
