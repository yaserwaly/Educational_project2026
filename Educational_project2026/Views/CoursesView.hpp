#pragma once
#include "../Models/CourseData.hpp"
#include "../Models/ViewModels.hpp"

namespace nsCoursesView {

    /**
     * View class for displaying course-related information in the UI – كلاس العرض لعرض معلومات الدورات في الواجهة
     */
    class clsCoursesView {
    public:
        /**
         * Display detailed information about a single course – عرض معلومات دورة واحدة بشكل مفصل
         *
         * @param course the course to display – الدورة المطلوب عرضها
         */
        static void ShowCourseInfo(const nsCourseData::sCourseData& course);

        /**
         * Display a list of all available courses – عرض قائمة بجميع الدورات المتاحة
         *
         * @param views simplified course views – نماذج عرض مبسّطة للدورات
         */
        static void ListAllCourses(const std::vector<nsViewModels::sCourseView>& views);
    };

}
