//#pragma once
//#include <string>
//#include <vector>
//#include <functional>
//#include "../App/AppState.hpp"
//#include "../Models/ProblemData.hpp"
//#include "../Models/CourseData.hpp"
//
//namespace nsProblemManager {
//
//    // Class responsible for managing problems within a specific course – كلاس مسؤول عن إدارة المشاكل داخل دورة معينة
//    class clsProblemManager {
//    private:
//        nsCourseData::sCourseData& Course; // Reference to the course being managed – مرجع إلى الدورة التي يتم إدارتها
//
//    public:
//        /**
//         * Constructor to bind the manager to a specific course – المُنشئ لربط المدير بدورة معينة
//         *
//         * @param course reference to the course data – مرجع إلى بيانات الدورة
//         */
//        clsProblemManager(nsCourseData::sCourseData& course);
//
//        /**
//         * Load all problems from the specified folder – تحميل جميع المشاكل من المجلد المحدد
//         *
//         * @param problemsFolder path to the problems folder – مسار مجلد المشاكل
//         * @return list of loaded problems – قائمة بالمشاكل المحمّلة
//         */
//        std::vector<nsProblemData::sProblemData> LoadProblemsForCourse(const std::string& problemsFolder) const;
//
//        /**
//         * Register a problem's execution function – تسجيل دالة تنفيذ المشكلة
//         *
//         * @param courseId ID of the course – معرف الدورة
//         * @param problemId ID of the problem – معرف المشكلة
//         * @param fnName name of the function – اسم الدالة
//         * @param fn function to execute – الدالة المطلوب تنفيذها
//         */
//        void RegisterProblem(int courseId, int problemId, const std::string& fnName, const std::function<void()>& fn) const;
//
//        ///**
//        // * Create a new problem on disk – إنشاء مشكلة جديدة على القرص
//        // *
//        // * @param courseID ID of the course – معرف الدورة
//        // * @param Problem problem data to create – بيانات المشكلة المطلوب إنشاؤها
//        // * @param problemIndex index of the problem – رقم المشكلة داخل الدورة
//        // * @param idWidth number of digits used to format IDs – عدد الخانات لتنسيق المعرفات
//        // * @return true if creation was successful – يرجع true إذا تم الإنشاء بنجاح
//        // */
//        //bool CreateProblemOnDisk(int courseID, const nsProblemData::sProblemData& Problem, int problemIndex, int idWidth = 3) const;
//
//        ///**
//        // * Modify an existing problem on disk – تعديل مشكلة موجودة على القرص
//        // *
//        // * @param courseID ID of the course – معرف الدورة
//        // * @param problemIndex index of the problem – رقم المشكلة داخل الدورة
//        // * @param updatedProblem updated problem data – بيانات المشكلة المعدّلة
//        // * @param idWidth number of digits used to format IDs – عدد الخانات لتنسيق المعرفات
//        // * @return true if modification was successful – يرجع true إذا تم التعديل بنجاح
//        // */
//        //bool ModifyProblemOnDisk(int courseID, int problemIndex, const nsProblemData::sProblemData& updatedProblem, int idWidth = 3) const;
//
//        ///**
//        // * Delete a problem and remove its files from the project – حذف مشكلة وإزالة ملفاتها من المشروع
//        // *
//        // * @param courseID ID of the course – معرف الدورة
//        // * @param problemIndex index of the problem – رقم المشكلة داخل الدورة
//        // * @param idWidth number of digits used to format IDs – عدد الخانات لتنسيق المعرفات
//        // * @param vcxprojPath path to the .vcxproj file – مسار ملف المشروع
//        // * @return true if deletion was successful – يرجع true إذا تم الحذف بنجاح
//        // */
//        //bool DeleteProblemFromDiskAndProject(int courseID, int problemIndex, int idWidth, const std::string& vcxprojPath) const;
//
//        /**
//         * Select a problem by its assigned code – اختيار مشكلة بناءً على رمزها
//         *
//         * @param ProblemCode the code assigned to the problem – الرمز المخصص للمشكلة
//         * @return the matching problem or empty if not found – المشكلة المطابقة أو فارغة إن لم تُوجد
//         */
//        //nsProblemData::sProblemData SelectProblemByCode(int ProblemCode) const;
//
//        /**
//         * Find the next available problem ID – إيجاد أول معرف مشكلة غير مستخدم
//         *
//         * @return next safe problem ID – المعرف التالي المتاح للمشكلة
//         */
//        //int GetNextProblemIDSafe() const;
//
//        /**
//         * Get the number of problems in the course – الحصول على عدد المشاكل داخل الدورة
//         *
//         * @return number of problems – عدد المشاكل
//         */
//        int NumberOfProblems() const;
//
//        // These functions do not depend on Course, so they are static – هذه الدوال لا تعتمد على الدورة، لذا جعلناها ثابتة
//
//        /**
//         * Run a problem using its full namespace – تشغيل مشكلة باستخدام namespace الكامل
//         *
//         * @param ns full namespace signature – التوقيع الكامل لـ namespace
//         */
//        static void RunProblemByNamespace(const std::string& ns);
//
//        /**
//         * Run a problem using course ID and problem ID – تشغيل مشكلة باستخدام معرف الدورة ومعرف المشكلة
//         *
//         * @param courseId ID of the course – معرف الدورة
//         * @param problemId ID of the problem – معرف المشكلة
//         */
//        static void RunProblemById(int courseId, int problemId);
//    };
//
//}
