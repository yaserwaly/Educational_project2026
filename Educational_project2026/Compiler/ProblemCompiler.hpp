#pragma once
#include <string>

namespace nsProblemCompiler {

    /**
     * Compiles and runs a single exercise on demand, isolated from the
     * main project build – يبني وينفّذ تمرين واحد فقط عند الطلب، بمعزل
     * عن بناء المشروع الرئيسي
     */
    class clsProblemCompiler {
    public:
        /**
         * @param headerPath relative path to the problem's .hpp (sProblemData::FilePath)
         *                   المسار النسبي لملف الهيدر الخاص بالتمرين
         * @param signature  fully qualified callable, e.g. "c01Problem003::clsProblem003::Run"
         *                   (sProblemData::Namespace) – التوقيع الكامل القابل للاستدعاء
         * @return true if the exercise built and ran successfully
         */
        static bool CompileAndRun(const std::string& headerPath,
                                   const std::string& signature);
    };

}
