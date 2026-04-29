cmake_minimum_required(VERSION 3.28)
project(mini-htop)

#find and include ncurses package
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_subdirectory(lib)


add_executable(${PROJECT_NAME} main.c)
#add_library(mylib lib.cpp)

target_link_libraries(${PROJECT_NAME} mylib ${CURSES_LIBRARIES} m)

