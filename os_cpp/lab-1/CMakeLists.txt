
cmake_minimum_required(VERSION 3.17.0)

project(rCore)

set(CMAKE_CXX_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcmodel=medany")
set(CMAKE_CXX_LINK_EXECUTABLE "riscv64-unknown-elf-ld -T ${CMAKE_SOURCE_DIR}/linker.ld <OBJECTS> -o <TARGET>.out")

file(GLOB_RECURSE SOURCES
    ./*.h
    ./*.cpp)

add_executable(rCore
    ${SOURCES}
)
target_include_directories(
    rCore PRIVATE ./
)
