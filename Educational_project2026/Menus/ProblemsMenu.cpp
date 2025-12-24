#include "ProblemsMenu.hpp"
#include <iostream>
#include "../Adapters/Repositories/ProblemRepositoryAdapter.hpp"  // ⬅️ جديد
#include "../Adapters/Repositories/CourseRepositoryAdapter.hpp"   // ⬅️ جديد
#include "../Views/ProblemsView.hpp"
#include "../Actions/ProblemActions.hpp"
#include "../App/DefaultProblem.hpp"
#include "../Views/CoursesView.hpp"
#include "../UIHelpers.hpp"
#include "../Registry/FileHelpers.hpp"
#include "../Menus/CoursesMenu.hpp"
#include "../App/AppController.hpp"
#include "../Registry/DispatcherRunner.hpp"  // ⬅️ ضروري لتشغيل المشاكل

using namespace std;

namespace nsProblemsMenu {

    clsProblemsMenu::clsProblemsMenu(nsAppState::sAppState& state)
        : State(state) {
        // لا حاجة لـ ProblemManager بعد الآن
    }

    void clsProblemsMenu::Run() {
        nsAdapters::clsProblemRepositoryAdapter problemRepo;  // ⬅️ جديد
        nsDefaultProblem::clsDefaultProblem defaultProblem(State.selectedCourse.ID);

        // استخدام النظام الجديد
        auto problems = problemRepo.LoadProblemsForCourse(State.selectedCourse.ID);  // ⬅️ جديد
        int defaultCode = defaultProblem.Load();

        if (defaultCode != -1 &&
            defaultCode <= static_cast<int>(problems.size()) &&  // ⬅️ تعديل
            defaultCode > 0) {

            // البحث عن المشكلة بالرمز
            auto it = std::find_if(problems.begin(), problems.end(),
                [defaultCode](const nsProblemData::sProblemData& problem) {
                    return problem.Code == defaultCode;
                });

            if (it != problems.end()) {
                State.selectedProblem = *it;
                nsProblemsView::clsProblemsView::ShowProblemInfo(State.selectedProblem);

                if (UIHelpers::ConfirmYes("Do you Run Problem?")) {
                    system("cls");
                    nsDispatcherRunner::clsDispatcherRunner::Run(State.selectedProblem.Namespace);  // ⬅️ استخدام مباشر
                    UIHelpers::Pause();
                    Run();
                    return;
                }
            }
        }

        // الحلقة الرئيسية
        while (true) {
            system("cls");
            nsCoursesView::clsCoursesView::ShowCourseInfo(State.selectedCourse);
            ShowProblemsMenu();
            int Opt = UIHelpers::ReadInt("Choose option [1-7]: ", 1, 7);
            PerformOption((enProblemsMenueOptions)Opt);
        }
    }

    void clsProblemsMenu::ShowProblemsMenu() const {
        nsAdapters::clsProblemRepositoryAdapter problemRepo;  // ⬅️ جديد
        auto problems = problemRepo.LoadProblemsForCourse(State.selectedCourse.ID);  // ⬅️ جديد

        std::vector<nsViewModels::sProblemView> views;
        for (const auto& p : problems)  // ⬅️ استخدام problems الجديدة
            views.push_back(nsViewModels::sProblemView::FromProblem(p));

        nsProblemsView::clsProblemsView::ListProblems(views);

        std::cout << "========================================\n";
        std::cout << "\t\tMain Menu Problems\n";
        std::cout << "========================================\n";
        std::cout << "\t[1] Select Problem.\n";
        std::cout << "\t[2] Set Default Problem.\n";
        std::cout << "\t[3] Add New Problem.\n";
        std::cout << "\t[4] Update Problem.\n";
        std::cout << "\t[5] Delete Problem.\n";
        std::cout << "\t[6] Return to Courses Menu.\n";
        std::cout << "\t[7] Exit.\n";
        std::cout << "========================================\n";
    }

    void clsProblemsMenu::PerformOption(enProblemsMenueOptions opt) {
        nsAdapters::clsProblemRepositoryAdapter problemRepo;  // ⬅️ جديد
        nsDefaultProblem::clsDefaultProblem defaultProblem(State.selectedCourse.ID);
        nsAdapters::clsCourseRepositoryAdapter courseRepo;  // ⬅️ جديد

        auto problems = problemRepo.LoadProblemsForCourse(State.selectedCourse.ID);  // ⬅️ جديد

        switch (opt) {
        case eSelectProblem: {
            int problemCode = ReadProblemCode(problems);  // ⬅️ تعديل
            auto it = std::find_if(problems.begin(), problems.end(),
                [problemCode](const nsProblemData::sProblemData& problem) {
                    return problem.Code == problemCode;
                });

            if (it != problems.end()) {
                State.selectedProblem = *it;
                nsProblemsView::clsProblemsView::ShowProblemInfo(State.selectedProblem);
                if (UIHelpers::ConfirmYes("Do you Run Problem?")) {
                    system("cls");
                    nsDispatcherRunner::clsDispatcherRunner::Run(State.selectedProblem.Namespace);
                }
            }
            UIHelpers::Pause();
            Run();
            break;
        }

        case eSetDefaultProblem: {
            int currentDefault = defaultProblem.Load();
            if (currentDefault > 0) {
                std::cout << "Current default problem code: " << currentDefault << "\n";
                std::cout << "[1] Change default problem\n";
                std::cout << "[2] Remove default problem\n";
                int choice = UIHelpers::ReadInt("Choose option [1-2]: ", 1, 2);
                if (choice == 1) {
                    int newCode = ReadProblemCode(problems);  // ⬅️ تعديل
                    defaultProblem.Save(newCode);
                }
                else {
                    defaultProblem.Clear();
                }
            }
            else {
                int newCode = ReadProblemCode(problems);  // ⬅️ تعديل
                defaultProblem.Save(newCode);
            }
            UIHelpers::Pause();
            nsAppController::clsAppController::StartApp();
            break;
        }

        case eAddProblem:
            ShowAddNewProblemMenu();
            UIHelpers::Pause();
            RefreshProblemsMenu();
            break;

        case eUpdateProblem: {
            int problemCode = ReadProblemCode(problems);  // ⬅️ تعديل
            auto it = std::find_if(problems.begin(), problems.end(),
                [problemCode](const nsProblemData::sProblemData& problem) {
                    return problem.Code == problemCode;
                });

            if (it != problems.end()) {
                State.selectedProblem = *it;
                ShowUpdateProblemMenu(State.selectedProblem);
            }
            UIHelpers::Pause();
            RefreshProblemsMenu();
            break;
        }

        case eDeleteProblem: {
            int problemCode = ReadProblemCode(problems);  // ⬅️ تعديل
            auto it = std::find_if(problems.begin(), problems.end(),
                [problemCode](const nsProblemData::sProblemData& problem) {
                    return problem.Code == problemCode;
                });

            if (it != problems.end()) {
                State.selectedProblem = *it;
                ShowDeleteProblemMenu(State.selectedProblem);
            }
            UIHelpers::Pause();
            RefreshProblemsMenu();
            break;
        }

        case eCoursesMenu: {
            auto courses = courseRepo.LoadAllCourses();  // ⬅️ جديد
            auto it = std::find_if(courses.begin(), courses.end(),
                [this](const nsCourseData::sCourseData& course) {
                    return course.Code == State.selectedCourse.Code;
                });

            if (it != courses.end()) {
                State.selectedCourse = *it;
            }
            UIHelpers::Pause();
            nsCoursesMenu::clsCoursesMenu menu(State, const_cast<std::vector<nsCourseData::sCourseData>&>(courses));
            menu.Run();
            break;
        }

        case eExit:
            system("cls");
            std::exit(0);
        }
    }

    // الدوال المساعدة تفضل كما هي مع التعديلات البسيطة
    void clsProblemsMenu::ShowAddNewProblemMenu() {
        system("cls");
        std::cout << "========================================\n";
        std::cout << "\t\tAdd New Problem Menu\n";
        std::cout << "========================================\n";
        nsProblemActions::clsProblemActions::AddNewProblem(State.selectedCourse);
    }

    void clsProblemsMenu::ShowUpdateProblemMenu(nsProblemData::sProblemData& selectedProblem) {
        nsProblemsView::clsProblemsView::ShowProblemInfo(selectedProblem);
        std::cout << "========================================\n";
        std::cout << "\t\tUpdate Problem Menu\n";
        std::cout << "========================================\n";
        nsProblemActions::clsProblemActions::UpdateProblem(State.selectedCourse, selectedProblem);
    }

    void clsProblemsMenu::ShowDeleteProblemMenu(const nsProblemData::sProblemData& selectedProblem) {
        nsProblemsView::clsProblemsView::ShowProblemInfo(selectedProblem);
        std::cout << "========================================\n";
        std::cout << "\t\tDelete Problem Menu\n";
        std::cout << "========================================\n";
        nsProblemActions::clsProblemActions::DeleteProblem(State.selectedCourse, selectedProblem);
    }

    int clsProblemsMenu::ReadProblemCode(const std::vector<nsProblemData::sProblemData>& problems) const {
        return UIHelpers::ReadInt("Enter Problem number: ", 1, static_cast<int>(problems.size()));
    }

    void clsProblemsMenu::RefreshProblemsMenu() {
        nsAdapters::clsCourseRepositoryAdapter courseRepo;
        auto courses = courseRepo.LoadAllCourses();

        auto it = std::find_if(courses.begin(), courses.end(),
            [this](const nsCourseData::sCourseData& course) {
                return course.Code == State.selectedCourse.Code;
            });

        if (it != courses.end()) {
            State.selectedCourse = *it;
        }
        Run();
    }

}