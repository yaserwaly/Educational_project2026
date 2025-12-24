#pragma once
#include "../Models/ProblemData.hpp"
#include "../Models/CourseData.hpp"
#include "../Models/ViewModels.hpp"

namespace nsProblemsView {

    /**
     * View class for displaying problem-related information in the UI – كلاس العرض لعرض معلومات المشاكل في الواجهة
     */
    class clsProblemsView {
    public:
        /**
         * Display detailed information about a single problem – عرض معلومات مشكلة واحدة بشكل مفصل
         *
         * @param problem the problem to display – المشكلة المطلوب عرضها
         */
        static void ShowProblemInfo(const nsProblemData::sProblemData& problem);

        /**
         * Display a list of all available problems – عرض قائمة بجميع المشاكل المتاحة
         *
         * @param views simplified problem views – نماذج عرض مبسّطة للمشاكل
         */
        static void ListProblems(const std::vector<nsViewModels::sProblemView>& views);
    };

}
