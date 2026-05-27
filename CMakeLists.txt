cmake_minimum_required(VERSION 3.16)
project(QtCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtCalculator main.cpp)
target_link_libraries(QtCalculator PRIVATE Qt6::Widgets)

install(TARGETS QtCalculator RUNTIME DESTINATION bin)
