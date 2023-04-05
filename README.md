# wxWidgets samples
wxWidgets sample projects using JetBrains CLion and CMake, for Microsoft Windows platform.

## Install WxWidgets on Windows

- [Download ](https://www.wxwidgets.org/downloads/) both wxWidgets **source** and Windows **binaries**. For Windows binaries, download 64-bit **Development** Files under Visual Studio 2019.
- Unzip the source, and put contents to `C:/DevLibs/`. The final source path should be like `C:/DevLibs/wxWidgets-3.2.1`.
- Unzip the binary, and put the contents to `C:/DevLibs/wxWidgets-3.2.1/lib/`. 
    - The final binary path should be like `C:/DevLibs/wxWidgets-3.2.1/lib/vc14x_x64_dll`.  Also add this path to Environmental Variable Path.
    - The binaries are those dependencies dlls for debug build.
- Add the path to distribution dlls `C:\DevLibs\wxWidgets-3.2.1\distrib\vc14x_x64_dll` to Environmental Variable Path too. This is for release build.


## Configure CMakeLists

The CMakeLists for each project should be like the following template. Remember to add `WIN32` to `add_executable`, and to set `wxWidgets_ROOT_DIR`.

```cmake
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)

project(hello)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

# wxWidgets
set(wxWidgets_ROOT_DIR "C:/DevLibs/wxWidgets-3.2.1")
find_package(wxWidgets REQUIRED COMPONENTS core base)
include("${wxWidgets_USE_FILE}")
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
```

## Build wxrc.exe

- Make a copy of `C:/DevLibs/wxWidgets-3.2.1/lib/vc14x_x64_dll`, renamed it to `C:/DevLibs/wxWidgets-3.2.1/lib/vc_x64_dll`
- Launch `x64 Native Tools Command Prompt for VS 2022` 
- cd `C:\DevLibs\wxWidgets-3.2.1\utils\wxrc`
- Run `nmake /f makefile.vc BUILD=release SHARED=1 TARGET_CPU=X64`. For more details, see [this article](https://docs.wxwidgets.org/stable/plat_msw_install.html#:~:text=Using%20makefiles%20from%20Windows%20command%20line%201%20Change,you%20need%20to%20rebuild%2C%20use%20%22clean%22%20target%20first.)
- Copy `C:/DevLibs/wxWidgets-3.2.1/utils/wxrc/vc_x64_mswudll/wxrc.exe` to `C:/DevLibs/wxWidgets-3.2.1/lib/vc14x_x64_dll`.

## List of Sample Projects

- [Hello World](https://github.com/wxinix/wxWidgets-samples/tree/main/hello). For details, [read this article](https://docs.wxwidgets.org/latest/overview_helloworld.html).