#pragma once
#include "../App/AppState.hpp"

namespace nsProblemsMenu {

    // Class responsible for displaying and handling the problems menu – كلاس مسؤول عن عرض ومعالجة قائمة المشاكل
    class clsProblemsMenu {
    private:
        nsAppState::sAppState& State; // Reference to application state – مرجع إلى حالة التطبيق

        // Menu options enumeration – تعداد خيارات القائمة
        enum enProblemsMenueOptions {
            eSelectProblem = 1,     // اختيار مشكلة
            eSetDefaultProblem = 2, // تعيين مشكلة افتراضية
            eAddProblem = 3,        // إضافة مشكلة جديدة
            eUpdateProblem = 4,     // تعديل مشكلة
            eDeleteProblem = 5,     // حذف مشكلة
            eCoursesMenu = 6,       // العودة لقائمة الدورات
            eExit = 7               // خروج
        };

        /**
         * Display the main problems menu – عرض القائمة الرئيسية للمشاكل
         */
        void ShowProblemsMenu() const;

        /**
         * Perform action based on selected option – تنفيذ الإجراء بناءً على الخيار المحدد
         *
         * @param opt selected menu option – الخيار المحدد من القائمة
         */
        void PerformOption(enProblemsMenueOptions opt);

        /**
         * Show menu for adding a new problem – عرض قائمة إضافة مشكلة جديدة
         */
        void ShowAddNewProblemMenu();

        /**
         * Show menu for updating a selected problem – عرض قائمة تعديل مشكلة محددة
         *
         * @param selectedProblem the problem to update – المشكلة المطلوب تعديلها
         */
        void ShowUpdateProblemMenu(nsProblemData::sProblemData& selectedProblem);

        /**
         * Show menu for deleting a selected problem – عرض قائمة حذف مشكلة محددة
         *
         * @param selectedProblem the problem to delete – المشكلة المطلوب حذفها
         */
        void ShowDeleteProblemMenu(const nsProblemData::sProblemData& selectedProblem);

        /**
         * Read problem code from user input – قراءة رمز المشكلة من المستخدم
         *
         * @return selected problem code – رمز المشكلة المحددة
         */
        int ReadProblemCode(const std::vector<nsProblemData::sProblemData>& problems) const;  // ⬅️ تعد

        /**
         * Reload course and rerun problems menu – إعادة تحميل الدورة وتشغيل القائمة من جديد
         */
        void RefreshProblemsMenu();

    public:
        /**
         * Constructor to initialize the problems menu – المُنشئ لتهيئة قائمة المشاكل
         *
         * @param state reference to application state – مرجع إلى حالة التطبيق
         */
        clsProblemsMenu(nsAppState::sAppState& state);

        /**
         * Run the main problems menu loop – تشغيل حلقة القائمة الرئيسية للمشاكل
         */
        void Run();
    };

}
