cmake_minimum_required(VERSION 2.6)
project(Voltam)

# default to debug build type
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif ()


# Debugging definitions.
if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions("-DBUILD_DEBUG")
endif()

# gather source files
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} source/*.cpp)

# add executable
set(exec_name voltam)
add_executable(${exec_name} ${sources})


###  Packages and Libraries
###  ======================

find_package(PkgConfig)

# ObjectiveLua
include_directories  (thirdparty/objectivelua/include)

# Lua51
find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
target_link_libraries(${exec_name} ${LUA_LIBRARY})

# garbage collector
pkg_check_modules(GC bdw-gc)
link_directories     (${GC_LIBRARY_DIRS})
include_directories  (${GC_INCLUDE_DIRS})
target_link_libraries(${exec_name} ${GC_LIBRARIES})

# gtkmm
pkg_check_modules(GTKMM gtkmm-3.0)
if (NOT GTKMM_FOUND)
	pkg_check_modules(GTKMM gtkmm-2.4)
endif()
link_directories     (${GTKMM_LIBRARY_DIRS})
include_directories  (${GTKMM_INCLUDE_DIRS})
target_link_libraries(${exec_name} ${GTKMM_LIBRARIES})
