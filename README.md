# Geo Engine

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![CMake](https://img.shields.io/badge/Build-CMake-brightgreen.svg)](https://cmake.org/)

A simple, lightweight OpenGL ECS game engine library implemented in C++.

---

## 📖 Table of Contents

* [✨ Features](#-features)
* [🚀 Quick Start](#-quick-start)
* [🎮 Using GeoEngine in Your Game](#-using-geoengine-in-your-game)
* [🔧 Building the Engine](#-building-the-engine)
* [🐧 Platform Notes](#-platform-notes)
	* [Linux](#linux)
	* [Windows](#windows)
* [📚 Third-Party Libraries](#-third-party-libraries)

---

## ✨ Features

* **ECS/DOD:** A simple ECS project for learning game engines and C++.
* **Built from scratch:** Rendering and all systems built from scratch with the help of only a few librarys.
* **Cross-Platform (Planned/Partial):** Designed with portability in mind.

*(GIF or screenshot here)*
---

## 🚀 Quick Start

```bash
# Clone GeoEngine to your game project
cd MyGame
git clone <repo-url> GeoEngine
```

Add to your `CMakeLists.txt`:
```cmake
add_subdirectory(GeoEngine)
target_link_libraries(MyGame PRIVATE GeoEngine)
```

Create your game:
```cpp
#include <Engine.h>

int main() {
    Application app;
    app.Run();
    return 0;
}
```

## 🎮 Using GeoEngine in Your Game

### Project Structure
```
MyGame/
├── CMakeLists.txt
├── main.cpp
└── GeoEngine/          # GeoEngine as git submodule or copied folder
    ├── src/
    ├── libs/
    └── CMakeLists.txt
```

### CMakeLists.txt Setup
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyGame)
set(CMAKE_CXX_STANDARD 23)

# Include GeoEngine library
add_subdirectory(GeoEngine)

# Create your game executable
add_executable(MyGame main.cpp)

# Link against GeoEngine
target_link_libraries(MyGame PRIVATE GeoEngine)
```

### Building Your Game
```bash
mkdir build && cd build
cmake ..
make
./MyGame
```

## 🔧 Building the Engine

If you want to build the engine library directly:

```bash
git clone <repo-url>
cd GeoEngine
mkdir build && cd build
cmake ..
make
```

This builds the static library `libGeoEngine.a` that you can link against.

---

## 🐧 Platform Notes

### Linux

For successful compilation on Linux, you will need the development packages for X11 and Wayland for GLFW to link correctly and support both window managers.

Common packages include:
* `mesa-libGL-devel`
* `libxkbcommon-devel`

Wayland
* `wayland-protocols`
* `wayland-devel`

X11
* `libX11-devel`
* `libXrandr-devel`
* `libXi-devel`
* `libXcursor-devel`
* `libXrender-devel`
* `libXinerama-devel`

*(Package names may vary slightly depending on your specific distribution.)*

### Windows

I haven't tested or documented the build process on Windows yet and will update this when i do.

*If you encounter issues, please open an issue on the GitHub repository!*

---

## 📚 Third-Party Libraries

All necessary external libraries are included directly within the project's `libs/` directory and automatically linked when you use GeoEngine.

The key libraries used are:

* [**GLFW**](https://www.glfw.org/): A multi-platform library for OpenGL, OpenGL ES, and Vulkan development, providing a simple API for creating windows, contexts and surfaces, receiving input and events.
* [**Glad**](https://glad.dav1d.de/): A multi-language Vulkan/GL/GLES/EGL/GLX/WGL loader-generator. It allows you to load OpenGL functions dynamically.
* [**GLM**](https://glm.g-truc.net/): OpenGL Mathematics, a header-only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
* [**stb_image**](https://github.com/nothings/stb/blob/master/stb_image.h): A single-file public domain library for loading images.
* [**ImGui**](https://github.com/ocornut/imgui): Dear ImGui is a graphical user interface library for C++.
