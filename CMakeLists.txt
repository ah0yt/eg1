cmake_minimum_required(VERSION 3.25)
project("sdl2"
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add additional source files here
set(SOURCE_FILES main.cpp)

# find SDL2_LIBRARY
find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 )
