# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                             #
#   Voltam Tests                                                              #
#                                                                             #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Attributes 

add_executable(
	attributes
	
	attribute/list.cpp
	misc/smartpointer.cpp
	tests/attributes.cpp
)
target_link_libraries(
	attributes
)
