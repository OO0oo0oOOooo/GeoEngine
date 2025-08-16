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

# option(GLFW_BUILD_WAYLAND "Build Wayland support" ON)
# option(GLFW_BUILD_X11 "Build X11 support" ON)

add_subdirectory("libs/glfw")
add_subdirectory("libs/glad")
add_subdirectory("libs/glm")
add_subdirectory("libs/stb_image")
add_subdirectory("libs/imgui")

add_library("GeoEngine" STATIC "unity/unity.cpp")
target_link_libraries("GeoEngine" PUBLIC glfw glad glm stb_image imgui)
target_include_directories("GeoEngine" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_definitions("GeoEngine" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
