cmake_minimum_required(VERSION 3.16)

project(core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- libcore.a ---
add_library(core STATIC
    libcore.cpp
    libcore.h
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
