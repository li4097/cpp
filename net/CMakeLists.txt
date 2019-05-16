cmake_minimum_required(VERSION 2.8)
project(ObjTest)

set(CMAKE_CXX_COMPILER g++)
add_compile_options(-std=c++11 -g -Wall)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory( ${SRC_DIR}/utility)
add_subdirectory( ${SRC_DIR}/mythread)
add_subdirectory( ${SRC_DIR}/net)

include_directories(
	${SRC_DIR}/utility
	${SRC_DIR}/thread
	${SRC_DIR}/net
	)

add_executable(main ${SRC_DIR}/main.cpp)
target_link_libraries(main  Utility MyThread MyNet)
