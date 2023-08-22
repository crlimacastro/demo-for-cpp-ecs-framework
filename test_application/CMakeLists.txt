cmake_minimum_required(VERSION 3.13)

project(test_application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRCS "src/*.cpp")
add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC
	PRIVATE
	fae_framework
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	PRIVATE
	fae_framework
)