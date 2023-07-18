cmake_minimum_required(VERSION 3.10)
project(checkers VERSION 1.0 LANGUAGES CXX)
string(TIMESTAMP TODAY "%Y%m%d")

set(CMAKE_PREFIX_PATH /opt/local ${CMAKE_PREFIX_PATH})
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(ASSETS_DIR "${CMAKE_INSTALL_PREFIX}/share/checkers/assets")

option(VERBOSE "Print traces" OFF)
option(VERBOSE_EVEN_MORE "Print even more traces" OFF)

configure_file(checkers_config.h.in checkers_config.h)

find_package(wxWidgets 3.1.4 REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES
  src/checkers.cpp
  src/board_panel.cpp
  src/main_frame.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

set(checkers_ICON ${CMAKE_CURRENT_SOURCE_DIR}/assets/checkers.icns)
set_source_files_properties(${checkers_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set(MACOSX_BUNDLE_ICON_FILE checkers.icns)

add_executable(checkers MACOSX_BUNDLE ${checkers_ICON} ${SOURCE_FILES})

INSTALL(TARGETS checkers DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
INSTALL(FILES
  assets/black.png
  assets/black-sel.png
  assets/black-king.png
  assets/black-king-sel.png
  assets/white.png
  assets/white-sel.png
  assets/white-king.png
  assets/white-king-sel.png
  assets/valid-position.png
  DESTINATION ${ASSETS_DIR})

include_directories(${CMAKE_CURRENT_BINARY_DIR} checkers_engine/src)
add_subdirectory(checkers_engine)

include_directories(${CMAKE_CURRENT_BINARY_DIR} checkers_agents/src)
add_subdirectory(checkers_agents)

target_link_libraries(${PROJECT_NAME} checkers_engine checkers_agents ${wxWidgets_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Applications")

add_subdirectory(google_tests)

