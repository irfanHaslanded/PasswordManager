project (Test_PasswordManager)

# where is your gtest installed?
set(CMAKE_LIBRARY_PATH $HOME/install/lib)
set(CMAKE_INCLUDE_PATH $HOME/install/include)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Test_Utilities TestUtilities.cpp)
target_link_libraries(Test_Utilities
	${GTEST_BOTH_LIBRARIES} pthread crypto crypt
	)

add_test(Test_Utilities Test_Utilities)

add_executable(Test_UserData TestUserData.cpp 
	../Utilities.cpp
)
target_link_libraries(Test_UserData
	${GTEST_BOTH_LIBRARIES} pthread crypto crypt
	)

add_test(Test_UserData Test_UserData)


add_executable(Test_Users TestUsers.cpp 
	../Utilities.cpp
	../UserData.cpp
)
target_link_libraries(Test_Users
	${GTEST_BOTH_LIBRARIES} pthread crypto crypt
	)


add_test(NAME Test_Users COMMAND Test_Users --gtest_output=xml)

add_custom_target(test 
					DEPENDS Test_Users Test_UserData Test_Utilities
                   COMMAND ctest -V )


