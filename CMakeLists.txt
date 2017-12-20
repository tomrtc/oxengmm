#
# Main CMakelists for the oxengmm project.
#
# Project specific options :
#   - OXENGMM_USE_DOXYGEN
#   - OXENGMM_BUILD_TESTS (requires BUILD_TESTING set to ON)
# Other options might be available through the cmake scripts including (not exhaustive):
#   - ENABLE_WARNINGS_SETTINGS
#   - ENABLE_LTO
#
cmake_minimum_required(VERSION 3.9)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR
    "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()


project(oxengmm C CXX)


# Standard CMake modules

# Must be called before adding tests but after calling project().
#This automatically calls enable_testing() and configures ctest targets when using Make/Ninja
include(CTest)


# This is a really useful scripts that creates options that depends on other options.
# It can even be used with generator expressions !
include(CMakeDependentOption)

# Custom modules and scripts

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(LTO)
include(Warnings)
#include(CopyDllsForDebug)
#include(Coverage)

# options

option(OXENGMM_USE_DOXYGEN "Add a doxygen target to generate the documentation" ON)

# Use your own option for tests, in case people use your library through add_subdirectory
cmake_dependent_option(OXENGMM_BUILD_TESTS
  "Enable oxengmm project tests targets" ON # By default we want tests if CTest is enabled
  "BUILD_TESTING" OFF # Stay coherent with CTest variables
  )

# External dependencies
add_subdirectory(external EXCLUDE_FROM_ALL)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################

# Check for LTO support (needs to be after project(...) )
find_lto(CXX)

#==========================#
#  oxengmm executable  #
#==========================#
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 1)
set(TARGET_VERSION_PATCH 2)
set_property(GLOBAL PROPERTY VERSION    ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
# Define some variables
set(OXENGMM_PROJECT_PATH 		        ${CMAKE_SOURCE_DIR})
set(OXENGMM_SOURCE_directory 		${CMAKE_CURRENT_SOURCE_DIR})

set(OXENGMM_INCLUDES_DIRECTORIES 	PRIVATE ${OXENGMM_SOURCE_DIR})
set(OXENGMM_COMPILE_DEFINITIONS 	PRIVATE -DOXENGMM_VERSION=${VERSION})
set(OXENGMM_LINK_LIBRARIES          PRIVATE                  # The following libraries are only linked for this target.
  m general fmt spdlog
  # It is possible to link some libraries for debug
  #or optimized builds only
  #debug DEBUGLIBS
  #optimized RELEASELIBS
  )

if(UNIX)
  find_package(PkgConfig 	REQUIRED)
  find_package(Threads 	REQUIRED)

  pkg_check_modules(GTKMM gtkmm-3.0)

  list(APPEND OXENGMM_INCLUDES_DIRECTORIES
    PRIVATE ${GTKMM_INCLUDE_DIRS})

  list(APPEND OXENGMM_LINK_LIBRARIES

    PRIVATE dl
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    PRIVATE ${GTKMM_LIBRARIES}

    )
endif()

set(OXENGMM_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/source/mainwindow.cc
  ${CMAKE_SOURCE_DIR}/source/icon.cc
  ${CMAKE_SOURCE_DIR}/source/main.cc)

# In this case we don't have headers, but always list them so that they appear in the IDE
set(OXENGMM_INCLUDE_FILES )

add_executable(oxengmm ${OXENGMM_SOURCE_FILES} ${BOILERPLATE_INCLUDE_FILES})
# Require c++14, this is better than setting CMAKE_CXX_STANDARD since it won't pollute other targets
# note : cxx_std_* features were added in CMake 3.8.2
target_compile_features(oxengmm PRIVATE cxx_std_14)
target_compile_definitions(oxengmm 	${OXENGMM_COMPILE_DEFINITIONS})
target_include_directories(oxengmm 	${OXENGMM_INCLUDES_DIRECTORIES})
target_link_libraries(oxengmm	${OXENGMM_LINK_LIBRARIES})
# CMake scripts extensions
target_set_warnings(oxengmm ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Helper that can set default warning flags for you
target_enable_lto(oxengmm optimized) #enable lto if available for non-debug configurations





#copy_dlls_for_debug(oxengmm "" "") # Copy dependencies next to the executable (DLLs for example)

# Setup our project as the startup project for Visual so that people don't need to do it manually
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT oxengmm)

#   Tests   #

if(OXENGMM_BUILD_TESTS)
  # Let the user add options to the test runner if needed
  set(TEST_RUNNER_PARAMS "--force-colors=true" CACHE STRING "Options to add to our test runners commands")
  # In a real project you most likely want to exclude test folders
  # list(APPEND CUSTOM_COVERAGE_EXCLUDE "/test/")
  add_subdirectory(tests)
  # You can setup some custom variables and add them to the CTestCustom.cmake.in template to have custom ctest settings
  # For example, you can exclude some directories from the coverage reports such as third-parties and tests
  configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/CTestCustom.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CTestCustom.cmake
    @ONLY
    )
endif()


## Doxygen ##


if(OXENGMM_USE_DOXYGEN AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.9)
  find_package(Doxygen
    OPTIONAL_COMPONENTS dot mscgen dia
    )
  if(DOXYGEN_FOUND)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    doxygen_add_docs(
      doc
      README.md source
      COMMENT "Generate man pages"
      )
  endif()
endif()
