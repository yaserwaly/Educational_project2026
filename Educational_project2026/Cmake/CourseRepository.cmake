add_library(CourseRepositoryLib
  ${PROJECT_SOURCE_DIR}/Adapters/Repositories/CourseRepositoryAdapter.cpp
  ${PROJECT_SOURCE_DIR}/Adapters/Repositories/CourseRepositoryAdapter.hpp
  ${PROJECT_SOURCE_DIR}/DataLoaders/CourseLoader.cpp
  ${PROJECT_SOURCE_DIR}/DataLoaders/ProblemLoader.cpp
  ${PROJECT_SOURCE_DIR}/DataInserters/CourseInserter.cpp
  ${PROJECT_SOURCE_DIR}/DataInserters/ProblemInserter.cpp
  ${PROJECT_SOURCE_DIR}/DataModifiers/CourseModifier.cpp
  ${PROJECT_SOURCE_DIR}/DataRemovers/CourseRemover.cpp
  ${PROJECT_SOURCE_DIR}/VcxprojUpdater/VcxprojUpdater.cpp
)

target_include_directories(CourseRepositoryLib PUBLIC
  ${PROJECT_SOURCE_DIR}/Adapters/Repositories
  ${PROJECT_SOURCE_DIR}/Interfaces/Repositories
  ${PROJECT_SOURCE_DIR}/DataLoaders
  ${PROJECT_SOURCE_DIR}/DataInserters
  ${PROJECT_SOURCE_DIR}/DataModifiers
  ${PROJECT_SOURCE_DIR}/DataRemovers
  ${PROJECT_SOURCE_DIR}/VcxprojUpdater

)

# ربط المكتبات اللازمة
target_link_libraries(CourseRepositoryLib
  FileManagerLib
  tinyxml2
)

set(TEST_SOURCES_CourseRepository
  ${PROJECT_SOURCE_DIR}/Tester/UnitTests/CourseRepositoryTest.cpp
  ${PROJECT_SOURCE_DIR}/Tester/UnitTests/CourseRepositoryMockTest.cpp
  ${PROJECT_SOURCE_DIR}/Tester/IntegrationTests/CourseRepositoryIntegration.cpp
  ${PROJECT_SOURCE_DIR}/Tester/Fakes/CourseRepositoryFakeTest.cpp
)

add_executable(CourseRepositoryUnitTests ${TEST_SOURCES_CourseRepository})

target_include_directories(CourseRepositoryUnitTests PRIVATE
  ${PROJECT_SOURCE_DIR}/Adapters/Repositories
  ${PROJECT_SOURCE_DIR}/Interfaces/Repositories
  ${PROJECT_SOURCE_DIR}/Tester
  ${PROJECT_SOURCE_DIR}/Tester/UnitTests
  ${PROJECT_SOURCE_DIR}/Tester/IntegrationTests
  ${PROJECT_SOURCE_DIR}/Tester/Fakes
  ${PROJECT_SOURCE_DIR}/Tester/Mocks
  ${PROJECT_SOURCE_DIR}/googletest/googletest/include
  ${PROJECT_SOURCE_DIR}/googletest/googlemock/include
)

target_link_libraries(CourseRepositoryUnitTests
  CourseRepositoryLib
  FileManagerLib
  tinyxml2
  gtest
  gmock
  gtest_main
)