#pragma once
#include "../../Interfaces/Repositories/ICourseRepository.hpp"
#include <gmock/gmock.h>

namespace nsMock {

    class MockCourseRepository : public nsInterfaces::ICourseRepository {
    public:
        MOCK_METHOD(std::vector<nsCourseData::sCourseData>, LoadAllCourses, (), (override));
        MOCK_METHOD(bool, SaveCourse, (const nsCourseData::sCourseData& course), (override));
        MOCK_METHOD(bool, UpdateCourse, (const nsCourseData::sCourseData& course), (override));
        MOCK_METHOD(bool, DeleteCourse, (int courseId), (override));
        MOCK_METHOD(nsCourseData::sCourseData, GetCourseById, (int courseId), (override));
        MOCK_METHOD(int, GetNextCourseId, (), (override));
    };

}
