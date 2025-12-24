//#include "CourseManager.hpp"
//#include <filesystem>
//#include <unordered_set>
//#include <limits>
//#include "../Registry/FileHelpers.hpp"
//#include "../DataLoaders/CourseLoader.hpp"
//#include "../DataLoaders/ProblemLoader.hpp"
//#include "../DataInserters/CourseInserter.hpp"
//#include "../DataModifiers/CourseModifier.hpp"
//#include "../DataRemovers/CourseRemover.hpp"
//
//namespace nsCourseManager {
//
//    namespace fs = std::filesystem;
//
//    // Constructor: initialize base folder – المُنشئ: تهيئة مجلد الأساس
//    clsCourseManager::clsCourseManager(const std::string& baseFolder)
//        : BaseFolder(baseFolder) {
//    }
//
//    // Load all courses from disk and assign codes – تحميل جميع الدورات من القرص وتعيين رموز لها
//    //void clsCourseManager::Load(int startCode) {
//    //    AllCourses.clear();
//    //    std::vector<std::pair<std::string, fs::file_time_type>> folderTimes;
//
//    //    if (!fs::exists(BaseFolder)) return;
//
//    //    // Collect course folders with timestamps – جمع مجلدات الدورات مع توقيت التعديل
//    //    for (const auto& entry : fs::directory_iterator(BaseFolder)) {
//    //        if (entry.is_directory()) {
//    //            folderTimes.emplace_back(entry.path().string(), fs::last_write_time(entry));
//    //        }
//    //    }
//
//    //    // Sort folders by last write time – ترتيب المجلدات حسب تاريخ التعديل
//    //    std::sort(folderTimes.begin(), folderTimes.end(),
//    //        [](const auto& a, const auto& b) {
//    //            return a.second < b.second;
//    //        });
//
//    //    nsCourseLoader::clsCourseLoader loader;
//    //    nsProblemLoader::clsProblemLoader problemLoader;
//
//    //    // Load each course and its problems – تحميل كل دورة والمشاكل التابعة لها
//    //    for (const auto& [coursePath, _] : folderTimes) {
//    //        nsCourseData::sCourseData c = loader.LoadCourse(coursePath);
//    //        c.Code = startCode++;
//    //        c.Problems = problemLoader.LoadProblems(coursePath + "/Problems");
//    //        AllCourses.push_back(std::move(c));
//    //    }
//    //}
//
//    // Return all loaded courses – إرجاع جميع الدورات المحمّلة
//    const std::vector<nsCourseData::sCourseData>& clsCourseManager::GetCourses() const {
//        return AllCourses;
//    }
//
//    // Find the next available course ID – إيجاد أول معرف دورة غير مستخدم
//    /*int clsCourseManager::GetNextCourseIDSafe() const {
//        std::unordered_set<int> seen;
//        int minVal = std::numeric_limits<int>::max();
//        int maxVal = std::numeric_limits<int>::min();
//
//        for (const auto& p : AllCourses) {
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
//    // Return number of loaded courses – إرجاع عدد الدورات المحمّلة
//    int clsCourseManager::NumberOfCourses() const {
//        return static_cast<int>(AllCourses.size());
//    }
//
//    // Select a course by its assigned code – اختيار دورة بناءً على رمزها
//    void clsCourseManager::SelectCourseByCode(nsAppState::sAppState& State, int CourseCode) const {
//        auto it = std::find_if(AllCourses.begin(), AllCourses.end(), [&](const nsCourseData::sCourseData& c) {
//            return c.Code == CourseCode;
//            });
//
//        if (it != AllCourses.end()) {
//            State.selectedCourse = *it;
//        }
//    }
//
//    //// Create a new course on disk – إنشاء دورة جديدة على القرص
//    //bool clsCourseManager::CreateCourseOnDisk(const nsCourseData::sCourseData& course, int idWidth) const {
//    //    nsCourseInserter::clsCourseInserter inserter;
//    //    return inserter.CreateCourseStructureOnDisk(course, idWidth);
//    //}
//
//    //// Modify an existing course on disk – تعديل دورة موجودة على القرص
//    //bool clsCourseManager::ModifyCourseOnDisk(const nsCourseData::sCourseData& updatedCourse, int idWidth) const {
//    //    nsCourseModifier::clsCourseModifier modifier;
//    //    return modifier.ModifyCourseStructureOnDisk(updatedCourse, idWidth);
//    //}
//
//    //// Delete a course and remove its files from the project – حذف دورة وإزالة ملفاتها من المشروع
//    //bool clsCourseManager::DeleteCourseFromDiskAndProject(int courseID, int idWidth, const std::string& vcxprojPath) const {
//    //    nsCourseRemover::clsCourseRemover remover;
//    //    return remover.DeleteCourseStructureFromDiskAndProject(courseID, idWidth, vcxprojPath);
//    //}
//
//}
