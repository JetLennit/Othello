# A Reversi/Othello Clone

## Requirements:

- C++11 (although with minor modifications to "src/CMakeLists.txt" other versions should work)
- CMake
- SDL2

This may only build on Linux... I've only tested on Arch Linux.

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

- [x] Graphics
- [ ] Cross-platform networking
- [ ] AI