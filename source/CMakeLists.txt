# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                                                 #
#   Voltam CMake Configuration                                                                    #
#                                                                                                 #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required(VERSION 2.6)
project(voltam)



#
# --- Packages ---
#

# Add the PkgConfig package to find packages that CMake doesn't.
find_package(PkgConfig)

# gtkmm
pkg_check_modules(GTKMM gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})

# Boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

# Lua
find_package(Lua51)
include_directories(${LUA_INCLUDE_DIR})

# luabind
pkg_check_modules(LUABIND luabind)
include_directories(${LUABIND_INCLUDE_DIRS})



#
# --- Executable ---
#

# List Sources
set(sources
	main.cpp
	
	smartpointer.cpp
	
	# Geometry
	geometry/bezierpath/bezierpath.cpp
	geometry/bezierpath/invocation.cpp
)

# Setup Executable
add_executable(
	voltam
	${sources}
)
target_link_libraries(
	voltam
	${GTKMM_LIBRARIES}
	${LUA_LIBRARIES}
	${LUABIND_LIBRARIES}
)

