# مكتبة التنفيذ
add_library(FileManagerLib
  ${PROJECT_SOURCE_DIR}/Adapters/IO/FileManagerAdapter.cpp
  ${PROJECT_SOURCE_DIR}/Adapters/IO/FileManagerAdapter.hpp
 )

target_include_directories(FileManagerLib PUBLIC
  ${PROJECT_SOURCE_DIR}/Adapters/IO
  ${PROJECT_SOURCE_DIR}/Interfaces/IO
)

# ✅ ملفات الاختبار
set(TEST_SOURCES_FileManager
  ${PROJECT_SOURCE_DIR}/Tester/UnitTests/FileManagerTest.cpp
  ${PROJECT_SOURCE_DIR}/Tester/UnitTests/FileManagerMockTest.cpp
  ${PROJECT_SOURCE_DIR}/Tester/IntegrationTests/FileManagerAdapterIntegration.cpp
  ${PROJECT_SOURCE_DIR}/Tester/Fakes/FileManagerFakeTest.cpp
)

add_executable(FileManagerUnitTests ${TEST_SOURCES_FileManager})

target_include_directories(FileManagerUnitTests PRIVATE
  ${PROJECT_SOURCE_DIR}/Adapters/IO
  ${PROJECT_SOURCE_DIR}/Interfaces/IO
  ${PROJECT_SOURCE_DIR}/Tester
  ${PROJECT_SOURCE_DIR}/Tester/UnitTests
  ${PROJECT_SOURCE_DIR}/Tester/IntegrationTests
  ${PROJECT_SOURCE_DIR}/Tester/Fakes
  ${PROJECT_SOURCE_DIR}/Tester/Mocks
  ${PROJECT_SOURCE_DIR}/googletest/googletest/include
  ${PROJECT_SOURCE_DIR}/googletest/googlemock/include
)

target_link_libraries(FileManagerUnitTests
  FileManagerLib
  gtest
  gmock
  gtest_main
)

