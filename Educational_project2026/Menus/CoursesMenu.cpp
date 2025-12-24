#include "CoursesMenu.hpp"
#include <iostream>
#include "../UIHelpers.hpp"
#include "../Adapters/Repositories/CourseRepositoryAdapter.hpp" // ⬅️ جديد
#include "../Adapters/Repositories/ProblemRepositoryAdapter.hpp" // ⬅️ جديد
#include "../Views/CoursesView.hpp"
#include "../Actions/CourseActions.hpp"
#include "../App/DefaultCourse.hpp"
#include "../App/AppController.hpp"
#include "ProblemsMenu.hpp"

using namespace std;

namespace nsCoursesMenu {

    clsCoursesMenu::clsCoursesMenu(nsAppState::sAppState& state, std::vector<nsCourseData::sCourseData>& courses)
        : State(state), AllCourses(courses) {
    }

    void clsCoursesMenu::RefreshCourses() {
        nsAdapters::clsCourseRepositoryAdapter courseRepo;
        AllCourses = courseRepo.LoadAllCourses();
    }

    void clsCoursesMenu::Run() {
        while (true) {
            RefreshCourses(); // ⬅️ تحديث القائمة أولاً
            ShowCoursesMenu();
            int Opt = UIHelpers::ReadInt("Choose option [1-7]: ", 1, 7);
            PerformOption((enCoursesMenueOptions)Opt);
        }
    }

    void clsCoursesMenu::ShowCoursesMenu() const {
        system("cls");
        std::vector<nsViewModels::sCourseView> views;
        for (const auto& c : AllCourses)
            views.push_back(nsViewModels::sCourseView::FromCourse(c));

        nsCoursesView::clsCoursesView::ListAllCourses(views);

        cout << "========================================\n";
        cout << "\t\tMain Menu Courses\n";
        cout << "========================================\n";
        cout << "\t[1] Select Course.\n";
        cout << "\t[2] Set Default Course.\n";
        cout << "\t[3] Add New Course.\n";
        cout << "\t[4] Update Course.\n";
        cout << "\t[5] Delete Course.\n";
        cout << "\t[6] Show Adapter System Info.\n";
        cout << "\t[7] Exit.\n";
        cout << "========================================\n";
    }

    bool clsCoursesMenu::SelectCourseByCode(int courseCode) {
        auto it = std::find_if(AllCourses.begin(), AllCourses.end(),
            [courseCode](const nsCourseData::sCourseData& course) {
                return course.Code == courseCode;
            });

        if (it != AllCourses.end()) {
            State.selectedCourse = *it;

            // تحميل المشاكل باستخدام النظام الجديد
            nsAdapters::clsProblemRepositoryAdapter problemRepo;
            State.selectedCourse.Problems = problemRepo.LoadProblemsForCourse(State.selectedCourse.ID);

            std::cout << "✅ Course selected using NEW system: " << State.selectedCourse.Name << "\n";
            return true;
        }

        std::cout << "❌ Course not found with code: " << courseCode << "\n";
        return false;
    }

    void clsCoursesMenu::PerformOption(enCoursesMenueOptions opt) {
        nsAdapters::clsCourseRepositoryAdapter courseRepo;
        nsDefaultCourse::clsDefaultCourse defaultCourse;
        nsProblemsMenu::clsProblemsMenu problemsMenu(State);

        switch (opt) {
        case eSelectCourse:
            if (SelectCourseByCode(ReadCourseCode())) {
                problemsMenu.Run();
            }
            else {
                UIHelpers::Pause();
            }
            break;

        case eSetDefaultCourse: {
            int currentDefault = defaultCourse.Load();
            if (currentDefault > 0) {
                std::cout << "Current default course code: " << currentDefault << "\n";
                std::cout << "[1] Change default course\n";
                std::cout << "[2] Remove default course\n";
                int choice = UIHelpers::ReadInt("Choose option [1-2]: ", 1, 2);
                if (choice == 1) {
                    int newCode = ReadCourseCode();
                    defaultCourse.Save(newCode);
                    std::cout << "✅ Default course updated using NEW system\n";
                }
                else {
                    defaultCourse.Clear();
                    std::cout << "✅ Default course removed using NEW system\n";
                }
            }
            else {
                int newCode = ReadCourseCode();
                defaultCourse.Save(newCode);
                std::cout << "✅ Default course set using NEW system\n";
            }
            UIHelpers::Pause();
            nsAppController::clsAppController::StartApp();
            break;
        }

        case eAddCourse:
            ShowAddNewCourseMenu();
            UIHelpers::Pause();
            Run();
            break;

        case eUpdateCourse:
            if (SelectCourseByCode(ReadCourseCode())) {
                ShowUpdateCourseMenu(State.selectedCourse);
            }
            UIHelpers::Pause();
            Run();
            break;

        case eDeleteCourse:
            if (SelectCourseByCode(ReadCourseCode())) {
                ShowDeleteCourseMenu(State.selectedCourse);
            }
            UIHelpers::Pause();
            Run();
            break;

        case eShowAdapterInfo:
            ShowAdapterInfo();
            break;

        case eExit:
            system("cls");
            std::exit(0);
        }
    }

    void clsCoursesMenu::ShowAddNewCourseMenu() {
        system("cls");
        cout << "========================================\n";
        cout << "\t\tAdd New Course Menu\n";
        cout << "========================================\n";
        nsCourseActions::clsCourseActions::AddNewCourse(AllCourses);
    }

    void clsCoursesMenu::ShowUpdateCourseMenu(nsCourseData::sCourseData selectedCourse) {
        nsCoursesView::clsCoursesView::ShowCourseInfo(selectedCourse);
        cout << "========================================\n";
        cout << "\t\tUpdate Course Menu\n";
        cout << "========================================\n";
        nsCourseActions::clsCourseActions::UpdateCourse(selectedCourse, AllCourses);
    }

    void clsCoursesMenu::ShowDeleteCourseMenu(nsCourseData::sCourseData selectedCourse) {
        nsCoursesView::clsCoursesView::ShowCourseInfo(selectedCourse);
        cout << "========================================\n";
        cout << "\t\tDelete Course Menu\n";
        cout << "========================================\n";
        nsCourseActions::clsCourseActions::DeleteCourse(selectedCourse, AllCourses);
    }

    int clsCoursesMenu::ReadCourseCode() const {
        return UIHelpers::ReadInt("Enter Course number: ", 1, static_cast<int>(AllCourses.size()));
    }

    void clsCoursesMenu::ShowAdapterInfo() const {
        system("cls");
        std::cout << "========================================\n";
        std::cout << "\t\tAdapter System Info\n";
        std::cout << "\t\tمعلومات نظام المحولات\n";
        std::cout << "========================================\n";

        nsAdapters::clsCourseRepositoryAdapter courseRepo;
        nsAdapters::clsProblemRepositoryAdapter problemRepo;

        auto courses = courseRepo.LoadAllCourses();
        std::cout << "Total courses using NEW system: " << courses.size() << "\n";
        std::cout << "إجمالي الدورات باستخدام النظام الجديد: " << courses.size() << "\n";

        int totalProblems = 0;
        for (const auto& course : courses) {
            auto problems = problemRepo.LoadProblemsForCourse(course.ID);
            totalProblems += problems.size();
            std::cout << "- " << course.Name << " (" << problems.size() << " problems)\n";
        }

        std::cout << "Total problems: " << totalProblems << "\n";
        std::cout << "إجمالي المشاكل: " << totalProblems << "\n";
        std::cout << "========================================\n";
        UIHelpers::Pause();
    }

}