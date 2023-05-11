cmake_minimum_required(VERSION 3.26)

project(NBNP-Chess)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 8)

find_package(PkgConfig)
    pkg_check_modules(libmodbus REQUIRED IMPORTED_TARGET libmodbus)
    if(libmodbus_FOUND)
        message(STATUS "Found libmodbus CFLAGS: ${libmodbus_CFLAGS}")
        message(STATUS "Found libmodbus LDFLAGS: ${libmodbus_LDFLAGS}")
    else()
        message(STATUS "Libmodbus not found")
    endif()

find_package(wxWidgets REQUIRED net gl core base)
    if(wxWidgets_USE_FILE) # not defined in CONFIG mode
        include(${wxWidgets_USE_FILE})
    endif()
    if(wxWidgets_FOUND)
        message(STATUS "Found wxWidgets CXXFLAGS: ${wxWidgets_CXX_FLAGS}")
        message(STATUS "Found wxWidgets LDFLAGS: ${wxWidgets_LIBRARIES}")
    else()
        message(STATUS "wxWidgets not found")  
    endif()
message(STATUS "${wxWidgets_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${libmodbus_CFLAGS} ${wxWidgets_CXX_FLAGS}")

include_directories(include)
include_directories(external)
file(GLOB SRC_FILES 
src/*.cpp
include/*.h
external/*.cpp
external/*.h
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${libmodbus_LDFLAGS})