cmake_minimum_required(VERSION 3.21.3)
project(untitled)

set(BOOST_ROOT "C:\\boost_1_77_0") # either set it here or from the command line
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS) # header only libraries must not be added here

add_executable(server server.cpp)
add_executable(client client.cpp)
target_include_directories(server PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(server ${Boost_LIBRARIES})
target_include_directories(client PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(client ${Boost_LIBRARIES})
