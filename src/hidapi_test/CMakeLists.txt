cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SRC
"main.cpp")
include (${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/FindHIDAPI.cmake)
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_link_libraries(hidapi_test HIDAPI::hidapi)
