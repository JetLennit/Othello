include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(SDL2 REQUIRED)
include_directories(othello ${SDL2_INCLUDE_DIRS})

add_executable(othello main.cpp game.cpp board.cpp)

target_link_libraries(othello ${SDL2_LIBRARIES})
target_compile_options(othello PRIVATE -Werror -Wall -Wextra)

add_custom_target(run COMMAND othello)
