cmake_minimum_required(VERSION 3.5)

project(example
  VERSION 0.1.0
  LANGUAGES CXX
)

configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/RapidJSON-CMakeLists.txt.in
  ${CMAKE_BINARY_DIR}/rapidjson-download/CMakeLists.txt
)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/rapidjson-download
)

if(result)
  message(FATAL_ERROR "CMake step for rapidjson failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/rapidjson-download
)

if(result)
  message(FATAL_ERROR "Build step for rapidjson failed: ${result}")
endif()

add_subdirectory(
  ${CMAKE_BINARY_DIR}/rapidjson-src
  ${CMAKE_BINARY_DIR}/rapidjson-build
  EXCLUDE_FROM_ALL
)

add_executable(example src/main.cc)
target_compile_features(example PRIVATE cxx_auto_type)

find_package(funcxxy 1.0 REQUIRED)
find_package(rapidjson 1.1 REQUIRED)
add_library(RapidJSON::RapidJSON INTERFACE IMPORTED)
set_target_properties(RapidJSON::RapidJSON PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${RapidJSON_INCLUDE_DIRS}"
)
target_link_libraries(example funcxxy::funcxxy RapidJSON::RapidJSON)
