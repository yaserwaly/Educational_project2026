#pragma once
#include "../Models/CourseData.hpp"

namespace nsProblemModifier {

    // Class responsible for modifying problem metadata on disk – كلاس مسؤول عن تعديل بيانات المشكلة على القرص
    class clsProblemModifier {
    public:
        /**
         * Modify the metadata of a specific problem inside a course – تعديل بيانات مشكلة معينة داخل دورة
         *
         * @param courseID ID of the course containing the problem – معرف الدورة التي تحتوي على المشكلة
         * @param problemIndex index of the problem within the course – رقم المشكلة داخل الدورة
         * @param updatedProblem updated problem data to apply – بيانات المشكلة المعدّلة
         * @param idWidth number of digits used to format IDs – عدد الخانات المستخدمة لتنسيق المعرفات
         * @return true if modification was successful – يرجع true إذا تم التعديل بنجاح
         */
        bool ModifyProblemStructureOnDisk(int courseID, int problemIndex, const nsProblemData::sProblemData& updatedProblem, int idWidth) const;
    };

}
