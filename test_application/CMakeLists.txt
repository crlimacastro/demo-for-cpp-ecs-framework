cmake_minimum_required(VERSION 3.13)

project(test_application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	PRIVATE
	fae_framework
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
	PRIVATE
	fae_framework
)

# target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH=${CMAKE_CURRENT_SOURCE_DIR}/resources)
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/fae_framework/src/)
# target_link_libraries(${PROJECT_NAME} PRIVATE fae_framework)
# file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# target_sources(${PROJECT_NAME} PRIVATE ${SRCS})