#include "ProblemRepositoryAdapter.hpp"
#include "../IO/FileManagerAdapter.hpp"
//#include "../../Managers/CourseManager.hpp"
#include "../../Interfaces/Repositories/ICourseRepository.hpp"
#include "CourseRepositoryAdapter.hpp"
#include "../../DataLoaders/ProblemLoader.hpp"
#include <algorithm>
#include <unordered_set>

namespace nsAdapters {

    clsProblemRepositoryAdapter::clsProblemRepositoryAdapter(
        std::unique_ptr<nsInterfaces::IFileManager> fileManager,
        std::unique_ptr<nsInterfaces::ICourseRepository> courseRepository,
		std::unique_ptr<nsProblemLoader::clsProblemLoader> loader,
        std::unique_ptr<nsProblemInserter::clsProblemInserter> inserter,
        std::unique_ptr<nsProblemModifier::clsProblemModifier> modifier,
        std::unique_ptr<nsProblemRemover::clsProblemRemover> remover
    ) : m_FileManager(fileManager ? std::move(fileManager) : std::make_unique<clsFileManagerAdapter>()),
        m_CourseRepository(courseRepository ? std::move(courseRepository) : std::make_unique<clsCourseRepositoryAdapter>()),
		m_Loader(loader ? std::move(loader) : std::make_unique<nsProblemLoader::clsProblemLoader>()),
        m_Inserter(inserter ? std::move(inserter) : std::make_unique<nsProblemInserter::clsProblemInserter>()),
        m_Modifier(modifier ? std::move(modifier) : std::make_unique<nsProblemModifier::clsProblemModifier>()),
        m_Remover(remover ? std::move(remover) : std::make_unique<nsProblemRemover::clsProblemRemover>()) {
    }


    std::vector<nsProblemData::sProblemData>
        clsProblemRepositoryAdapter::LoadProblemsForCourse(int courseId) {
        /*nsAdapters::clsFileManagerAdapter fileManager;
        auto course = GetCourseById(courseId);
        if (course.ID == 0) return {};

        nsProblemManager::clsProblemManager manager(course);
        return manager.LoadProblemsForCourse("Courses/Course" +
            fileManager.FormatID(courseId, 2) +
            "/Problems");*/

        auto course = m_CourseRepository->GetCourseById(courseId);
        if (course.ID == 0) return {};

        std::string folder = "Courses/Course" + m_FileManager->FormatID(courseId, 2) + "/Problems";

        // نستخدم الـ ProblemLoader إذا كان موجود، أو ننفذ المنطق مباشرة
        /*nsProblemLoader::clsProblemLoader loader;
        return loader.LoadProblems(folder);*/
        return m_Loader->LoadProblems(folder);
    }

    bool clsProblemRepositoryAdapter::SaveProblem(int courseId,
        const nsProblemData::sProblemData& problem) {
  //      auto course = GetCourseById(courseId);
  //      if (course.ID == 0) return false;

  //      nsProblemManager::clsProblemManager manager(course);
  //      int nextId = manager.GetNextProblemIDSafe();
  //      //return manager.CreateProblemOnDisk(courseId, problem, nextId, 3);
		//return m_ProblemInserter.CreateProblemStructureOnDisk(courseId, problem, nextId, 3);

        auto course = m_CourseRepository->GetCourseById(courseId);
        if (course.ID == 0) return false;

        int nextId = GetNextProblemId(courseId);
        return m_Inserter->CreateProblemStructureOnDisk(courseId, problem, nextId, 3);
    }

    bool clsProblemRepositoryAdapter::UpdateProblem(int courseId,
        const nsProblemData::sProblemData& problem) {
  //      auto course = GetCourseById(courseId);
  //      if (course.ID == 0) return false;

  //      //nsProblemManager::clsProblemManager manager(course);
  //      //return manager.ModifyProblemOnDisk(courseId, problem.ID, problem, 3);
		//return m_ProblemModifier.ModifyProblemStructureOnDisk(courseId, problem.ID, problem, 3);

        auto course = m_CourseRepository->GetCourseById(courseId);
        if (course.ID == 0) return false;

        return m_Modifier->ModifyProblemStructureOnDisk(courseId, problem.ID, problem, 3);
    }

    bool clsProblemRepositoryAdapter::DeleteProblem(int courseId, int problemId) {
  //      auto course = GetCourseById(courseId);
  //      if (course.ID == 0) return false;

  //      //nsProblemManager::clsProblemManager manager(course);
  //      //return manager.DeleteProblemFromDiskAndProject(courseId, problemId, 3,
  //          //"Educational_project.vcxproj");
		//return m_ProblemRemover.DeleteProblemStructureFromDiskAndProject(courseId, problemId, 3, "Educational_project.vcxproj");

        auto course = m_CourseRepository->GetCourseById(courseId);
        if (course.ID == 0) return false;

        return m_Remover->DeleteProblemStructureFromDiskAndProject(courseId, problemId, 3,
            "Educational_project2026.vcxproj");
    }

    nsProblemData::sProblemData
        clsProblemRepositoryAdapter::GetProblemById(int courseId, int problemId) {
        /*auto problems = LoadProblemsForCourse(courseId);
        auto it = std::find_if(problems.begin(), problems.end(),
            [problemId](const nsProblemData::sProblemData& problem) {
                return problem.ID == problemId;
            });

        return (it != problems.end()) ? *it : nsProblemData::sProblemData{};*/

        auto problems = LoadProblemsForCourse(courseId);
        auto it = std::find_if(problems.begin(), problems.end(),
            [problemId](const nsProblemData::sProblemData& problem) {
                return problem.ID == problemId;
            });

        return (it != problems.end()) ? *it : nsProblemData::sProblemData{};
    }

    nsCourseData::sCourseData clsProblemRepositoryAdapter::GetCourseById(int courseId) {
        /*nsCourseManager::clsCourseManager courseManager;
        courseManager.Load();

        const auto& courses = courseManager.GetCourses();
        auto it = std::find_if(courses.begin(), courses.end(),
            [courseId](const nsCourseData::sCourseData& course) {
                return course.ID == courseId;
            });

        return (it != courses.end()) ? *it : nsCourseData::sCourseData{};*/

        return m_CourseRepository->GetCourseById(courseId);
    }

    /*int clsProblemRepositoryAdapter::GetNextProblemId(int courseId) {
        auto problems = LoadProblemsForCourse(courseId);
        int maxId = 0;
        for (const auto& problem : problems) {
            if (problem.ID > maxId) maxId = problem.ID;
        }
        return maxId + 1;
    }*/

    int clsProblemRepositoryAdapter::GetNextProblemId(int courseId) {
        auto problems = LoadProblemsForCourse(courseId);
        std::unordered_set<int> seen;
        int minVal = std::numeric_limits<int>::max();
        int maxVal = std::numeric_limits<int>::min();

        for (const auto& p : problems) {
            int id = p.ID;
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

    nsProblemData::sProblemData clsProblemRepositoryAdapter::SelectProblemByCode(int courseId, int problemCode) {
        auto problems = LoadProblemsForCourse(courseId);
        auto it = std::find_if(problems.begin(), problems.end(),
            [problemCode](const nsProblemData::sProblemData& p) {
                return p.Code == problemCode;
            });

        return (it != problems.end()) ? *it : nsProblemData::sProblemData{};
    }



} // namespace nsAdapters