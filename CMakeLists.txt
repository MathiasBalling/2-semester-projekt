cmake_minimum_required(VERSION 3.26)
project(wx-example)

Set(CMAKE_CXX_STANDARD 11)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

find_package(libmodbus)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(drawing ${SRC_FILES})
include_directories(include)
target_link_libraries(drawing ${wxWidgets_LIBRARIES})

target_link_libraries(drawing ${libmodbus_LIBRARIES})
