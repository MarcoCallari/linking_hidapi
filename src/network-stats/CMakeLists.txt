cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#add_definitions(-DHAVE_STDINT_H)
include (${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/includenetsnmp.cmake)
include_directories(${NET_SNMP_INCLUDE_DIR})
set(PROJECT_SRC
"main.cpp"
"node.cpp"
"node.hpp"
"type.hpp"
"type.cpp"
)
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
message(status "${NET_SNMP_LIBRARIES}")

if (WIN32)
  target_link_libraries (${PROJECT_NAME} ${NET_SNMP_LIBRARIES} wsock32 ws2_32)
endif (WIN32)

# if (UNIX)
#   #TODO
# endif (UNIX)
