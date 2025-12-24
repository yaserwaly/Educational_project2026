#pragma once
#include "../Models/ProblemData.hpp"
#include <string>
#include <vector>

namespace nsProblemLoader {

    // Class responsible for loading problems from disk – كلاس مسؤول عن تحميل المشاكل من القرص
    class clsProblemLoader {
    public:
        /**
         * Load all problems from the specified folder – تحميل جميع المشاكل من المجلد المحدد
         *
         * @param problemsFolder path to the folder containing problem metadata – مسار المجلد الذي يحتوي على بيانات المشاكل
         * @return list of loaded problems – قائمة بالمشاكل المحمّلة
         */
        std::vector<nsProblemData::sProblemData> LoadProblems(const std::string& problemsFolder) const;
    };

}
