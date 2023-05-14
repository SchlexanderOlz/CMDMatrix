cmake_minimum_required(VERSION 3.5)
project(matrix)

# Find the ncurses library
find_package(Curses REQUIRED)

# Set the source files for your program
set(SOURCES src/matrix.c)

# Create the executable and link against the ncurses library
add_executable(matrix ${SOURCES})
target_link_libraries(matrix ${CURSES_LIBRARIES})
