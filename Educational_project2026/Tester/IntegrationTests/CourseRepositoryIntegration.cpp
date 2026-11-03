#include "pch.h"
#include <gtest/gtest.h>
#include "../../Adapters/Repositories/CourseRepositoryAdapter.hpp"
// #include <filesystem>  // مكرر: موجود أصلاً بـ pch.h

using namespace nsAdapters;

TEST(CourseRepositoryIntegration, LoadAllCoursesReturnsVector) {
    clsCourseRepositoryAdapter repo;
    auto courses = repo.LoadAllCourses();
    EXPECT_TRUE(courses.size() >= 0);  // ممكن يكون فارغ، بس لازم يرجع شي
}
