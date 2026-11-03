#include "pch.h"
#include <gtest/gtest.h>
#include "FakeCourseRepository.hpp"

TEST(CourseRepositoryFakeTest, SaveAndGetCourseWorks) {
    FakeCourseRepository repo;
    nsCourseData::sCourseData course;
    course.ID = 1;
    course.Name = "Algorithms";

    EXPECT_TRUE(repo.SaveCourse(course));
    EXPECT_EQ(repo.GetCourseById(1).Name, "Algorithms");
}
