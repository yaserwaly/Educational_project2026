#pragma once
#include "../Models/ProblemData.hpp"
#include "../Models/CourseData.hpp"

namespace nsProblemActions {

    /**
     * Class for managing problem-level actions – كلاس لإدارة العمليات المتعلقة بالمشاكل داخل الدورة
     *
     * This includes:
     * - Adding new problems to a course – إضافة مشاكل جديدة إلى دورة
     * - Updating existing problems – تعديل المشاكل الحالية
     * - Deleting problems from disk and project – حذف المشاكل من القرص وملف المشروع
     */
    class clsProblemActions {
    public:
        /**
         * Add a new problem to the given course – إضافة مشكلة جديدة إلى الدورة المحددة
         *
         * Creates the problem structure on disk and registers it – ينشئ هيكل المشكلة على القرص ويسجّلها
         *
         * @param Course reference to the course where the problem will be added – مرجع للدورة التي ستُضاف إليها المشكلة
         * @return true if the problem was added successfully – يرجع true إذا تمت إضافة المشكلة بنجاح
         */
        static bool AddNewProblem(nsCourseData::sCourseData& Course);

        /**
         * Update an existing problem in the course – تعديل مشكلة موجودة داخل الدورة
         *
         * Applies user-selected changes and updates disk/project files – ينفّذ التعديلات ويحدّث ملفات القرص والمشروع
         *
         * @param Course reference to the course containing the problem – مرجع للدورة التي تحتوي على المشكلة
         * @param selectedProblem reference to the problem to update – مرجع للمشكلة المطلوب تعديلها
         * @return true if the update was successful – يرجع true إذا تم التعديل بنجاح
         */
        static bool UpdateProblem(nsCourseData::sCourseData& Course, nsProblemData::sProblemData& selectedProblem);

        /**
         * Delete a problem from the course – حذف مشكلة من الدورة
         *
         * Confirms deletion, removes problem from disk and project – يؤكد الحذف ويزيل المشكلة من القرص والمشروع
         *
         * @param Course reference to the course containing the problem – مرجع للدورة التي تحتوي على المشكلة
         * @param selectedProblem reference to the problem to delete – مرجع للمشكلة المطلوب حذفها
         * @return true if the deletion was successful – يرجع true إذا تم الحذف بنجاح
         */
        static bool DeleteProblem(const nsCourseData::sCourseData& Course, const nsProblemData::sProblemData& selectedProblem);
    };

}
