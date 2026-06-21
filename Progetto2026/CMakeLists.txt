cmake_minimum_required(VERSION 3.20)
project(progetto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 REQUIRED)

add_executable(main main_circuito.cpp)

target_link_libraries(main PRIVATE Eigen3::Eigen)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/netlist.txt
    ${CMAKE_CURRENT_BINARY_DIR}/netlist.txt
    COPYONLY
)