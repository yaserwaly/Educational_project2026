#pragma once
#include <string>

namespace nsProblemData {

    /**
     * Represents a single problem and its metadata – يمثل مشكلة واحدة وبياناتها الوصفية
     */
    struct sProblemData {
        int ID = 0;                  // Unique internal ID – المعرف الداخلي الفريد
        int Code = 0;                // Display code used in menus – رمز العرض المستخدم في القوائم
        std::string Name;           // Short name of the problem – الاسم المختصر للمشكلة
        std::string Description;    // Brief description – وصف مختصر
        std::string FullDescription;// Detailed description – وصف تفصيلي

        std::string Namespace;      // C++ namespace for execution, e.g. "c02Problem00::c02Problem00" – مساحة الاسم المستخدمة للتنفيذ
        std::string FilePath;       // Relative path to logic file, e.g. "Courses/Course02/Problems/c02Problem00.hpp" – المسار النسبي لملف المنطق
    };

}
