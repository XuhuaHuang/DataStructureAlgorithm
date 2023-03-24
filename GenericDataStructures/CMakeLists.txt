cmake_minimum_required(VERSION 3.20)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘
project(GenericDataStructure
    VERSION 1.0.0
    DESCRIPTION "Generic Data Structure using C++ template"
    LANGUAGES CXX
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  CXX Standard Requirements                                       │
# └──────────────────────────────────────────────────────────────────┘
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Sub-directories with CMake                                      │
# └──────────────────────────────────────────────────────────────────┘
add_subdirectory("DoubleLinkedList")
add_subdirectory("LinkedList")
