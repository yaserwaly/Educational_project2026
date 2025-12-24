#pragma once
#include <string>
#include "CourseData.hpp"
#include "ProblemData.hpp"

namespace nsViewModels {

    /**
     * View model for displaying course summary in UI – نموذج عرض لتمثيل الدورة في الواجهة
     */
    struct sCourseView {
        int Code;                 // Display code for the course – رمز العرض للدورة
        std::string Name;         // Course name – اسم الدورة
        std::string Description;  // Short description – وصف مختصر

        /**
         * Convert full course data to a simplified view – تحويل بيانات الدورة الكاملة إلى نموذج عرض مبسّط
         *
         * @param c full course data – بيانات الدورة الكاملة
         * @return simplified course view – نموذج العرض المبسّط
         */
        static sCourseView FromCourse(const nsCourseData::sCourseData& c) {
            return { c.Code, c.Name, c.Description };
        }
    };

    /**
     * View model for displaying problem summary in UI – نموذج عرض لتمثيل المشكلة في الواجهة
     */
    struct sProblemView {
        int Code;                 // Display code for the problem – رمز العرض للمشكلة
        std::string Name;         // Problem name – اسم المشكلة
        std::string Description;  // Short description – وصف مختصر

        /**
         * Convert full problem data to a simplified view – تحويل بيانات المشكلة الكاملة إلى نموذج عرض مبسّط
         *
         * @param p full problem data – بيانات المشكلة الكاملة
         * @return simplified problem view – نموذج العرض المبسّط
         */
        static sProblemView FromProblem(const nsProblemData::sProblemData& p) {
            return { p.Code, p.Name, p.Description };
        }
    };

}
