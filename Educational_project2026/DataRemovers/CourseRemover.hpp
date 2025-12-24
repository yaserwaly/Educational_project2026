#pragma once
#include <string>

namespace nsCourseRemover {

    // Class responsible for deleting course folder and removing its files from the project – كلاس مسؤول عن حذف مجلد الدورة وإزالة ملفاته من المشروع
    class clsCourseRemover {
    public:
        /**
         * Delete the course folder from disk and remove its logic files from the .vcxproj – حذف مجلد الدورة من القرص وإزالة ملفات المنطق من المشروع
         *
         * @param courseID ID of the course to delete – معرف الدورة المطلوب حذفها
         * @param idWidth number of digits used to format course ID – عدد الخانات المستخدمة لتنسيق معرف الدورة
         * @param vcxprojPath path to the .vcxproj file to update – مسار ملف المشروع المطلوب تحديثه
         * @return true if deletion and update were successful – يرجع true إذا تم الحذف والتحديث بنجاح
         */
        bool DeleteCourseStructureFromDiskAndProject(int courseID, int idWidth, const std::string& vcxprojPath) const;
    };

}
