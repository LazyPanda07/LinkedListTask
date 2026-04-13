cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(GOOGLE_TEST_TAG v1.17.0)

project(Tests)

add_executable(
	${PROJECT_NAME}
	src/main.cpp
)

include(FetchContent)

FetchContent_Declare(
	gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG ${GOOGLE_TEST_TAG}
)

FetchContent_MakeAvailable(gtest)

target_link_libraries(
	${PROJECT_NAME}
	GTest::gtest
	GTest::gtest_main
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/../assets/ DESTINATION .)

if (UNIX)
	install(FILES ${CMAKE_SOURCE_DIR}/../LinkedList/LinkedListTask DESTINATION . PERMISSIONS OWNER_EXECUTE)

	add_definitions(-D__LINUX__)
else()
	install(FILES ${CMAKE_SOURCE_DIR}/../LinkedList/LinkedListTask.exe DESTINATION .)
endif()
