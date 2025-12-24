#pragma once
#include "../../Models/CourseData.hpp"
#include <vector>

namespace nsInterfaces {

    /**
     * Interface for course data repository operations
     * واجهة عمليات مستودع بيانات الدورات
     */
    class ICourseRepository {
    public:
        virtual ~ICourseRepository() = default;

        virtual std::vector<nsCourseData::sCourseData> LoadAllCourses() = 0;

        virtual bool SaveCourse(const nsCourseData::sCourseData& course) = 0;

        virtual bool UpdateCourse(const nsCourseData::sCourseData& course) = 0;

        virtual bool DeleteCourse(int courseId) = 0;

        virtual nsCourseData::sCourseData GetCourseById(int courseId) = 0;

        /**
        * Get the next available course ID – الحصول على أول معرف دورة غير مستخدم
        *
        * @return next safe course ID – المعرف التالي المتاح للدورة
        */
        virtual int GetNextCourseId() = 0;

    };

} // namespace nsInterfaces