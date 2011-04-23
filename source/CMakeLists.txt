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
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

# Boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})



#
# --- Executable ---
#

# List Sources
set(sources
	main.cpp
	
	# Symbol
	#symbol/symbol.cpp
	symbol/manager.cpp
	symbol/generator.cpp
	symbol/generatormanager.cpp
)

# Setup Executable
add_executable(
	voltam
	${sources}
)
target_link_libraries(
	voltam
	${GTKMM_LIBRARIES}
)

