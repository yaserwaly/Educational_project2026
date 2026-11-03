#include "pch.h"
#include "AdaptersTest.hpp"
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include <memory>
#include "../Adapters/IO/FileManagerAdapter.hpp"
#include "../Adapters/Repositories/CourseRepositoryAdapter.hpp"
#include "../Adapters/Repositories/ProblemRepositoryAdapter.hpp"

/**
 * Test the new adapters without affecting main project
 * اختبار المحولات الجديدة بدون التأثير على المشروع الرئيسي
 */
void TestAdapters() {
    std::cout << "=== Testing New Adapters ===\n";

    // 1. Test FileManagerAdapter
    auto fileManager = std::make_unique<nsAdapters::clsFileManagerAdapter>();

    std::string testFile = "adapter_test.txt";
    if (fileManager->WriteFile(testFile, "Hello from Adapter!")) {
        std::cout << "✅ FileManagerAdapter - WriteFile: SUCCESS\n";

        std::string content = fileManager->ReadFile(testFile);
        std::cout << "✅ FileManagerAdapter - ReadFile: " << content << "\n";

        std::string formattedId = fileManager->FormatID(5, 3);
        std::cout << "✅ FileManagerAdapter - FormatID: " << formattedId << "\n";
    }

    // 2. Test CourseRepositoryAdapter
    auto courseRepo = std::make_unique<nsAdapters::clsCourseRepositoryAdapter>();
    auto courses = courseRepo->LoadAllCourses();
    std::cout << "✅ CourseRepositoryAdapter - LoadAllCourses: "
        << courses.size() << " courses found\n";

    // 3. Test ProblemRepositoryAdapter  
    auto problemRepo = std::make_unique<nsAdapters::clsProblemRepositoryAdapter>();

    // نختبر فقط إذا في courses موجودة
    if (!courses.empty()) {
        int firstCourseId = courses[0].ID;
        auto problems = problemRepo->LoadProblemsForCourse(firstCourseId);
        std::cout << "✅ ProblemRepositoryAdapter - LoadProblemsForCourse: "
            << problems.size() << " problems found\n";
    }

    std::cout << "=== Adapters Test Completed ===\n";
}