#pragma once
#include "../Models/CourseData.hpp"
#include <string>

namespace nsCourseLoader {

    // Class responsible for loading course metadata from disk – كلاس مسؤول عن تحميل بيانات الدورة من القرص
    class clsCourseLoader {
    public:
        /**
         * Load course metadata from the specified folder – تحميل بيانات الدورة من المجلد المحدد
         *
         * @param courseFolder path to the course folder – مسار مجلد الدورة
         * @return course data structure with loaded values – بنية بيانات الدورة بعد التحميل
         */
        nsCourseData::sCourseData LoadCourse(const std::string& courseFolder) const;
    };

}
