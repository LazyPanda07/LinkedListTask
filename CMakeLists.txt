cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
option(WITH_ASSETS "Also install inlet.in" ON)

project(LinkedListTask)

add_executable(
	${PROJECT_NAME}
	src/main.cpp
	src/LinkedList.cpp
)

target_include_directories(
	${PROJECT_NAME} PRIVATE
	include
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)

if (${WITH_ASSETS})
	install(DIRECTORY assets/ DESTINATION .)
endif()
