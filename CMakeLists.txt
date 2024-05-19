cmake_minimum_required(VERSION 3.5)
project(GeneticAlgo CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_C_LINKER_FLAGS “-g -Wall -Werror”)

add_executable(${PROJECT_NAME} src/main.cpp)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} genetic libCrossover libMutation
                      libSelection)
