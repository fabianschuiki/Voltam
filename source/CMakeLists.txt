cmake_minimum_required(VERSION 2.6)
project(Voltam)

# default to debug build type
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif ()

# gather source files
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} *.cpp)

# add executable
set(exec_name voltam)
add_executable(${exec_name} ${sources})


#  Libraries
#  #########

find_package(PkgConfig)

pkg_check_modules(GC bdw-gc)
link_directories     (${GC_LIBRARY_DIRS})
include_directories  (${GC_INCLUDE_DIRS})
target_link_libraries(${exec_name} ${GC_LIBRARIES})

pkg_check_modules(GTKMM gtkmm-3.0)
link_directories     (${GTKMM_LIBRARY_DIRS})
include_directories  (${GTKMM_INCLUDE_DIRS})
target_link_libraries(${exec_name} ${GTKMM_LIBRARIES})
