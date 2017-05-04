cmake_minimum_required(VERSION 3.6)
project(Petris)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

file(GLOB SOURCE_FILES
    "src/*.h"
    "src/*.cpp"
    "src/imgui-sfml/*.h"
    "src/imgui-sfml/*.cpp"
    )
add_executable(Petris src/main.cpp ${SOURCE_FILES})

set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/SFML")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.4.2 REQUIRED audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Petris ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()