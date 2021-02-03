project(win_service)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -O3 -Wall")

set(WIN_SERVICE_SRC 
    main.cpp 
    win_service.cpp
    win_service.h
    parse_ini.cpp
    parse_ini.h)

#include_directories()
#link_directories()
add_executable(win_service ${WIN_SERVICE_SRC})
#target_link_libraries(win_service )


