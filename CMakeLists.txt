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
    include_directories(include)
    add_library(
        libssvm OBJECT
        lib/loader/loader.cpp
        lib/loader/ldmgr.cpp
        lib/loader/filemgr.cpp
        lib/ast/expression.cpp
        lib/ast/segment.cpp
        lib/ast/module.cpp
        lib/ast/instruction.cpp
        lib/ast/section.cpp
        lib/ast/type.cpp
        lib/ast/description.cpp
        lib/interpreter/instantiate/memory.cpp
        lib/interpreter/instantiate/data.cpp
        lib/interpreter/instantiate/elem.cpp
        lib/interpreter/instantiate/module.cpp
        lib/interpreter/instantiate/import.cpp
        lib/interpreter/instantiate/function.cpp
        lib/interpreter/instantiate/table.cpp
        lib/interpreter/instantiate/global.cpp
        lib/interpreter/instantiate/export.cpp
        lib/interpreter/interpreter.cpp
        lib/interpreter/engine/memory.cpp
        lib/interpreter/engine/control.cpp
        lib/interpreter/engine/provider.cpp
        lib/interpreter/engine/engine.cpp
        lib/interpreter/engine/variable.cpp
        lib/validator/validator.cpp
        lib/validator/formchecker.cpp
        lib/vm/vm.cpp
        lib/support/log.cpp
        lib/support/hexstr.cpp
    )
    target_link_libraries(libssvm ${Boost_LIBRARIES})
    target_link_libraries(libssvm dl)
endif()
