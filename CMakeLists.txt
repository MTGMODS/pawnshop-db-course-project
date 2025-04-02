cmake_minimum_required(VERSION 3.28)
project(course)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(course main.cpp
        Client.cpp
        Client.h
        Item.cpp
        Item.h
        Pawnshop.cpp
        Pawnshop.h
        Menu.cpp
        Menu.h
)



