#include "CoursesView.hpp"
#include <iostream>

namespace nsCoursesView {

    /**
     * Display detailed information about a single course – عرض معلومات تفصيلية عن دورة واحدة
     *
     * @param course the course to display – الدورة المطلوب عرضها
     */
    void clsCoursesView::ShowCourseInfo(const nsCourseData::sCourseData& course) {
        system("cls"); // Clear screen – مسح الشاشة
        std::cout << "========================================\n";
        std::cout << "\t\tCourse Info\n";
        std::cout << "========================================\n";
        std::cout << "Name            : " << course.Name << "\n";             // اسم الدورة
        std::cout << "Description     : " << course.Description << "\n";      // وصف مختصر
        std::cout << "Full Description: " << course.FullDescription << "\n";  // وصف تفصيلي
        std::cout << "========================================\n";
    }

    /**
     * Display a list of all available courses – عرض قائمة بجميع الدورات المتاحة
     *
     * @param views simplified course views – نماذج عرض مبسّطة للدورات
     */
    void clsCoursesView::ListAllCourses(const std::vector<nsViewModels::sCourseView>& views) {
        std::cout << "========================================\n";
        std::cout << "\t\tAvailable Courses\n";
        std::cout << "========================================\n";
        for (const auto& v : views) {
            std::cout << "- (ID: " << v.Code << ") " << v.Name << " -- " << v.Description << "\n";
            // عرض رمز الدورة واسمها ووصفها المختصر
        }
        std::cout << "========================================\n";
    }

}
