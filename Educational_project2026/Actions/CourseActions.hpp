#pragma once
#include "../Models/CourseData.hpp"
#include <vector>

namespace nsCourseActions {

    /**
     * Class for managing course-level actions – كلاس لإدارة العمليات المتعلقة بالدورات
     *
     * This includes:
     * - Adding new courses – إضافة دورات جديدة
     * - Updating existing courses – تعديل الدورات الحالية
     * - Deleting courses from disk and project – حذف الدورات من القرص وملف المشروع
     */
    class clsCourseActions {
    public:
        /**
         * Add a new course and refresh the course list – إضافة دورة جديدة وتحديث قائمة الدورات
         *
         * Creates the course structure on disk and reloads the full list – ينشئ هيكل الدورة على القرص ويعيد تحميل القائمة
         *
         * @param AllCourses reference to the full course list – مرجع لقائمة الدورات الكاملة
         * @return true if course was added successfully – يرجع true إذا تمت إضافة الدورة بنجاح
         */
        static bool AddNewCourse(std::vector<nsCourseData::sCourseData>& AllCourses);

        /**
         * Update an existing course and refresh the list – تعديل دورة موجودة وتحديث القائمة
         *
         * Applies user-selected changes and reloads the updated list – ينفّذ التعديلات المختارة ويعيد تحميل القائمة
         *
         * @param selectedCourse reference to the course to update – مرجع للدورة المطلوب تعديلها
         * @param AllCourses reference to the full course list – مرجع لقائمة الدورات الكاملة
         * @return true if update was successful – يرجع true إذا تم التعديل بنجاح
         */
        static bool UpdateCourse(nsCourseData::sCourseData& selectedCourse, std::vector<nsCourseData::sCourseData>& AllCourses);

        /**
         * Delete a course and refresh the list – حذف دورة وتحديث القائمة
         *
         * Confirms deletion, removes course from disk and project, then reloads the list – يؤكد الحذف، ويزيل الدورة من القرص والمشروع، ثم يعيد تحميل القائمة
         *
         * @param selectedCourse reference to the course to delete – مرجع للدورة المطلوب حذفها
         * @param AllCourses reference to the full course list – مرجع لقائمة الدورات الكاملة
         * @return true if deletion was successful – يرجع true إذا تم الحذف بنجاح
         */
        static bool DeleteCourse(const nsCourseData::sCourseData& selectedCourse, std::vector<nsCourseData::sCourseData>& AllCourses);
    };

}
