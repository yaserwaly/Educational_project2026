#include "pch.h"
#include "ProblemLoader.hpp"
#include "../Models/ProblemData.hpp"
// #include <fstream>  // مكرر: موجود أصلاً بـ pch.h
// #include <string>  // مكرر: موجود أصلاً بـ pch.h
// #include <vector>  // مكرر: موجود أصلاً بـ pch.h
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h

namespace nsProblemLoader {

    // Load all problems from the given folder – تحميل جميع المشاكل من المجلد المحدد
    std::vector<nsProblemData::sProblemData> clsProblemLoader::LoadProblems(const std::string& folder) const {
        std::vector<nsProblemData::sProblemData> problems;

        // فتح ملفات البيانات النصية للمشاكل
        std::ifstream names(folder + "/Names.txt");
        std::ifstream descs(folder + "/Descriptions.txt");
        std::ifstream fulls(folder + "/Full_Descriptions.txt");
        std::ifstream logic(folder + "/Logic_Files.txt");

        if (!names || !descs || !fulls || !logic) {
            std::cerr << "❌ فشل في فتح ملفات البيانات.\n";
            return {};
        }

        std::string nameLine, descLine, fullLine, logicLine;
        int Code = 1;

        // قراءة الأسطر المتقابلة من الملفات الأربعة – Read corresponding lines from all four files
        while (std::getline(names, nameLine) &&
            std::getline(descs, descLine) &&
            std::getline(fulls, fullLine) &&
            std::getline(logic, logicLine)) {

            // Extract value after colon – استخراج القيمة بعد النقطتين
            auto extractValue = [](const std::string& line) -> std::string {
                size_t sep = line.find(':');
                if (sep == std::string::npos) return "";
                std::string val = line.substr(sep + 1);
                if (!val.empty() && val[0] == ' ') val = val.substr(1);
                return val;
                };

            std::string name = extractValue(nameLine);
            std::string desc = extractValue(descLine);
            std::string full = extractValue(fullLine);
            std::string logicData = extractValue(logicLine);

            // Split logicData into namespace and file path – تقسيم بيانات المنطق إلى namespace ومسار الملف
            size_t comma = logicData.find(',');
            if (comma == std::string::npos) continue;

            std::string ns = logicData.substr(0, comma);
            std::string path = logicData.substr(comma + 1);
            if (!path.empty() && path[0] == ' ') path = path.substr(1);

            nsProblemData::sProblemData p;

            // استخراج رقم المشكلة من namespace مثل: c01Problem001::clsProblem001::Run
            size_t probStart = ns.find("Problem");
            if (probStart != std::string::npos) {
                std::string digits;
                for (size_t i = probStart + 7; i < ns.size(); ++i) {
                    if (isdigit(ns[i])) digits += ns[i];
                    else break;
                }
                try {
                    p.ID = std::stoi(digits);
                }
                catch (...) {
                    continue;
                }
            }
            else {
                continue;
            }

            // تعبئة بيانات المشكلة – Fill in problem data
            p.Code = Code++;
            p.Name = name;
            p.Description = desc;
            p.FullDescription = full;
            p.Namespace = ns;
            p.FilePath = path;

            problems.push_back(p);
        }

        return problems;
    }

}
