#pragma once
#include "../../Interfaces/Repositories/IProblemRepository.hpp"
#include "../../Models/CourseData.hpp"
#include "../../DataLoaders/ProblemLoader.hpp"
#include "../../DataInserters/ProblemInserter.hpp"
#include "../../DataModifiers/ProblemModifier.hpp"
#include "../../DataRemovers/ProblemRemover.hpp"
#include <memory>

#include "../../Interfaces/IO/IFileManager.hpp"
#include "../../Interfaces/Repositories/ICourseRepository.hpp"

namespace nsAdapters {

    /**
     * Adapter for ProblemManager to implement IProblemRepository interface
     * محول لـ ProblemManager لتنفيذ واجهة IProblemRepository
     */
    class clsProblemRepositoryAdapter : public nsInterfaces::IProblemRepository {
    private:
        std::unique_ptr<nsInterfaces::IFileManager> m_FileManager;
        std::unique_ptr<nsInterfaces::ICourseRepository> m_CourseRepository;
        std::unique_ptr<nsProblemLoader::clsProblemLoader> m_Loader;
        std::unique_ptr<nsProblemInserter::clsProblemInserter> m_Inserter;
        std::unique_ptr<nsProblemModifier::clsProblemModifier> m_Modifier;
        std::unique_ptr<nsProblemRemover::clsProblemRemover> m_Remover;

    public:
        /**
         * Constructor with full dependency injection
         * مُنشئ مع حقن dependencies كامل
         */
        clsProblemRepositoryAdapter(
            std::unique_ptr<nsInterfaces::IFileManager> fileManager = nullptr,
            std::unique_ptr<nsInterfaces::ICourseRepository> courseRepository = nullptr,
            std::unique_ptr<nsProblemLoader::clsProblemLoader> loader = nullptr, // ⬅️ جديد
            std::unique_ptr<nsProblemInserter::clsProblemInserter> inserter = nullptr,
            std::unique_ptr<nsProblemModifier::clsProblemModifier> modifier = nullptr,
            std::unique_ptr<nsProblemRemover::clsProblemRemover> remover = nullptr
        );

        std::vector<nsProblemData::sProblemData> LoadProblemsForCourse(
            int courseId) override;

        bool SaveProblem(int courseId,
            const nsProblemData::sProblemData& problem) override;

        bool UpdateProblem(int courseId,
            const nsProblemData::sProblemData& problem) override;

        bool DeleteProblem(int courseId, int problemId) override;

        nsProblemData::sProblemData GetProblemById(int courseId,
            int problemId) override;

    private:
        nsCourseData::sCourseData GetCourseById(int courseId);
        /**
        * Get the next available problem ID – الحصول على أول معرف مشكلة غير مستخدم
        */
        int GetNextProblemId(int courseId);

        /**
         * Select a problem by its assigned code – اختيار مشكلة بناءً على رمزها
         */
        nsProblemData::sProblemData SelectProblemByCode(int courseId, int problemCode);
        /*nsProblemInserter::clsProblemInserter m_ProblemInserter;
		nsProblemModifier::clsProblemModifier m_ProblemModifier;
        nsProblemRemover::clsProblemRemover m_ProblemRemover;*/
    };

} // namespace nsAdapters