# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                                                 #
#   Voltam CMake Configuration                                                                    #
#                                                                                                 #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required(VERSION 2.6)
project(voltam)

# Find Packages
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)
pkg_check_modules(GNOMEMM gnome-vfsmm-2.6)


# List Sources
set(sources
	main.cpp
)


# Setup Linking
link_directories(
	${GTKMM_LIBRARY_DIRS}
)
include_directories(
	${GTKMM_INCLUDE_DIRS}
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

