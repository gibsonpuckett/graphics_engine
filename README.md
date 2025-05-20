Not sure where this is going yet...

For now, focusing on making an OpenGL graphics engine with C.

Probably will do a 2D game, and eventually want to experiment with procedural generation


To build/compile:
> cd build
> cmake ..
> make
> ./run


Build Structure (so far):

engine/
├── README.md
├── CMakeLists.txt
├── src/
│   ├── main.c
│   ├── shader.c
│   └── glad.c
├── assets/
│   ├── shaders/
│   │   ├── vertex_shader.glsl
│   │   └── fragment_shader.glsl
│   └── textures
├── build/
│   ├── run.sh
│   ├── Makefile
│   ├── CMakeCache.txt
│   ├── cmake_install.cmake
│   └── CMakeFiles/...
├── include/
│   ├── main.h
│   └── shader.h
└── dependencies/
    ├── glad/...
    ├── GLFW/...
    └── KHR/...