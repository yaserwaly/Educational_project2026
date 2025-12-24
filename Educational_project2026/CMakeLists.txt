cmake_minimum_required(VERSION 3.16)
project(Educational_project LANGUAGES CXX)

# تفعيل C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

enable_testing()

# تحميل الملفات المقسمة
include(${CMAKE_SOURCE_DIR}/cmake/Dependencies.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/FileManager.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CourseRepository.cmake)

include(GoogleTest)

# اكتشاف الاختبارات تلقائيًا
gtest_discover_tests(CourseRepositoryUnitTests)
gtest_discover_tests(FileManagerUnitTests)

