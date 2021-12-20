include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(othello main.cpp helper.cpp game.cpp board.cpp)

add_custom_target(run COMMAND othello)

#target_link_libraries(opengljet GL glfw GLU) 
