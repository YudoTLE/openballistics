cmake_minimum_required(VERSION 4.2)

project(
    openballistics_core
    VERSION 0.0.7
    LANGUAGES CXX
)

find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)

add_library(openballistics_core INTERFACE)

target_sources(openballistics_core INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/openballistics.hpp
)

target_link_libraries(openballistics_core INTERFACE
    Boost::boost
    Eigen3::Eigen
)

target_compile_features(openballistics_core INTERFACE cxx_std_17)
