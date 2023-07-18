cmake_minimum_required(VERSION 3.10)
project(checkers_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(
  SOURCE_FILES
  src/pos.cpp
  src/piece.cpp
  src/board.cpp
  src/game.cpp
  src/game_state.cpp
  src/snapshot.cpp
  src/utils.cpp)

add_library(checkers_engine ${SOURCE_FILES})
target_include_directories(checkers_engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(checkers_engine PROPERTIES PUBLIC_HEADER "src/defines.h;src/pos.h;src/piece.h;src/move.h;src/board.h;src/game.h;src/snapshot.h;src/utils.h")
INSTALL(TARGETS checkers_engine
  PUBLIC_HEADER DESTINATION /usr/local/include/checkers_engine
  LIBRARY DESTINATION /usr/local/lib)
