#pragma once
#include "../Models/CourseData.hpp"
#include "../App/AppState.hpp"
#include <vector>

namespace nsCoursesMenu {

    // Class responsible for displaying and handling the main courses menu using new adapters
    // كلاس مسؤول عن عرض ومعالجة القائمة الرئيسية للدورات باستخدام المحولات الجديدة
    class clsCoursesMenu {
    private:
        nsAppState::sAppState& State; // Reference to application state - مرجع إلى حالة التطبيق
        std::vector<nsCourseData::sCourseData>& AllCourses; // Reference to all loaded courses - مرجع إلى جميع الدورات المحمّلة

        // Menu options enumeration - تعداد خيارات القائمة
        enum enCoursesMenueOptions {
            eSelectCourse = 1,       // اختيار دورة
            eSetDefaultCourse = 2,   // تعيين دورة افتراضية
            eAddCourse = 3,          // إضافة دورة جديدة
            eUpdateCourse = 4,       // تعديل دورة
            eDeleteCourse = 5,       // حذف دورة
            eShowAdapterInfo = 6,    // عرض معلومات النظام الجديد
            eExit = 7                // خروج
        };

        /**
         * Display the main courses menu - عرض القائمة الرئيسية للدورات
         */
        void ShowCoursesMenu() const;

        /**
         * Perform action based on selected option - تنفيذ الإجراء بناءً على الخيار المحدد
         * @param opt selected menu option - الخيار المحدد من القائمة
         */
        void PerformOption(enCoursesMenueOptions opt);

        /**
         * Show menu for adding a new course - عرض قائمة إضافة دورة جديدة
         */
        void ShowAddNewCourseMenu();

        /**
         * Show menu for updating a selected course - عرض قائمة تعديل دورة محددة
         * @param selectedCourse the course to update - الدورة المطلوب تعديلها
         */
        void ShowUpdateCourseMenu(nsCourseData::sCourseData selectedCourse);

        /**
         * Show menu for deleting a selected course - عرض قائمة حذف دورة محددة
         * @param selectedCourse the course to delete - الدورة المطلوب حذفها
         */
        void ShowDeleteCourseMenu(nsCourseData::sCourseData selectedCourse);

        /**
         * Read course code from user input - قراءة رمز الدورة من المستخدم
         * @return selected course code - رمز الدورة المحددة
         */
        int ReadCourseCode() const;

        /**
         * Show adapter system information - عرض معلومات نظام المحولات
         */
        void ShowAdapterInfo() const;

        /**
         * Refresh courses list from repository - تحديث قائمة الدورات من المستودع
         */
        void RefreshCourses();

        /**
         * Select course by code using new system - اختيار دورة بالرمز باستخدام النظام الجديد
         * @param courseCode code of the course to select - رمز الدورة المطلوب اختيارها
         * @return true if course was found and selected - يرجع true إذا تم العثور على الدورة واختيارها
         */
        bool SelectCourseByCode(int courseCode);

    public:
        /**
         * Constructor to initialize the courses menu - المُنشئ لتهيئة قائمة الدورات
         * @param state reference to application state - مرجع إلى حالة التطبيق
         * @param courses reference to all loaded courses - مرجع إلى جميع الدورات المحمّلة
         */
        clsCoursesMenu(nsAppState::sAppState& state, std::vector<nsCourseData::sCourseData>& courses);

        /**
         * Run the main courses menu loop - تشغيل حلقة القائمة الرئيسية للدورات
         */
        void Run();
    };

}