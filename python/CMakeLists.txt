cmake_minimum_required(VERSION 4.2)

project(openballistics_python LANGUAGES CXX)

find_package(Python 3.9
    REQUIRED COMPONENTS Interpreter Development.Module
    OPTIONAL_COMPONENTS Development.SABIModule
)

execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT
)
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(_core
    STABLE_ABI
    NB_STATIC
    src/bindings.cpp
)

target_link_libraries(_core PRIVATE openballistics_core)

install(TARGETS _core LIBRARY DESTINATION openballistics)

nanobind_add_stub(
    _core_stub
    MODULE _core
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/openballistics/_core.pyi
    PYTHON_PATH $<TARGET_FILE_DIR:_core>
    DEPENDS _core
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/openballistics/py.typed DESTINATION openballistics)
