cmake_minimum_required(VERSION 3.20)

if(WIN32)
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Debug>:MultiThreadedDebug>$<$<CONFIG:Release>:MultiThreaded>")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GeoEngine)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory("libs/glfw")
add_subdirectory("libs/glad")
add_subdirectory("libs/glm")
add_subdirectory("libs/stb_image")
add_subdirectory("libs/imgui")

add_library("${CMAKE_PROJECT_NAME}" STATIC "unity/unity.cpp")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC glfw glad glm stb_image imgui)
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_precompile_headers("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_SOURCE_DIR}/resources/")
