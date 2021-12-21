include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(othello main.cpp game.cpp board.cpp)

add_custom_target(run COMMAND othello)
