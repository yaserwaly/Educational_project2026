#pragma once
#include <string>

namespace nsProblemRemover {

    // Class responsible for deleting a problem and cleaning up its project references – كلاس مسؤول عن حذف مشكلة وتنظيف إشاراتها من المشروع
    class clsProblemRemover {
    public:
        /**
         * Delete problem files and metadata from disk and remove them from the .vcxproj – حذف ملفات المشكلة وبياناتها من القرص ومن ملف المشروع
         *
         * @param courseID ID of the course containing the problem – معرف الدورة التي تحتوي على المشكلة
         * @param problemIndex index of the problem within the course – رقم المشكلة داخل الدورة
         * @param idWidth number of digits used to format IDs – عدد الخانات المستخدمة لتنسيق المعرفات
         * @param vcxprojPath path to the .vcxproj file to update – مسار ملف المشروع المطلوب تحديثه
         * @return true if deletion and cleanup were successful – يرجع true إذا تم الحذف والتنظيف بنجاح
         */
        bool DeleteProblemStructureFromDiskAndProject(int courseID, int problemIndex, int idWidth, const std::string& vcxprojPath) const;
    };

}
