#pragma once
#include "../../Interfaces/Repositories/ICourseRepository.hpp"
//#include "../../Managers/CourseManager.hpp"
#include "../../DataInserters/CourseInserter.hpp"
#include "../../DataModifiers/CourseModifier.hpp"
#include "../../DataRemovers/CourseRemover.hpp"
#include "../../DataLoaders/ProblemLoader.hpp"
#include <memory>

#include "../../Interfaces/IO/IFileManager.hpp"
#include "../../DataLoaders/CourseLoader.hpp"


namespace nsAdapters {

    /**
     * Adapter for CourseManager to implement ICourseRepository interface
     * محول لـ CourseManager لتنفيذ واجهة ICourseRepository
     */
    class clsCourseRepositoryAdapter : public nsInterfaces::ICourseRepository {
    public:
        clsCourseRepositoryAdapter(
            std::unique_ptr<nsInterfaces::IFileManager> fileManager = nullptr,
            std::unique_ptr<nsCourseLoader::clsCourseLoader> loader = nullptr,
            std::unique_ptr<nsCourseInserter::clsCourseInserter> inserter = nullptr,
            std::unique_ptr<nsCourseModifier::clsCourseModifier> modifier = nullptr,
            std::unique_ptr<nsCourseRemover::clsCourseRemover> remover = nullptr,
			std::unique_ptr<nsProblemLoader::clsProblemLoader> problemLoader = nullptr
        );

        std::vector<nsCourseData::sCourseData> LoadAllCourses() override;

        bool SaveCourse(const nsCourseData::sCourseData& course) override;

        bool UpdateCourse(const nsCourseData::sCourseData& course) override;

        bool DeleteCourse(int courseId) override;

        nsCourseData::sCourseData GetCourseById(int courseId) override;

        /**
        * Get the next available course ID – الحصول على أول معرف دورة غير مستخدم
        */
        int GetNextCourseId();

    private:
        /*nsCourseManager::clsCourseManager m_CourseManager;
		nsCourseInserter::clsCourseInserter m_CourseInserter;
		nsCourseModifier::clsCourseModifier m_CourseModifier;
		nsCourseRemover::clsCourseRemover m_CourseRemover;*/

        std::unique_ptr<nsInterfaces::IFileManager> m_FileManager;
        std::unique_ptr<nsCourseLoader::clsCourseLoader> m_Loader;
        std::unique_ptr<nsCourseInserter::clsCourseInserter> m_Inserter;
        std::unique_ptr<nsCourseModifier::clsCourseModifier> m_Modifier;
        std::unique_ptr<nsCourseRemover::clsCourseRemover> m_Remover;
		std::unique_ptr<nsProblemLoader::clsProblemLoader> m_ProblemLoader;
    };

} // namespace nsAdapters