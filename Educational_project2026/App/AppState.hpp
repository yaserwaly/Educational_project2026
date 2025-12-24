#pragma once
#include "../Models/CourseData.hpp"
#include <vector>

namespace nsAppState {

    // Struct representing the current application state – بنية تمثل حالة التطبيق الحالية
    struct sAppState {
        /**
         * Current course ID for tracking – رقم الدورة الحالية لأغراض التتبع
         */
        int currentCourseId = 0;

        /**
         * Current problem ID for tracking – رقم المشكلة الحالية لأغراض التتبع
         */
        int currentProblemId = 0;

        /**
         * The currently selected course – الدورة المحددة حاليًا
         */
        nsCourseData::sCourseData selectedCourse;

        /**
         * The currently selected problem – المشكلة المحددة حاليًا
         */
        nsProblemData::sProblemData selectedProblem;

        /**
         * Reset the application state to its initial values – إعادة حالة التطبيق إلى القيم الابتدائية
         */
        void Reset();

        /**
         * Check if a course has been selected – التحقق من اختيار دورة
         * @return true if a course is selected – يرجع true إذا تم اختيار دورة
         */
        bool IsCourseSelected() const;

        /**
         * Check if a problem has been selected – التحقق من اختيار مشكلة
         * @return true if a problem is selected – يرجع true إذا تم اختيار مشكلة
         */
        bool IsProblemSelected() const;

        /**
         * Reload the selected course from the full course list – إعادة تحميل الدورة المختارة من قائمة الدورات
         * @param allCourses list of all available courses – قائمة بجميع الدورات المتاحة
         */
        void ReloadSelectedCourse(const std::vector<nsCourseData::sCourseData>& allCourses);
    };

}
