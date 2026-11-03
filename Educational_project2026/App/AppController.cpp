#include "pch.h"
#include "AppController.hpp"
#include "../Menus/CoursesMenu.hpp"
#include "../Views/CoursesView.hpp"
#include "DefaultCourse.hpp"
#include "../Menus/ProblemsMenu.hpp"
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include <ctime>
#include "../UIHelpers.hpp"
// #include <algorithm>  // مكرر: موجود أصلاً بـ pch.h

namespace nsAppController {

    clsAppController::clsAppController(nsAppState::sAppState& state)
        : State(state) {
        InitializeAdapters();
        LogApplicationStart();
        /*CreateCourse("Default Course", 
                     "This is a default course created by the new system.",
			"Full description of the default course created by the new system.");*/
    }

    void clsAppController::InitializeAdapters() {
        // Initialize new adapters only - تهيئة المحولات الجديدة فقط
        FileManager = std::make_unique<nsAdapters::clsFileManagerAdapter>();
        CourseRepository = std::make_unique<nsAdapters::clsCourseRepositoryAdapter>();
        ProblemRepository = std::make_unique<nsAdapters::clsProblemRepositoryAdapter>();

        std::cout << "========================================\n";
        std::cout << "✅ All adapters initialized successfully\n";
        std::cout << "✅ تم تهيئة جميع المحولات بنجاح\n";
        std::cout << "========================================\n";
    }

    void clsAppController::LogApplicationStart() {
        std::string logContent = "========================================\n";
        logContent += "Application started with NEW adapters only\n";
        logContent += "التطبيق بدأ باستخدام المحولات الجديدة فقط\n";
        logContent += "Timestamp: " + std::to_string(time(nullptr)) + "\n";
        logContent += "========================================\n";

        if (!FileManager->FileExists("app_log.txt")) {
            FileManager->WriteFile("app_log.txt", logContent);
        }
        else {
            FileManager->AppendToFile("app_log.txt", logContent);
        }

        //FileManager->WriteFile("app_log.txt", logContent);
        std::cout << "✅ Application start logged using NEW adapter\n";
        std::cout << "✅ تم تسجيل بدء التطبيق باستخدام النظام الجديد\n";
    }

    std::vector<nsCourseData::sCourseData> clsAppController::LoadCourses() {
        // Use new repository only - استخدام المستودع الجديد فقط
        return CourseRepository->LoadAllCourses();
    }

    std::vector<nsProblemData::sProblemData> clsAppController::LoadProblemsForCourse(int courseId) {
        // Use new repository only - استخدام المستودع الجديد فقط
        return ProblemRepository->LoadProblemsForCourse(courseId);
    }

    bool clsAppController::SelectCourseByCode(int courseCode) {
        auto courses = LoadCourses();

        // Find course by code - البحث عن الدورة بالرمز
        auto it = std::find_if(courses.begin(), courses.end(),
            [courseCode](const nsCourseData::sCourseData& course) {
                return course.Code == courseCode;
            });

        if (it != courses.end()) {
            State.selectedCourse = *it;

            // Load problems for selected course using new system - تحميل مشاكل الدورة المحددة باستخدام النظام الجديد
            State.selectedCourse.Problems = LoadProblemsForCourse(State.selectedCourse.ID);

            std::cout << "✅ Course selected using NEW system: " << State.selectedCourse.Name << "\n";
            std::cout << "✅ تم اختيار الدورة باستخدام النظام الجديد: " << State.selectedCourse.Name << "\n";
            return true;
        }

        std::cout << "❌ Course not found with code: " << courseCode << "\n";
        std::cout << "❌ لم يتم العثور على دورة بالرمز: " << courseCode << "\n";
        return false;
    }

    void clsAppController::Run() {
        FileManager->AppendToFile("app_log.txt", "Run method started with NEW repositories - بدأت طريقة التشغيل بالمستودعات الجديدة\n");

        // Use new system only - استخدام النظام الجديد فقط
        auto courses = LoadCourses();

        std::cout << "========================================\n";
        std::cout << "=== NEW Repository System Status ===\n";
        std::cout << "Courses loaded: " << courses.size() << "\n";
        std::cout << "=== حالة نظام المستودعات الجديد ===\n";
        std::cout << "عدد الدورات المحملة: " << courses.size() << "\n";
        std::cout << "========================================\n";

        // Log using new system - التسجيل باستخدام النظام الجديد
        std::string logMsg = "Run method started with NEW repositories - بدأت طريقة التشغيل بالمستودعات الجديدة\n";
        logMsg += "\nCourses loaded using NEW system: " + std::to_string(courses.size()) + "\n";
        logMsg += "========================================\n";
        FileManager->AppendToFile("app_log.txt", logMsg);

        nsDefaultCourse::clsDefaultCourse defaultCourse;
        int DefaultCourseCode = defaultCourse.Load();

        // Use new system for verification - استخدام النظام الجديد للتحقق
        if (DefaultCourseCode != -1 &&
            DefaultCourseCode <= static_cast<int>(courses.size()) &&
            DefaultCourseCode > 0) {

            if (SelectCourseByCode(DefaultCourseCode)) {
                nsCoursesView::clsCoursesView::ShowCourseInfo(State.selectedCourse);
                nsProblemsMenu::clsProblemsMenu problemsMenu(State);
                problemsMenu.Run();
            }
            else {
                std::cout << "❌ Default course not found in NEW system\n";
                std::cout << "❌ الدورة الافتراضية غير موجودة في النظام الجديد\n";
                UIHelpers::Pause();

                // Fallback to courses menu - العودة لقائمة الدورات
                nsCoursesMenu::clsCoursesMenu menu(State, const_cast<std::vector<nsCourseData::sCourseData>&>(courses));
                menu.Run();
            }
        }
        else {
            // Use new system in menu - استخدام النظام الجديد في القائمة
            nsCoursesMenu::clsCoursesMenu menu(State, const_cast<std::vector<nsCourseData::sCourseData>&>(courses));
            menu.Run();
        }

        FileManager->AppendToFile("app_log.txt", "\nRun method completed:Run method completed with NEW repositories - اكتملت طريقة التشغيل بالمستودعات الجديدة\n");
    }

    bool clsAppController::CreateCourse(const std::string& name, const std::string& description, const std::string& fullDescription) {
        nsCourseData::sCourseData newCourse;
        newCourse.Name = name;
        newCourse.Description = description;
        newCourse.FullDescription = fullDescription;

        // Get next available ID using new system - الحصول على المعرف المتاح التالي باستخدام النظام الجديد
        auto existingCourses = CourseRepository->LoadAllCourses();
        int nextId = 1;
        for (const auto& course : existingCourses) {
            if (course.ID >= nextId) nextId = course.ID + 1;
        }
        newCourse.ID = nextId;

        bool success = CourseRepository->SaveCourse(newCourse);

        // Log using new system - التسجيل باستخدام النظام الجديد
        std::string logMsg = "\nCreate course using NEW system:Create course using NEW system - Name: " + name +
            ", Success: " + (success ? "Yes" : "No") + "\n";
        FileManager->AppendToFile("app_log.txt", logMsg);

        if (success) {
            std::cout << "✅ Course created successfully using NEW system\n";
            std::cout << "✅ تم إنشاء الدورة بنجاح باستخدام النظام الجديد\n";
        }
        else {
            std::cout << "❌ Failed to create course using NEW system\n";
            std::cout << "❌ فشل إنشاء الدورة باستخدام النظام الجديد\n";
        }

        return success;
    }

    int clsAppController::GetCoursesCount() const {
        auto courses = CourseRepository->LoadAllCourses();
        return static_cast<int>(courses.size());
    }

    void clsAppController::StartApp() {
        //srand((unsigned)time(NULL));

        nsAppState::sAppState state;
        clsAppController controller(state);  // ✅ No CourseManager needed anymore - لا حاجة لـ CourseManager بعد الآن
        controller.Run();

        UIHelpers::Pause();
    }

}