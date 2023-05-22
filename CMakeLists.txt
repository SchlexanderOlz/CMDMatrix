cmake_minimum_required(VERSION 3.5)
project(matrix)

find_package(Curses REQUIRED)

set(SOURCES src/matrix.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(matrix ${SOURCES})
target_link_libraries(matrix ${CURSES_LIBRARIES})

set_target_properties(matrix PROPERTIES OUTPUT_NAME "matrix")

if (WIN32)
  set_target_properties(matrix PROPERTIES SUFFIX ".exe")
endif (WIN32)