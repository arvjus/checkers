project(google_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} checkers_engine/src checkers_agents/src)

set(
  SOURCE_FILES
  src/main.cpp
  src/test-board.cpp
  src/test-piece.cpp
  src/test-pos.cpp
  src/test-game.cpp
  src/test-agent.cpp
  src/test-agents.cpp
  src/test-snapshot.cpp
  src/test-heuristics.cpp)

add_executable(google_tests_run ${SOURCE_FILES})
target_include_directories(google_tests_run PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(google_tests_run checkers_engine checkers_agents ${GTEST_LIBRARIES} pthread)

add_executable(checkers_run src/checkers_run.cpp)
target_include_directories(checkers_run PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(checkers_run checkers_engine checkers_agents pthread)
