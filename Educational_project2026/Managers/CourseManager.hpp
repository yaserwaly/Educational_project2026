//#pragma once
//#include <vector>
//#include <string>
//#include "../App/AppState.hpp"
//#include "../Models/CourseData.hpp"
//
//namespace nsCourseManager {
//
//    // Class responsible for managing all course operations – كلاس مسؤول عن إدارة جميع عمليات الدورات
//    class clsCourseManager {
//    private:
//        std::string BaseFolder; // Base folder where courses are stored – مجلد الأساس الذي تُخزّن فيه الدورات
//        std::vector<nsCourseData::sCourseData> AllCourses; // Loaded courses – قائمة الدورات المحمّلة
//
//    public:
//        /**
//         * Constructor to initialize course manager with a base folder – المُنشئ لتهيئة مدير الدورات بمجلد الأساس
//         *
//         * @param baseFolder path to the folder containing all courses – مسار المجلد الذي يحتوي على جميع الدورات
//         */
//        clsCourseManager(const std::string& baseFolder = "Courses");
//
//        /**
//         * Load all courses from disk and assign codes – تحميل جميع الدورات من القرص وتعيين رموز لها
//         *
//         * @param startCode starting code to assign to loaded courses – الرمز الابتدائي لتعيين رموز الدورات
//         */
//        //void Load(int startCode = 1);
//
//        /**
//         * Get all loaded courses – الحصول على جميع الدورات المحمّلة
//         *
//         * @return reference to the list of courses – مرجع إلى قائمة الدورات
//         */
//        const std::vector<nsCourseData::sCourseData>& GetCourses() const;
//
//        /**
//         * Find the next available course ID – إيجاد أول معرف دورة غير مستخدم
//         *
//         * @return next safe course ID – المعرف التالي المتاح للدورة
//         */
//        //int GetNextCourseIDSafe() const;
//
//        /**
//         * Get the number of loaded courses – الحصول على عدد الدورات المحمّلة
//         *
//         * @return number of courses – عدد الدورات
//         */
//        int NumberOfCourses() const;
//
//        /**
//         * Select a course by its assigned code – اختيار دورة بناءً على رمزها
//         *
//         * @param State application state to update – حالة التطبيق لتحديث الدورة المحددة
//         * @param CourseCode the code of the course to select – رمز الدورة المطلوب تحديدها
//         */
//        void SelectCourseByCode(nsAppState::sAppState& State, int CourseCode) const;
//
//        ///**
//        // * Create a new course on disk – إنشاء دورة جديدة على القرص
//        // *
//        // * @param course course data to create – بيانات الدورة المطلوب إنشاؤها
//        // * @param idWidth number of digits used to format course ID – عدد الخانات لتنسيق معرف الدورة
//        // * @return true if creation was successful – يرجع true إذا تم الإنشاء بنجاح
//        // */
//        //bool CreateCourseOnDisk(const nsCourseData::sCourseData& course, int idWidth = 2) const;
//
//        ///**
//        // * Modify an existing course on disk – تعديل دورة موجودة على القرص
//        // *
//        // * @param updatedCourse updated course data – بيانات الدورة المعدّلة
//        // * @param idWidth number of digits used to format course ID – عدد الخانات لتنسيق المعرف
//        // * @return true if modification was successful – يرجع true إذا تم التعديل بنجاح
//        // */
//        //bool ModifyCourseOnDisk(const nsCourseData::sCourseData& updatedCourse, int idWidth = 2) const;
//
//        ///**
//        // * Delete a course and remove its files from the project – حذف دورة وإزالة ملفاتها من المشروع
//        // *
//        // * @param courseID ID of the course to delete – معرف الدورة المطلوب حذفها
//        // * @param idWidth number of digits used to format course ID – عدد الخانات لتنسيق المعرف
//        // * @param vcxprojPath path to the .vcxproj file – مسار ملف المشروع
//        // * @return true if deletion was successful – يرجع true إذا تم الحذف بنجاح
//        // */
//        //bool DeleteCourseFromDiskAndProject(int courseID, int idWidth, const std::string& vcxprojPath) const;
//    };
//
//}
