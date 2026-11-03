#include "pch.h"
#include <gtest/gtest.h>
#include "../Mocks/MockCourseRepository.hpp"

using namespace nsMock;
using ::testing::Return;

TEST(CourseRepositoryMockTest, GetNextCourseIdReturnsExpected) {
    MockCourseRepository mock;
    EXPECT_CALL(mock, GetNextCourseId()).WillOnce(Return(42));
    EXPECT_EQ(mock.GetNextCourseId(), 42);
}
