#pragma once
#include <string>
#include <vector>
#include "ProblemData.hpp"

namespace nsCourseData {

    /**
     * Represents a course and its associated metadata – يمثل دورة تدريبية وبياناتها المرتبطة
     */
    struct sCourseData {
        int ID = 0;                          // Unique internal ID – المعرف الداخلي الفريد
        int Code = 0;                        // Display code used in menus – رمز العرض المستخدم في القوائم
        std::string Name;                   // Short name of the course – الاسم المختصر للدورة
        std::string Description;            // Brief description – وصف مختصر
        std::string FullDescription;        // Detailed description – وصف تفصيلي
        std::vector<nsProblemData::sProblemData> Problems; // List of problems in the course – قائمة المشاكل داخل الدورة
    };

}
