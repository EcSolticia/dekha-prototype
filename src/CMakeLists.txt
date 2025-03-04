cmake_minimum_required(VERSION 3.28.3)

Project(Dekha)

add_executable(${PROJECT_NAME} main.cpp node/node.cpp node/polygon.cpp node/camera.cpp)