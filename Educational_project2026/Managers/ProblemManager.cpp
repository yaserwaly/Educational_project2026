//#include "ProblemManager.hpp"
//#include <fstream>
//#include <string>
//#include <vector>
//#include <iostream>
//#include <unordered_set>
//#include <limits>
//#include "../DataLoaders/ProblemLoader.hpp"
//#include "../Registry/DispatcherRegistrar.hpp"
//#include "../Registry/DispatcherRunner.hpp"
//#include "../DataInserters/ProblemInserter.hpp"
//#include "../DataModifiers/ProblemModifier.hpp"
//#include "../DataRemovers/ProblemRemover.hpp"
//
//namespace nsProblemManager {
//
//    // Constructor: bind manager to a specific course – المُنشئ: ربط المدير بدورة معينة
//    clsProblemManager::clsProblemManager(nsCourseData::sCourseData& course)
//        : Course(course) {
//    }
//
//    // Load all problems for a given course folder – تحميل جميع المشاكل من مجلد دورة محددة
//    std::vector<nsProblemData::sProblemData> clsProblemManager::LoadProblemsForCourse(const std::string& problemsFolder) const {
//        nsProblemLoader::clsProblemLoader loader;
//        return loader.LoadProblems(problemsFolder);
//    }
//
//    // Register a problem's execution function – تسجيل دالة تنفيذ المشكلة
//    void clsProblemManager::RegisterProblem(int courseId, int problemId, const std::string& fnName, const std::function<void()>& fn) const {
//        nsDispatcherRegistrar::clsDispatcherRegistrar::Register(fnName, fn);              // تسجيل باسم الدالة
//        nsDispatcherRegistrar::clsDispatcherRegistrar::Register(courseId, problemId, fn); // تسجيل باستخدام معرفات الدورة والمشكلة
//    }
//
//    //// Create a new problem on disk – إنشاء مشكلة جديدة على القرص
//    //bool clsProblemManager::CreateProblemOnDisk(int courseID, const nsProblemData::sProblemData& Problem, int problemIndex, int idWidth) const {
//    //    nsProblemInserter::clsProblemInserter inserter;
//    //    return inserter.CreateProblemStructureOnDisk(courseID, Problem, problemIndex, idWidth);
//    //}
//
//    //// Modify an existing problem on disk – تعديل مشكلة موجودة على القرص
//    //bool clsProblemManager::ModifyProblemOnDisk(int courseID, int problemIndex, const nsProblemData::sProblemData& updatedProblem, int idWidth) const {
//    //    nsProblemModifier::clsProblemModifier modifier;
//    //    return modifier.ModifyProblemStructureOnDisk(courseID, problemIndex, updatedProblem, idWidth);
//    //}
//
//    //// Delete a problem and remove its files from the project – حذف مشكلة وإزالة ملفاتها من المشروع
//    //bool clsProblemManager::DeleteProblemFromDiskAndProject(int courseID, int problemIndex, int idWidth, const std::string& vcxprojPath) const {
//    //    nsProblemRemover::clsProblemRemover remover;
//    //    return remover.DeleteProblemStructureFromDiskAndProject(courseID, problemIndex, idWidth, vcxprojPath);
//    //}
//
//    // Select a problem by its assigned code – اختيار مشكلة بناءً على رمزها
//    /*nsProblemData::sProblemData clsProblemManager::SelectProblemByCode(int ProblemCode) const {
//        auto it = std::find_if(Course.Problems.begin(), Course.Problems.end(),
//            [&](const nsProblemData::sProblemData& p) { return p.Code == ProblemCode; });
//        return (it != Course.Problems.end()) ? *it : nsProblemData::sProblemData{};
//    }*/
//
//    // Find the next available problem ID – إيجاد أول معرف مشكلة غير مستخدم
//    /*int clsProblemManager::GetNextProblemIDSafe() const {
//        std::unordered_set<int> seen;
//        int minVal = std::numeric_limits<int>::max();
//        int maxVal = std::numeric_limits<int>::min();
//
//        for (const auto& p : Course.Problems) {
//            int NextId = p.ID;
//            seen.insert(NextId);
//            if (NextId < minVal) minVal = NextId;
//            if (NextId > maxVal) maxVal = NextId;
//        }
//
//        for (int i = minVal; i <= maxVal; ++i) {
//            if (seen.find(i) == seen.end()) {
//                return i;
//            }
//        }
//
//        return maxVal + 1;
//    }*/
//
//    // Return number of problems in the course – إرجاع عدد المشاكل في الدورة
//    int clsProblemManager::NumberOfProblems() const {
//        return static_cast<int>(Course.Problems.size());
//    }
//
//    // Run a problem by its full namespace – تشغيل مشكلة باستخدام namespace الكامل
//    void clsProblemManager::RunProblemByNamespace(const std::string& ns) {
//        nsDispatcherRunner::clsDispatcherRunner::Run(ns);
//    }
//
//    // Run a problem by course ID and problem ID – تشغيل مشكلة باستخدام معرف الدورة ومعرف المشكلة
//    void clsProblemManager::RunProblemById(int courseId, int problemId) {
//        nsDispatcherRunner::clsDispatcherRunner::Run(courseId, problemId);
//    }
//
//}
