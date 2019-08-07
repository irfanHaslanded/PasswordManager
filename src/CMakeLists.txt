cmake_minimum_required (VERSION 2.6)

# Use C++ 11
set (CMAKE_CXX_STANDARD 11)

# Force the use of gcc and g++ and not cc which might be older
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project (PasswordManager)

file(GLOB PasswordManager_Sources *.cpp) # all cpp files in the src directory
add_executable(PasswordManager ${PasswordManager_Sources})

target_link_libraries(PasswordManager
	crypto crypt
)

add_subdirectory(test
	EXCLUDE_FROM_ALL # Make subdir test only if 'make test' not for 'make' or 'make all'
)
