#pragma once

#include "AppState.hpp"
#include "../Adapters/IO/FileManagerAdapter.hpp"
#include "../Adapters/Repositories/CourseRepositoryAdapter.hpp"
#include "../Adapters/Repositories/ProblemRepositoryAdapter.hpp"
#include <memory>

namespace nsAppController {

    /**
     * Main controller for managing application flow - using new adapters only
     * المتحكم الرئيسي في تدفق التطبيق - باستخدام المحولات الجديدة فقط
     */
    class clsAppController {
    public:
        /**
         * Constructor to initialize controller with app state
         * مُنشئ لتهيئة المتحكم بحالة التطبيق
         * @param state reference to application state - مرجع لحالة التطبيق
         */
        clsAppController(nsAppState::sAppState& state);

        /**
         * Run the main application logic using new adapters only
         * تنفيذ منطق التطبيق الأساسي باستخدام المحولات الجديدة فقط
         */
        void Run();

        /**
         * Static entry point to start the application
         * نقطة الدخول الرئيسية لتشغيل التطبيق
         */
        static void StartApp();

        /**
         * Create course using new repository adapter
         * إنشاء دورة باستخدام محول المستودع الجديد
         * @param name course name - اسم الدورة
         * @param description course description - وصف الدورة
         * @param fullDescription course full description - الوصف الكامل للدورة
         * @return true if course was created successfully - يرجع true إذا تم إنشاء الدورة بنجاح
         */
        bool CreateCourse(const std::string& name, const std::string& description, const std::string& fullDescription);

        /**
         * Get courses count using new repository adapter
         * الحصول على عدد الدورات باستخدام محول المستودع الجديد
         * @return number of courses - عدد الدورات
         */
        int GetCoursesCount() const;

    private:
        nsAppState::sAppState& State; ///< Reference to the current application state - مرجع لحالة التطبيق الحالية

        // New adapters only - المحولات الجديدة فقط
        std::unique_ptr<nsInterfaces::IFileManager> FileManager;           ///< File management adapter - محول إدارة الملفات
        std::unique_ptr<nsInterfaces::ICourseRepository> CourseRepository; ///< Course data repository adapter - محول مستودع بيانات الدورات
        std::unique_ptr<nsInterfaces::IProblemRepository> ProblemRepository; ///< Problem data repository adapter - محول مستودع بيانات المشاكل

        /**
         * Initialize new adapters
         * تهيئة المحولات الجديدة
         */
        void InitializeAdapters();

        /**
         * Log application start using new file manager
         * تسجيل بدء التطبيق باستخدام مدير الملفات الجديد
         */
        void LogApplicationStart();

        /**
         * Load courses using new repository
         * تحميل الدورات باستخدام المستودع الجديد
         * @return vector of loaded courses - متجه للدورات المحملة
         */
        std::vector<nsCourseData::sCourseData> LoadCourses();

        /**
         * Load problems for specific course using new repository
         * تحميل المشاكل لدورة محددة باستخدام المستودع الجديد
         * @param courseId ID of the course - معرف الدورة
         * @return vector of loaded problems - متجه للمشاكل المحملة
         */
        std::vector<nsProblemData::sProblemData> LoadProblemsForCourse(int courseId);

        /**
         * Select course by code using new system
         * اختيار دورة بالرمز باستخدام النظام الجديد
         * @param courseCode code of the course to select - رمز الدورة المطلوب اختيارها
         * @return true if course was found and selected - يرجع true إذا تم العثور على الدورة واختيارها
         */
        bool SelectCourseByCode(int courseCode);
    };

}