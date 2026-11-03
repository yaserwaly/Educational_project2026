#include "pch.h"
#include "CourseActions.hpp"
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include "../UIHelpers.hpp"
//#include "../Managers/CourseManager.hpp"
#include "../DataInserters/CourseInserter.hpp"
#include "../DataModifiers/CourseModifier.hpp"
#include "../DataRemovers/CourseRemover.hpp"
//#include "../Adapters/IO/FileManagerAdapter.hpp"
#include "../Adapters/Repositories/CourseRepositoryAdapter.hpp"

using namespace std;

namespace nsCourseActions {

    /**
     * Enum for course update menu options – تعداد خيارات تعديل الدورة
     */
    enum enCourseUpdateMenuOptions {
        eNameCourse = 1,
        eDescriptionCourse = 2,
        eFullDescriptionCourse = 3,
        eAllInfoCourse = 4,
        eExitUpdate = 5
    };

    /**
     * Collect new course data from user input – جمع بيانات دورة جديدة من المستخدم
     *
     * @return initialized course object – كائن دورة جاهز
     */
    static nsCourseData::sCourseData NewDataCourse() {
        nsCourseData::sCourseData c{};
        c.Name = UIHelpers::ReadString("Enter Course Name? ");
        c.Description = UIHelpers::ReadString("Enter Description? ");
        c.FullDescription = UIHelpers::ReadString("Enter Full Description? ");

        /*nsCourseManager::clsCourseManager manager;
        manager.Load();*/
        /*c.ID = manager.GetNextCourseIDSafe();*/
        nsAdapters::clsCourseRepositoryAdapter CourseRepo;
        c.ID = CourseRepo.GetNextCourseId();

        return c;
    }

    /**
     * Add a new course and update the list – إضافة دورة جديدة وتحديث القائمة
     *
     * @param AllCourses reference to the full course list – مرجع لقائمة الدورات الكاملة
     * @return true if course was created successfully – يرجع true إذا تم إنشاء الدورة بنجاح
     */
    bool clsCourseActions::AddNewCourse(std::vector<nsCourseData::sCourseData>& AllCourses) {
        nsCourseData::sCourseData c = NewDataCourse();

        nsAdapters::clsCourseRepositoryAdapter CourseRepo;
        if (CourseRepo.SaveCourse(c)) {
            AllCourses = CourseRepo.LoadAllCourses();
            std::cout << "Course created successfully. Name: " << c.Name << "\n";
            return true;
        }

        std::cout << "Failed to create course.\n";
        return false;
    }

    /**
     * Apply selected update option to a course – تنفيذ خيار تعديل معين على دورة
     *
     * @param opt selected update option – الخيار المختار من المستخدم
     * @param Course original course data – بيانات الدورة الأصلية
     * @return updated course data – بيانات الدورة بعد التعديل
     */
    static nsCourseData::sCourseData PerfromCoursesUpdateMenueOption(enCourseUpdateMenuOptions opt, nsCourseData::sCourseData Course) {
        nsCourseData::sCourseData updated{};
        updated.ID = Course.ID;

        switch (opt) {
        case eNameCourse:
            updated.Name = UIHelpers::ReadString("Enter New Course Name? ");
            updated.Description = Course.Description;
            updated.FullDescription = Course.FullDescription;
            break;
        case eDescriptionCourse:
            updated.Name = Course.Name;
            updated.Description = UIHelpers::ReadString("Enter New Description? ");
            updated.FullDescription = Course.FullDescription;
            break;
        case eFullDescriptionCourse:
            updated.Name = Course.Name;
            updated.Description = Course.Description;
            updated.FullDescription = UIHelpers::ReadString("Enter New Full Description? ");
            break;
        case eAllInfoCourse:
            updated.Name = UIHelpers::ReadString("Enter New Course Name? ");
            updated.Description = UIHelpers::ReadString("Enter New Description? ");
            updated.FullDescription = UIHelpers::ReadString("Enter New Full Description? ");
            break;
        case eExitUpdate:
            updated = Course;
            break;
        }

        return updated;
    }

    /**
     * Display the course update menu – عرض قائمة تعديل الدورة
     */
    static void ShowCourseUpdateMenu() {
        cout << "========================================\n";
        cout << "\t\tModify Menu Course\n";
        cout << "========================================\n";
        cout << "\t[1] Modify Name Course.\n";
        cout << "\t[2] Modify Description Course.\n";
        cout << "\t[3] Modify Full Description Course.\n";
        cout << "\t[4] Modify All Info Course.\n";
        cout << "\t[5] Exit.\n";
        cout << "========================================\n";
    }

    /**
     * Handle user selection from update menu – تنفيذ تعديل الدورة حسب اختيار المستخدم
     *
     * @param Course original course data – بيانات الدورة الأصلية
     * @return updated course data – بيانات الدورة بعد التعديل
     */
    static nsCourseData::sCourseData HandleCourseUpdateMenu(nsCourseData::sCourseData Course) {
        ShowCourseUpdateMenu();
        int opt = UIHelpers::ReadInt("Enter Option Menu: ", 1, 5);
        return PerfromCoursesUpdateMenueOption((enCourseUpdateMenuOptions)opt, Course);
    }

    /**
     * Update an existing course and refresh the list – تعديل دورة موجودة وتحديث القائمة
     *
     * @param selectedCourse reference to the course being updated – مرجع للدورة المحددة
     * @param AllCourses reference to the full course list – مرجع لقائمة الدورات الكاملة
     * @return true if update was successful – يرجع true إذا تم التعديل بنجاح
     */
    bool clsCourseActions::UpdateCourse(nsCourseData::sCourseData& selectedCourse, std::vector<nsCourseData::sCourseData>& AllCourses) {
        nsCourseData::sCourseData Updated = HandleCourseUpdateMenu(selectedCourse);

        nsAdapters::clsCourseRepositoryAdapter CourseRepo;
        if (CourseRepo.UpdateCourse(Updated)) {
            AllCourses = CourseRepo.LoadAllCourses();
            std::cout << "Course modified successfully. Name: " << Updated.Name << "\n";
            selectedCourse = Updated;
            return true;
        }

        std::cout << "Failed to modify course.\n";
        return false;
    }

    /**
     * Delete a course after confirmation and refresh list – حذف دورة بعد التأكيد وتحديث القائمة
     *
     * @param selectedCourse the course to delete – الدورة المطلوب حذفها
     * @param AllCourses reference to the full course list – مرجع لقائمة الدورات الكاملة
     * @return true if deletion was successful – يرجع true إذا تم الحذف بنجاح
     */
    bool clsCourseActions::DeleteCourse(const nsCourseData::sCourseData& selectedCourse, std::vector<nsCourseData::sCourseData>& AllCourses) {
        if (!UIHelpers::ConfirmYes("Are you sure you want to DELETE this course and all its problems?")) {
            std::cout << "Deletion cancelled.\n";
            return false;
        }

        nsAdapters::clsCourseRepositoryAdapter courseRepo;
        if (courseRepo.DeleteCourse(selectedCourse.ID)) {
            AllCourses = courseRepo.LoadAllCourses();
            std::cout << "Course deleted successfully. Name: " << selectedCourse.Name << "\n";
            return true;
        }

        AllCourses = courseRepo.LoadAllCourses();
        std::cout << "Failed to delete course.\n";
        return false;
    }

}
