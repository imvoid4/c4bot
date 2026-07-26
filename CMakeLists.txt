cmake_minimum_required(VERSION 3.20)

project(c4bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_executable(c4bot
    main.cpp
)

target_include_directories(c4bot PRIVATE
    include
)

target_link_libraries(c4bot PRIVATE
    raylib
    OpenGL::GL
)
