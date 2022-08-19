cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

project(game)
add_executable(game GameDriver.cpp Player.cpp Resources.cpp MapVG.cpp MapGB.cpp MapVGLoader.cpp MapGBLoader.cpp GameObservers.cpp Graph/Graph.cpp Graph/Node.cpp)