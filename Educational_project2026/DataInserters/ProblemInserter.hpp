#pragma once
#include "../Models/CourseData.hpp"

namespace nsProblemInserter {

    /**
     * Class responsible for creating problem structure inside a course – كلاس مسؤول عن إنشاء هيكل المشكلة داخل الدورة
     */
    class clsProblemInserter {
    public:
        /**
         * Create folders, logic files, and register the problem in all relevant systems – إنشاء مجلدات وملفات منطقية وتسجيل المشكلة في الأنظمة المرتبطة
         *
         * This includes:
         * - Creating the problem folder – إنشاء مجلد خاص بالمشكلة
         * - Generating header and source files – توليد ملفات .hpp و .cpp
         * - Registering the problem in dispatcher and project files – تسجيل المشكلة في نظام التنفيذ وملف المشروع
         *
         * @param courseID ID of the course – معرف الدورة التي تنتمي إليها المشكلة
         * @param Problem full problem metadata – بيانات المشكلة الكاملة
         * @param problemIndex index of the problem within the course – ترتيب المشكلة داخل الدورة
         * @param idWidth number of digits used to format IDs – عدد الخانات المستخدمة لتنسيق المعرفات
         * @return true if structure was created successfully – يرجع true إذا تم إنشاء الهيكل بنجاح
         */
        bool CreateProblemStructureOnDisk(int courseID, const nsProblemData::sProblemData& Problem, int problemIndex, int idWidth) const;
    };

}
