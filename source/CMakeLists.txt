cmake_minimum_required(VERSION 2.6)
project(Voltam)

# default to debug build type
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif ()

# gather source files
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} *.cpp)

# add executable
set(EXECUTABLE_NAME voltam)
add_executable(${EXECUTABLE_NAME} ${sources})
