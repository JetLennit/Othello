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
           -c <ip>  Connect to host at ip
           -s       Host server          
           -h, -?   Print this screen    