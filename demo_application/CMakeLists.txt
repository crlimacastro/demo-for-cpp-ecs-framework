cmake_minimum_required(VERSION 3.13)

project(demo_application VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRCS "src/*.cpp")
add_executable(${PROJECT_NAME} src/main.cpp)

add_custom_target(${PROJECT_NAME}_copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E
	copy_directory "${fae_framework_BINARY_DIR}/resources" "${PROJECT_BINARY_DIR}/resources"
	COMMENT "Copying ${fae_framework_BINARY_DIR}/resources to ${PROJECT_BINARY_DIR}/resources"
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_copy_resources)
add_dependencies(${PROJECT_NAME}_copy_resources fae_framework_copy_resources)

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