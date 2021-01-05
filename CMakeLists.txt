cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
project(SSVM)
find_package(Boost 1.45.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(.)
    add_library(
        libssvm OBJECT
        ./loader/loader.cpp
        ./loader/ldmgr.cpp
        ./loader/filemgr.cpp
        ./ast/expression.cpp
        ./ast/segment.cpp
        ./ast/module.cpp
        ./ast/instruction.cpp
        ./ast/section.cpp
        ./ast/type.cpp
        ./ast/description.cpp
        ./interpreter/instantiate/memory.cpp
        ./interpreter/instantiate/data.cpp
        ./interpreter/instantiate/elem.cpp
        ./interpreter/instantiate/module.cpp
        ./interpreter/instantiate/import.cpp
        ./interpreter/instantiate/function.cpp
        ./interpreter/instantiate/table.cpp
        ./interpreter/instantiate/global.cpp
        ./interpreter/instantiate/export.cpp
        ./interpreter/interpreter.cpp
        ./interpreter/engine/memory.cpp
        ./interpreter/engine/control.cpp
        ./interpreter/engine/provider.cpp
        ./interpreter/engine/engine.cpp
        ./interpreter/engine/variable.cpp
        ./validator/validator.cpp
        ./validator/formchecker.cpp
        ./main.cpp
        ./vm/vm.cpp
        ./support/log.cpp
        ./support/hexstr.cpp
    )
    target_link_libraries(libssvm ${Boost_LIBRARIES})
    target_link_libraries(libssvm dl)
endif()
