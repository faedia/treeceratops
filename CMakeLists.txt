cmake_minimum_required(VERSION 3.22)

project(
    treeceratops
    VERSION 0.1
    DESCRIPTION "Generic Tree Library"
    LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
    endif()

    set(CMAKE_CXX_STANDARD 20)

    include(CTest)
endif()

include(FetchContent)

add_library(treeceratops INTERFACE)
target_include_directories(treeceratops INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS treeceratops EXPORT treeceratops-target
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
export(TARGETS treeceratops NAMESPACE treeceratops::
    FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR LOXT_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(test)
endif()
