# Gibson's Graphics Engine

This is a graphics engine written in C with the OpenGL API. Eventually I'll use it as a base to build a game or simulator of some kind on. I want to experiment with procedural generation, especially procedural animation, in C. For now, I'm aiming to use minimal libraries, and I'm sticking to .bmp image files for textures so I can write my own image loader. Eventually if it makes more sense to go with extra libraries then I will. Part of this project is just to experiment with and learn these low-level processes, so that's guiding my decision to remain in C with minimal libraries. I would also like to experiment with Entity-Component-System style of programming, and think about optimization for both speed and memory/resource usage.

## Getting Started

**Prerequisites**

* C Compiler : GCC, Clang, MSVC (Visual Studio), etc...
* CMake      : Version 3.10 or newer
* Git        : To clone this repo

**Requirements**

Install OpenGL development libraries

Debian:
sudo apt-get install libgl1-mesa-dev xorg-dev build-essential cmake git

Windows:
- Install latest Graphics Drivers for your GPU from manufacturer.
- Install Visual Studio (community edition) with Desktop Development with C/C++ workload, this includes MSVC compiler and build tools.
- Install CMake and add it to your PATH. [Link to CMake downloads page.](https://cmake.org/download/) 
- Consider using Git Bash or WSL for better compatibility with CMake and Unix-style build steps.

**Building the project**

1. Clone the repository
```
git clone https://github.com/gibsonpuckett/graphics_engine.git
```

2. Navigate to the build directory
```
cd graphics_engine
cd build	# or 'mkdir build' to make new 
```

3. Run cmake and build the executable
```
cmake ..
cmake --build . # Windows
run.exe 	# Windows
make  	        # Linux / MacOS
./run 	        # Linux / MacOS
```
To clean the build files, on linux type `make clean` and optionally delete the build folder. On windows just delete the build folder. Supposedly sometimes CMake requires running from a developer command prompt for Visual Studio.

**Dependencies**

CMakeLists.txt will automatically include the dependencies in the build from the dependencies directory of this repo. The project uses the following libraries:
* GLFW (Windowing & Inputs)
* GLAD (OpenGL Loader)
* cglm (Math C Library)

##Build Structure (so far):
```
engine/
├── README.md
├── CMakeLists.txt
├── build/		# your local build
├── src/
│   ├── main.c
│   ├── shader.c
│   ├── noise.c
│   ├── bmp_loader.c	# should probably separate into texture.c
│   └── noise.c
├── assets/
│   ├── shaders/
│   │   ├── vertex_shader.glsl
│   │   └── fragment_shader.glsl
│   └── textures
│       └── bricks.bmp
├── include/
│   ├── main.h
│   ├── image_loader.h # also into texture.h
│   ├── noise.h
│   └── shader.h
└── dependencies/
    ├── cglm/...
    ├── glad/...
    └── glfw/...
```
