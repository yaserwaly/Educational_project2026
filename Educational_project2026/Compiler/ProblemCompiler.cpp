#include "pch.h"
#include "ProblemCompiler.hpp"
// #include <filesystem>  // مكرر: موجود أصلاً بـ pch.h
// #include <fstream>  // مكرر: موجود أصلاً بـ pch.h
// #include <sstream>  // مكرر: موجود أصلاً بـ pch.h
#include <cstdlib>
#include <cstdio>
#include <cstdlib>  // getenv
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include <array>
#include <memory>

namespace fs = std::filesystem;

namespace nsProblemCompiler {

    // Runs a shell command and returns its full stdout output (trimmed).
    // command must already be a single, fully self-contained string
    // (quoting included) – ينفّذ أمر شل ويرجع ناتجه النصي بعد إزالة
    // المسافات الزائدة؛ يُفترض إنو الأمر جاهز بالكامل مع التنصيص اللازم
    static std::string RunAndCapture(const std::string& command) {
        std::array<char, 256> buffer;
        std::string result;

        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
        if (!pipe) return "";

        while (fgets(buffer.data(), (int)buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        while (!result.empty() && (result.back() == '\n' || result.back() == '\r' || result.back() == ' ')) {
            result.pop_back();
        }
        return result;
    }

    // Locates vcvarsall.bat via vswhere.exe. vswhere always ships at this
    // fixed path under "Program Files (x86)" since VS2017 – يلاقي
    // vcvarsall.bat عبر vswhere.exe الموجود دائمًا بهذا المسار الثابت
    //
    // NOTE: "Program Files (x86)" contains literal parentheses, and
    // cmd.exe has a documented quirk where it refuses to preserve quotes
    // around a single quoted token that contains ( ) when nothing else
    // on the line is quoted. The fix is the classic double-quote-wrap:
    // wrap the ENTIRE command (not just the exe path) in one extra pair
    // of quotes – هذا يحل مشكلة فشل cmd مع الأقواس داخل علامات التنصيص
    /*static std::string FindVcvarsAllPath() {
        const char* pf86 = std::getenv("ProgramFiles(x86)");
        if (!pf86) return "";

        fs::path vswherePath = fs::path(pf86) / "Microsoft Visual Studio" / "Installer" / "vswhere.exe";
        if (!fs::exists(vswherePath)) return "";

        // Inner command: the quoted exe path + its arguments
        std::string inner =
            "\"" + vswherePath.string() + "\""
            " -latest -products * "
            "-requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
            "-property installationPath";

        // Outer wrap: makes cmd treat the whole thing as one quoted unit,
        // which is what lets it preserve the inner quotes correctly even
        // though the path contains "(x86)" – التغليف الخارجي يخلي cmd
        // يحافظ على التنصيص الداخلي رغم وجود الأقواس بالمسار
        std::string fullCmd = "\"" + inner + "\"";

        std::string installPath = RunAndCapture(fullCmd);
        if (installPath.empty()) return "";

        fs::path vcvarsall = fs::path(installPath) / "VC" / "Auxiliary" / "Build" / "vcvarsall.bat";
        if (!fs::exists(vcvarsall)) return "";

        return vcvarsall.string();
    }*/

    static std::string FindVcvarsAllPath() {
        char* pf86 = nullptr;
        size_t len = 0;
        if (_dupenv_s(&pf86, &len, "ProgramFiles(x86)") != 0 || pf86 == nullptr) {
            return "";
        }
        fs::path vswherePath = fs::path(pf86) / "Microsoft Visual Studio" / "Installer" / "vswhere.exe";
        free(pf86);  // ⬅️ _dupenv_s بتعمل allocate، لازم تحرر الذاكرة يدوياً

        if (!fs::exists(vswherePath)) return "";

        std::string inner =
            "\"" + vswherePath.string() + "\""
            " -latest -products * "
            "-requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
            "-property installationPath";

        std::string fullCmd = "\"" + inner + "\"";

        std::string installPath = RunAndCapture(fullCmd);
        if (installPath.empty()) return "";

        fs::path vcvarsall = fs::path(installPath) / "VC" / "Auxiliary" / "Build" / "vcvarsall.bat";
        if (!fs::exists(vcvarsall)) return "";

        return vcvarsall.string();
    }

    bool clsProblemCompiler::CompileAndRun(const std::string& headerPath,
                                            const std::string& signature) {
        fs::path hpp(headerPath);
        fs::path cppFile = hpp;
        cppFile.replace_extension(".cpp");

        if (!fs::exists(cppFile)) {
            std::cerr << "Exercise source not found: " << cppFile << "\n";
            return false;
        }

        fs::path tempDir = fs::path("Temp");
        std::error_code ec;
        fs::create_directories(tempDir, ec);

        fs::path wrapperCpp = tempDir / "runner_main.cpp";
        fs::path outExe     = tempDir / "runner_exe.exe";

        {
            std::ofstream wf(wrapperCpp);
            if (!wf) {
                std::cerr << "Failed to create wrapper file.\n";
                return false;
            }
            wf << "#include \"" << fs::absolute(hpp).generic_string() << "\"\n";
            wf << "int main() {\n";
            wf << "    " << signature << "();\n";
            wf << "    return 0;\n";
            wf << "}\n";
        }

        static std::string s_vcvarsall; // cached after first lookup
        if (s_vcvarsall.empty()) {
            s_vcvarsall = FindVcvarsAllPath();
        }

        if (s_vcvarsall.empty()) {
            std::cerr << "Could not locate a Visual Studio C++ installation "
                         "(vswhere/vcvarsall.bat). Please install the "
                         "\"Desktop development with C++\" workload.\n";
            return false;
        }

        // Same double-quote-wrap trick applied here for safety, even
        // though this particular path usually has no parentheses –
        // نفس أسلوب التغليف المزدوج، احتياطًا، رغم إنو هاد المسار عادة
        // ما فيه أقواس
        std::string inner =
            "\"" + s_vcvarsall + "\" x64 >nul && "
            "cl /nologo /std:c++20 /EHsc "
            "\"" + wrapperCpp.string() + "\" "
            "\"" + cppFile.string() + "\" "
            "\"Shared\\InputForExercises.cpp\" "
            "/Fe:\"" + outExe.string() + "\" "
            "/Fo:\"" + tempDir.string() + "\\\\\"";

        std::string fullCmd = "\"" + inner + "\"";

        int buildResult = std::system(fullCmd.c_str());
        if (buildResult != 0) {
            std::cerr << "Build failed for exercise: " << cppFile << "\n";
            return false;
        }

        std::system(("\"" + outExe.string() + "\"").c_str());
        return true;
    }

}
