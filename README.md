# wxWidgets samples
wxWidgets sample projects using CMake for Microsoft Windows platform.

## Install WxWidgets on Windows

- Download [wxWidgets source](https://www.wxwidgets.org/downloads/).
    - Unzip, and copy the entire unzipped folder to `C:/DevLibs/` or whatever parent folder appropriate. The full path to wxWidgets source should be like `C:/DevLibs/wxWidgets-3.2.2.1` in the case that the downloaded version is `3.2.2.1` and the unzipped folder name is `wxWidgets-3.2.2.1`.
    - Create a Windows System Environmental Variable `WXWIDGETS_ROOT`, and set its value to wxWidgets source path, for example, `C:/DevLibs/wxWidgets-3.2.2.1`.

- Download [Windows 64-bit (x86-64) Development Files](https://www.wxwidgets.org/downloads/), via "Download Windows Binaries -> Visual Studio 2015/2017/2019/2022 -> 64-Bit (x86_64) -> Development Files"
    - Unzip and copy the subdirectory `vc14x_x64_dll` to `%WXWIDGETS_ROOT%/lib/`. This gives the library path as  `%WXWIDGETS_ROOT%/lib/vc14x_x64_dll`. Add this path to Windows System Environmental Variable `Path`.
    - This library path is intended for development, including dlls for both debug and release builds, as well as static libs.
- Download [Release Dlls](https://www.wxwidgets.org/downloads/), via "Download Windows Binaries -> Visual Studio 2015/2017/2019/2022 -> 64-Bit (x86_64) -> Release DLLs"
    - Unzip and copy the subdirectory `vc14x_x64_dll` to %`WXWIDGETS_ROOT%/distrib/`. This gives the library path as
   `%WXWIDGETS_ROOT%\distrib\vc14x_x64_dll`. Add this path to Windows System Environmental Variable `Path` too. 
    - This library path is intended for distribution, including dlls for release build only.


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

#DPI AWARE
add_definitions(-DwxUSE_DPI_AWARE_MANIFEST=2)
```

## Build wxrc.exe

This is an optional step because wxrc.exe is already supplied in the development library path `%WXWIDGETS_ROOT%/lib/vc14x_x64_dll`. However, if you'd like to build your own, follow the following steps:

- Make a copy of `%WXWIDGETS_ROOT%/lib/vc14x_x64_dll`, renamed it to `%WXWIDGETS_ROOT%/lib/vc_x64_dll`
- Launch `x64 Native Tools Command Prompt for VS 2022` 
- cd `%WXWIDGETS_ROOT%\utils\wxrc`
- Run `nmake /f makefile.vc BUILD=release SHARED=1 TARGET_CPU=X64`. For more details, see [this article](https://docs.wxwidgets.org/stable/plat_msw_install.html#:~:text=Using%20makefiles%20from%20Windows%20command%20line%201%20Change,you%20need%20to%20rebuild%2C%20use%20%22clean%22%20target%20first.)
- The newly built `wxrc.exe` should be inside `%WXWIDGETS_ROOT%/utils/wxrc/vc_x64_mswudll/`.

## List of Sample Projects

- [Hello World](https://github.com/wxinix/wxWidgets-samples/tree/main/hello). For details, [read this article](https://docs.wxwidgets.org/latest/overview_helloworld.html).

## High DPI Support
 
See this reference [High DPI Support in wxWidgets](https://docs.wxwidgets.org/latest/overview_high_dpi.html). On Windows DPI-awareness must be set through manifest file.

To enable DPI-awareness, add the following line to the master CMakeLists:
```
set(wxUSE_DPI_AWARE_MANIFEST 1)
message("wxUSE_DPI_AWARE_MANIFEST is set to ${wxUSE_DPI_AWARE_MANIFEST}")
```

Then for each executable, add the following lines to their respective CMakeLists:

```
if (WIN32)
    if(wxUSE_DPI_AWARE_MANIFEST EQUAL 1)
        add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
                COMMAND mt.exe
                -manifest ${wxWidgets_ROOT_DIR}/include/wx/msw/wx_dpi_aware.manifest
                -outputresource:$<TARGET_FILE:${PROJECT_NAME}>\;\#1)
    elseif(wxUSE_DPI_AWARE_MANIFEST EQUAL 2)
        add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
                COMMAND mt.exe
                -manifest ${wxWidgets_ROOT_DIR}/include/wx/msw/wx_dpi_aware_pmv2.manifest
                -outputresource:$<TARGET_FILE:${PROJECT_NAME}>\;\#1)
    endif()
endif()
```

