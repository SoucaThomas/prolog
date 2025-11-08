cmake_minimum_required(VERSION 3.16)
project(PrologCppInterpreter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include headers
include_directories(include)

# Main executable
add_executable(prolog_interpreter
    src/main.cpp
    src/interpreter.cpp
    src/parser.cpp
    src/lexer.cpp
    src/utils.cpp
)

# Enable testing
enable_testing()
add_subdirectory(test)