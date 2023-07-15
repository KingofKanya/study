cmake_minimum_required(VERSION 3.25)
project(Employee_Managerment_System)

set(CMAKE_CXX_STANDARD 23)

add_executable(Employee_Managerment_System main.cpp workerManager.h boss.h employee.h manager.h worker.h boss.cpp employee.cpp manager.cpp workerManager.cpp)
