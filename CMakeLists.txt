cmake_minimum_required(VERSION 3.5)

project(funcxxy
  VERSION 1.0.0
  LANGUAGES CXX
)

add_library(funcxxy
  src/funcxxy.cc
)

target_include_directories(funcxxy
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(funcxxy::funcxxy ALIAS funcxxy)

target_compile_features(funcxxy PRIVATE cxx_auto_type)
target_compile_options(funcxxy PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/funcxxy)

install(TARGETS funcxxy
  EXPORT funcxxy-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT funcxxy-targets
  FILE
    funcxxyTargets.cmake
  NAMESPACE
    funcxxy::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/funcxxyConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/funcxxyConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/funcxxyConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/funcxxyConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/funcxxyConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT funcxxy-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/funcxxyTargets.cmake
  NAMESPACE funcxxy::
)

export(PACKAGE funcxxy)

add_subdirectory(test)
