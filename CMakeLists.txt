cmake_minimum_required(VERSION 3.0.0)
project(3 VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SOURCES src/*.cpp)
add_executable(5 ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
