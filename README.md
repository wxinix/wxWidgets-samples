# wxWidgets samples
wxWidgets sample projects using JetBrains CLion and CMake, for Microsoft Windows platform.

## Install WxWidgets on Windows

- Download [wxWidgets source](https://www.wxwidgets.org/downloads/).
    - Unzip, and copy the entire unzipped folder "wxWidgets-3.2.2.1" to `C:/DevLibs/`. The final source path should be like `C:/DevLibs/wxWidgets-3.2.2.1`.
    - Update Environmental Variable "WXWIDGETS_ROOT" to the correct path, for example, `C:/DevLibs/wxWidgets-3.2.2.1`.

- Download [Windows 64-bit (x86-64) Development Files](https://www.wxwidgets.org/downloads/), via "Download Windows Binaries -> Visual Studio 2015/2017/2019/2022 -> 64-Bit (x86_64) -> Development Files"
    - Unzip and copy the subdirectory "vc14x_x64_dll" to `%WXWIDGETS_ROOT%/lib/`. 
    - The path should be like `%WXWIDGETS_ROOT%/lib/vc14x_x64_dll`.  Add this path to Environmental Variable Path.
    - This path includes dlls for debug build.
- Download [Release Dlls](https://www.wxwidgets.org/downloads/), via "Download Windows Binaries -> Visual Studio 2015/2017/2019/2022 -> 64-Bit (x86_64) -> Release DLLs"
    - Unzip and copy the subdirectory "vc14x_x64_dll" to %`WXWIDGETS_ROOT%/distrib/`.
    - The path should be like `%WXWIDGETS_ROOT%\distrib\vc14x_x64_dll`. Add this path to Environmental Variable Path too. 
    - This is for release build.


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
set(wxWidgets_ROOT_DIR $ENV{WXWIDGETS_ROOT})
find_package(wxWidgets REQUIRED COMPONENTS core base)
include("${wxWidgets_USE_FILE}")
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
```

## Build wxrc.exe

- Make a copy of `%WXWIDGETS_ROOT%/lib/vc14x_x64_dll`, renamed it to `%WXWIDGETS_ROOT%/lib/vc_x64_dll`
- Launch `x64 Native Tools Command Prompt for VS 2022` 
- cd `%WXWIDGETS_ROOT%\utils\wxrc`
- Run `nmake /f makefile.vc BUILD=release SHARED=1 TARGET_CPU=X64`. For more details, see [this article](https://docs.wxwidgets.org/stable/plat_msw_install.html#:~:text=Using%20makefiles%20from%20Windows%20command%20line%201%20Change,you%20need%20to%20rebuild%2C%20use%20%22clean%22%20target%20first.)
- Copy `%WXWIDGETS_ROOT%/utils/wxrc/vc_x64_mswudll/wxrc.exe` to `%WXWIDGETS_ROOT%/lib/vc14x_x64_dll`.

## List of Sample Projects

- [Hello World](https://github.com/wxinix/wxWidgets-samples/tree/main/hello). For details, [read this article](https://docs.wxwidgets.org/latest/overview_helloworld.html).

## High DPI Support
 
See this reference [High DPI Support in wxWidgets](https://docs.wxwidgets.org/latest/overview_high_dpi.html)