#include <gtest/gtest.h>
#include "../../Adapters/Repositories/CourseRepositoryAdapter.hpp"

using namespace nsAdapters;

TEST(CourseRepositoryTest, DefaultConstructionDoesNotThrow) {
    EXPECT_NO_THROW(clsCourseRepositoryAdapter repo);
}
