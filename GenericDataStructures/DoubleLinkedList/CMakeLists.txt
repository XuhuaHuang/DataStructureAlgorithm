cmake_minimum_required(VERSION 3.20)

project("GenericDoubleLinkedList" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable("GenericDoubleLinkedList"
    "denode.hpp"
    "denode.cpp"
    "main.cpp"
)
