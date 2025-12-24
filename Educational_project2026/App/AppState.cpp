#include "AppState.hpp"
#include <algorithm>

namespace nsAppState {

    // Reset the application state to its initial values – إعادة حالة التطبيق إلى القيم الابتدائية
    void sAppState::Reset() {
        currentCourseId = 0;
        currentProblemId = 0;
        selectedCourse = nsCourseData::sCourseData{};
        selectedProblem = nsProblemData::sProblemData{};
    }

    // Check if a course has been selected – التحقق من اختيار دورة
    bool sAppState::IsCourseSelected() const {
        return selectedCourse.ID > 0;
    }

    // Check if a problem has been selected – التحقق من اختيار مشكلة
    bool sAppState::IsProblemSelected() const {
        return selectedProblem.ID > 0;
    }

    // Reload the selected course from the full course list – إعادة تحميل الدورة المختارة من قائمة الدورات
    void sAppState::ReloadSelectedCourse(const std::vector<nsCourseData::sCourseData>& allCourses) {
        auto it = std::find_if(allCourses.begin(), allCourses.end(),
            [this](const nsCourseData::sCourseData& c) {
                return c.Code == selectedCourse.Code;
            });

        if (it != allCourses.end()) {
            selectedCourse = *it;
        }
    }

}
