cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0072 NEW)
cmake_policy(SET CMP0135 NEW)
cmake_policy(SET CMP0148 NEW)

set(PROJECT_NAME CatalystAD)
project(${PROJECT_NAME})

# Configure CMake constants
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=maybe-uninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

# Add the submodules
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
add_subdirectory(external/gtest)
add_subdirectory(external/glad/cmake)
#add_subdirectory(external/stb)

# Find required packages
find_package(TBB REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCASCADE COMPONENTS FoundationClasses REQUIRED)
find_package(OpenCASCADE COMPONENTS ModelingData REQUIRED)
find_package(OpenCASCADE COMPONENTS DataExchange REQUIRED)

# Configure all the include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OpenCASCADE_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# NOTE: Globbing will disable automatic rebuild of make when adding new files
file(GLOB ROOT_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SRC_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")
list(REMOVE_ITEM ROOT_CPP_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp ${ROOT_CPP_FILES} ${SRC_CPP_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.h")
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    # ${TBB_LIBRARIES}
    ${OpenCASCADE_LIBRARIES}
    OpenGL::GL
    gtest_main
    glfw
)

# Build the tests
enable_testing()
include(GoogleTest)

add_definitions(-DUSING_GTEST)
add_executable(runUnitTests ${ROOT_CPP_FILES} ${SRC_CPP_FILES})
target_precompile_headers(runUnitTests PRIVATE "src/pch.h")
target_link_libraries(runUnitTests
    OpenGL::GL
    ${OpenCASCADE_LIBRARIES}
    gtest_main
    gtest
    glfw
)

gtest_discover_tests(runUnitTests)
