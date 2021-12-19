cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(othello VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(othello main.cpp helper.h game.h)

add_custom_target(run COMMAND othello)

#target_link_libraries(opengljet GL glfw GLU) 
