cmake_minimum_required(VERSION 3.6)
project(Rez_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(Rez_CPP ${SOURCE_FILES})

configure_file(${CMAKE_SOURCE_DIR}/example.in ${CMAKE_CURRENT_BINARY_DIR}/example.in COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/example.out ${CMAKE_SOURCE_DIR}/example.out)

configure_file(${CMAKE_SOURCE_DIR}/input.in ${CMAKE_CURRENT_BINARY_DIR}/input.in COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/output.out ${CMAKE_SOURCE_DIR}/output.out)

configure_file(${CMAKE_SOURCE_DIR}/small.in ${CMAKE_CURRENT_BINARY_DIR}/small.in COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/small.out ${CMAKE_SOURCE_DIR}/small.out)

configure_file(${CMAKE_SOURCE_DIR}/medium.in ${CMAKE_CURRENT_BINARY_DIR}/medium.in COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/medium.out ${CMAKE_SOURCE_DIR}/medium.out)

configure_file(${CMAKE_SOURCE_DIR}/big.in ${CMAKE_CURRENT_BINARY_DIR}/big.in COPYONLY)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/big.out ${CMAKE_SOURCE_DIR}/big.out)
