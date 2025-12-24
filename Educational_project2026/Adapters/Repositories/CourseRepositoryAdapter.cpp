#include "CourseRepositoryAdapter.hpp"
#include "../IO/FileManagerAdapter.hpp"
#include <algorithm>
#include <unordered_set>
//#include "../../Registry/DispatcherRegistrar.hpp"

namespace nsAdapters {

    clsCourseRepositoryAdapter::clsCourseRepositoryAdapter(
        std::unique_ptr<nsInterfaces::IFileManager> fileManager,
        std::unique_ptr<nsCourseLoader::clsCourseLoader> loader,
        std::unique_ptr<nsCourseInserter::clsCourseInserter> inserter,
        std::unique_ptr<nsCourseModifier::clsCourseModifier> modifier,
        std::unique_ptr<nsCourseRemover::clsCourseRemover> remover,
		std::unique_ptr<nsProblemLoader::clsProblemLoader> problemLoader
    ) : m_FileManager(fileManager ? std::move(fileManager) : std::make_unique<clsFileManagerAdapter>()),
        m_Loader(loader ? std::move(loader) : std::make_unique<nsCourseLoader::clsCourseLoader>()),
        m_Inserter(inserter ? std::move(inserter) : std::make_unique<nsCourseInserter::clsCourseInserter>()),
        m_Modifier(modifier ? std::move(modifier) : std::make_unique<nsCourseModifier::clsCourseModifier>()),
        m_Remover(remover ? std::move(remover) : std::make_unique<nsCourseRemover::clsCourseRemover>()),
    m_ProblemLoader(problemLoader ? std::move(problemLoader) : std::make_unique<nsProblemLoader::clsProblemLoader>()){
    }

    std::vector<nsCourseData::sCourseData> clsCourseRepositoryAdapter::LoadAllCourses() {
        std::vector<nsCourseData::sCourseData> result;
        std::vector<std::pair<std::string, std::filesystem::file_time_type>> folderTimes;

        const std::string baseFolder = "Courses";
        if (!std::filesystem::exists(baseFolder)) return {};

        for (const auto& entry : std::filesystem::directory_iterator(baseFolder)) {
            if (entry.is_directory()) {
                folderTimes.emplace_back(entry.path().string(), std::filesystem::last_write_time(entry));
            }
        }

        std::sort(folderTimes.begin(), folderTimes.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });

        //nsCourseLoader::clsCourseLoader loader;
        //nsProblemLoader::clsProblemLoader problemLoader;

        int startCode = 1;
        for (const auto& [coursePath, _] : folderTimes) {
            //nsCourseData::sCourseData c = loader.LoadCourse(coursePath);
            nsCourseData::sCourseData c = m_Loader->LoadCourse(coursePath);
            c.Code = startCode++;
            //c.Problems = problemLoader.LoadProblems(coursePath + "/Problems");
            c.Problems = m_ProblemLoader->LoadProblems(coursePath + "/Problems");


            //// ⬇️ مثال على التسجيل (اختياري حسب المعمارية)
            //for (const auto& p : c.Problems) {
            //    nsDispatcherRegistrar::clsDispatcherRegistrar::Register(p.Namespace, [=]() {
            //        // لازم تكون الدالة موجودة فعليًا
            //        });
            //    nsDispatcherRegistrar::clsDispatcherRegistrar::Register(c.ID, p.ID, [=]() {
            //        // نفس الشي
            //        });
            //}

            result.push_back(std::move(c));
        }

        return result;
    }

    int clsCourseRepositoryAdapter::GetNextCourseId() {
        auto courses = LoadAllCourses();
        std::unordered_set<int> seen;
        int minVal = std::numeric_limits<int>::max();
        int maxVal = std::numeric_limits<int>::min();

        for (const auto& c : courses) {
            int id = c.ID;
            seen.insert(id);
            if (id < minVal) minVal = id;
            if (id > maxVal) maxVal = id;
        }

        for (int i = minVal; i <= maxVal; ++i) {
            if (seen.find(i) == seen.end()) {
                return i;
            }
        }

        return maxVal + 1;
    }


    bool clsCourseRepositoryAdapter::SaveCourse(const nsCourseData::sCourseData& course) {
		//return m_CourseInserter.CreateCourseStructureOnDisk(course , 2);

		return m_Inserter->CreateCourseStructureOnDisk(course, 2);
    }

    bool clsCourseRepositoryAdapter::UpdateCourse(const nsCourseData::sCourseData& course) {
		//return m_CourseModifier.ModifyCourseStructureOnDisk(course, 2);

		return m_Modifier->ModifyCourseStructureOnDisk(course, 2);
    }

    bool clsCourseRepositoryAdapter::DeleteCourse(int courseId) {
        /*return m_CourseRemover.DeleteCourseStructureFromDiskAndProject(courseId, 2,
			"Educational_project.vcxproj");*/

        return m_Remover->DeleteCourseStructureFromDiskAndProject(courseId, 2,
			"Educational_project2026.vcxproj");
    }

    nsCourseData::sCourseData clsCourseRepositoryAdapter::GetCourseById(int courseId) {
        const auto& courses = LoadAllCourses();

        auto it = std::find_if(courses.begin(), courses.end(),
            [courseId](const nsCourseData::sCourseData& course) {
                return course.ID == courseId;
            });

        return (it != courses.end()) ? *it : nsCourseData::sCourseData{};
    }

} // namespace nsAdapters