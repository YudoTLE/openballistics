cmake_minimum_required(VERSION 4.2)

project(
    openballistics_core
    VERSION 0.0.9
    LANGUAGES CXX
)

find_package(Eigen3 3.4 QUIET)

if(NOT Eigen3_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Eigen3
        URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
    )
    FetchContent_MakeAvailable(Eigen3)

    if(NOT TARGET Eigen3::Eigen)
        add_library(Eigen3::Eigen ALIAS eigen)
    endif()
endif()

add_library(openballistics_core INTERFACE)

target_sources(openballistics_core INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/openballistics.hpp
)

target_link_libraries(openballistics_core INTERFACE
    Eigen3::Eigen
)

target_compile_features(openballistics_core INTERFACE cxx_std_17)