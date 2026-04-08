cmake_minimum_required(VERSION 3.0...4.0)
include(FetchContent)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(PROJECT_NAME Core)
project(${PROJECT_NAME})

FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb
)

FetchContent_MakeAvailable(stb)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-D_DEBUG)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_definitions(-D_RELEASE) 
endif()

set(PROCESSOR_ARHITECTURE_TYPE "UNKNOWN")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PROCESSOR_ARHITECTURE_TYPE "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PROCESSOR_ARHITECTURE_TYPE "x32")
else()
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" LOWER_CASE_PROC)

    if(${LOWER_CASE_PROC} STREQUAL "arm" OR ${LOWER_CASE_PROC} STREQUAL "aarch64")
        set(PROCESSOR_ARHITECTURE_TYPE "ARM")
    elseif(${LOWER_CASE_PROC} STREQUAL "powerpc" OR ${LOWER_CASE_PROC} STREQUAL "ppc64le")
        set(PROCESSOR_ARHITECTURE_TYPE "PowerPC")
    elseif(${LOWER_CASE_PROC} STREQUAL "mips" OR ${LOWER_CASE_PROC} STREQUAL "mipsel")
        set(PROCESSOR_ARHITECTURE_TYPE "MIPS")
    elseif(${LOWER_CASE_PROC} STREQUAL "riscv64")
        set(PROCESSOR_ARHITECTURE_TYPE "RISC-V 64-bit")
    else()
        message(ERROR "Unrecognized processor type: ${CMAKE_SYSTEM_PROCESSOR}. Setting PROCESSOR_ARHITECTURE_TYPE to Unknown.")
    endif()
endif()

message(STATUS "Building for architecture: ${PROCESSOR_ARHITECTURE_TYPE}, build type: ${CMAKE_BUILD_TYPE}")

# Custom cleanup target
add_custom_target(C_CLEANUP
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}/lib"
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}/bin"
    COMMENT "Cleaning output directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}"
)

set(HEADER_FILES 
    ${CMAKE_SOURCE_DIR}/include/FileReader.hpp
    ${CMAKE_SOURCE_DIR}/include/MinMax.hpp
    ${CMAKE_SOURCE_DIR}/include/Color.hpp
    ${CMAKE_SOURCE_DIR}/include/Base.hpp
    ${CMAKE_SOURCE_DIR}/include/Renderer.hpp
    ${CMAKE_SOURCE_DIR}/include/Window.hpp
    ${CMAKE_SOURCE_DIR}/include/Uniform.hpp
    ${CMAKE_SOURCE_DIR}/include/VertexShader.hpp
    ${CMAKE_SOURCE_DIR}/include/FragmentShader.hpp
    ${CMAKE_SOURCE_DIR}/include/Shader.hpp
    ${CMAKE_SOURCE_DIR}/include/IndexBuffer.hpp
    ${CMAKE_SOURCE_DIR}/include/VertexBuffer.hpp
    ${CMAKE_SOURCE_DIR}/include/VertexBufferLayout.hpp
    ${CMAKE_SOURCE_DIR}/include/VertexArray.hpp
    ${CMAKE_SOURCE_DIR}/include/Texture.hpp
)

set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/FileReader.cpp
    ${CMAKE_SOURCE_DIR}/src/Color.cpp
    ${CMAKE_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/Window.cpp
    ${CMAKE_SOURCE_DIR}/src/Uniform.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexShader.cpp
    ${CMAKE_SOURCE_DIR}/src/FragmentShader.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/IndexBuffer.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexBuffer.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexBufferLayout.cpp
    ${CMAKE_SOURCE_DIR}/src/VertexArray.cpp
    ${CMAKE_SOURCE_DIR}/src/Texture.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}/bin"
    PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROCESSOR_ARHITECTURE_TYPE}/bin"
)