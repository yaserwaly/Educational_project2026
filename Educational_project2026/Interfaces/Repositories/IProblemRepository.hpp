#pragma once
#include "../../Models/ProblemData.hpp"
#include <vector>

namespace nsInterfaces {

    /**
     * Interface for problem data repository operations
     * واجهة عمليات مستودع بيانات المشاكل
     */
    class IProblemRepository {
    public:
        virtual ~IProblemRepository() = default;

        virtual std::vector<nsProblemData::sProblemData> LoadProblemsForCourse(
            int courseId) = 0;

        virtual bool SaveProblem(int courseId,
            const nsProblemData::sProblemData& problem) = 0;

        virtual bool UpdateProblem(int courseId,
            const nsProblemData::sProblemData& problem) = 0;

        virtual bool DeleteProblem(int courseId, int problemId) = 0;

        virtual nsProblemData::sProblemData GetProblemById(int courseId,
            int problemId) = 0;

        /**
         * Select a problem by its assigned code – اختيار مشكلة بناءً على رمزها
        *
        * @param courseId ID of the course – معرف الدورة
        * @param problemCode assigned code of the problem – الرمز المخصص للمشكلة
        * @return matching problem or empty – المشكلة المطابقة أو فارغة
        */
        virtual nsProblemData::sProblemData SelectProblemByCode(int courseId, int problemCode) = 0;

    };

} // namespace nsInterfaces