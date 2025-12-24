#pragma once
#include "../Models/CourseData.hpp"

namespace nsCourseInserter {

    /**
     * Class responsible for creating course folder and file structure – كلاس مسؤول عن إنشاء هيكل مجلدات وملفات الدورة
     *
     * This includes:
     * - Creating the course directory and subfolders – إنشاء مجلد الدورة والمجلدات الفرعية
     * - Writing metadata files – كتابة ملفات البيانات الأساسية
     * - Generating a default problem – توليد مشكلة افتراضية داخل الدورة
     */
    class clsCourseInserter {
    public:
        /**
         * Create the full folder and file structure for a new course – إنشاء هيكل الدورة الكامل على القرص
         *
         * @param course full course metadata – بيانات الدورة المطلوب إنشاؤها
         * @param idWidth number of digits used to format course ID – عدد الخانات المستخدمة لتنسيق معرف الدورة
         * @return true if structure was created successfully – يرجع true إذا تم إنشاء الهيكل بنجاح
         */
        bool CreateCourseStructureOnDisk(const nsCourseData::sCourseData& course, int idWidth = 2) const;
    };

}
