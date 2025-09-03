# openGL_hub
For compilation run this: g++ "folder/main.cpp" "shared/glad/glad.c" -I "shared" -I "shared/glfw/include" -L "shared/lib" -lglfw3dll -o "bin/a.exe"

*include all file for compiling for e.g. "practice/main.cpp" "practice/shade.cpp" "practice/vbo.cpp" "practice/vao.cpp" "practice/ebo.cpp" for the practice folder

*Also ensure "glfw.dll" is in the same folder as executable.(Since we using Dynamic Linking so must be present @ runtime)

Some compilation notes:

"-I" is used to tell to find header file - ".h"
"-L" is used to tell to find libraries - ".lib" in Windows ".a" in Linux
"-l" is used for linking lib - ".lib" for static ".dll" for dynamic

for DeBugging:
"undefined reference" → means you included the header but didn’t link the right library.
"cannot find -lname" → means linker couldn’t find libname.so or libname.a in paths.
runtime error: missing DLL → you linked dynamically but didn’t copy .dll beside .exe.

Note: include make files for later projects