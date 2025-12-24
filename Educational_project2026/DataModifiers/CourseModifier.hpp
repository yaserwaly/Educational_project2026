#pragma once
#include "../Models/CourseData.hpp"

namespace nsCourseModifier {

    // Class responsible for modifying course metadata on disk – كلاس مسؤول عن تعديل بيانات الدورة على القرص
    class clsCourseModifier {
    public:
        /**
         * Modify the course metadata file on disk – تعديل ملف بيانات الدورة على القرص
         *
         * @param updatedCourse the updated course data – بيانات الدورة بعد التعديل
         * @param idWidth number of digits used to format course ID – عدد الخانات المستخدمة لتنسيق معرف الدورة
         * @return true if modification was successful – يرجع true إذا تم التعديل بنجاح
         */
        bool ModifyCourseStructureOnDisk(const nsCourseData::sCourseData& updatedCourse, int idWidth) const;
    };

}
