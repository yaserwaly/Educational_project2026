#pragma once
#include "../../Interfaces/Repositories/ICourseRepository.hpp"

class FakeCourseRepository : public nsInterfaces::ICourseRepository {
    std::vector<nsCourseData::sCourseData> courses;

public:
    std::vector<nsCourseData::sCourseData> LoadAllCourses() override {
        return courses;
    }

    bool SaveCourse(const nsCourseData::sCourseData& course) override {
        courses.push_back(course);
        return true;
    }

    bool UpdateCourse(const nsCourseData::sCourseData& course) override {
        for (auto& c : courses) {
            if (c.ID == course.ID) {
                c = course;
                return true;
            }
        }
        return false;
    }

    bool DeleteCourse(int courseId) override {
        auto it = std::remove_if(courses.begin(), courses.end(),
            [courseId](const auto& c) { return c.ID == courseId; });
        if (it != courses.end()) {
            courses.erase(it, courses.end());
            return true;
        }
        return false;
    }

    nsCourseData::sCourseData GetCourseById(int courseId) override {
        for (const auto& c : courses) {
            if (c.ID == courseId) return c;
        }
        return {};
    }

    int GetNextCourseId() override {
        int maxId = 0;
        for (const auto& c : courses) {
            if (c.ID > maxId) maxId = c.ID;
        }
        return maxId + 1;
    }
};
