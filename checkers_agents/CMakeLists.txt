cmake_minimum_required(VERSION 3.10)
project(checkers_agents)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(
  SOURCE_FILES
  src/agent.cpp
  src/random_agent.cpp
  src/first_move_agent.cpp
  src/heuristic_agent.cpp
  src/basic_heuristic.cpp
  src/early_heuristic.cpp
  src/late_heuristic.cpp
  src/minmax_agent.cpp
  src/alphabeta_agent.cpp)

add_library(checkers_agents ${SOURCE_FILES})
target_include_directories(checkers_agents PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
