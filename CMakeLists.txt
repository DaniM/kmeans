cmake_minimum_required(VERSION 2.6)

project (kmeans)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(kmeans src/main.cpp src/kmeans.cpp src/csvparser.cpp src/wingetopt.c)

include_directories(include)