# A Reversi/Othello Clone

## Requirements:

- C++11 (although with minor modifications to "src/CMakeLists.txt" this is likely not true)
- CMake
- SDL2

This may only build on Unix... I've only tested on Arch Linux

## Building:

        cd build

        cmake ../

        cmake --build ./ 
        OR 
        cmake --build ./ --target run 

## Command line parameters:

        Usage:                          
           ./othello [options]           
         Options:                        
           -t       Text mode            
           -d       Disable move hints   
           -h, -?   Print this screen    

## Todo:

- [x] Grahpics
- [ ] Cross-platform networking
- [ ] AI