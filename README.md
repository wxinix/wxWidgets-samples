# wxWidgets samples
wxWidgets sample projects using CMake for Microsoft Windows platform.

## Install WxWidgets on Windows

- Download [wxWidgets source](https://www.wxwidgets.org/downloads/).
    - Unzip, and copy the entire unzipped folder to `C:/DevLibs/` or whatever parent folder appropriate. The full path to wxWidgets source should be like `C:/DevLibs/wxWidgets-3.2.2.1` in the case that the downloaded version is `3.2.2.1` and the unzipped folder name is `wxWidgets-3.2.2.1`.
    - Create a Windows System Environmental Variable `WXWIN`, and set its value to wxWidgets source path, for example, `C:/DevLibs/wxWidgets-3.2.2.1`.

- Download [Windows 64-bit (x86-64) Development Files](https://www.wxwidgets.org/downloads/), via "Download Windows Binaries -> Visual Studio 2015/2017/2019/2022 -> 64-Bit (x86_64) -> Development Files"
    - Unzip and copy the subdirectory `vc14x_x64_dll` to `%WXWIN%/lib/`. This gives the library path as  `%WXWIN%/lib/vc14x_x64_dll`. Add this path to Windows System Environmental Variable `Path`.
    - This library path is intended for development, including dlls for both debug and release builds.
- Download [Release Dlls](https://www.wxwidgets.org/downloads/), via "Download Windows Binaries -> Visual Studio 2015/2017/2019/2022 -> 64-Bit (x86_64) -> Release DLLs"
    - Unzip and copy the subdirectory `vc14x_x64_dll` to %`WXWIN%/distrib/`. This gives the library path as
   `%WXWIN%\distrib\vc14x_x64_dll`. Add this path to Windows System Environmental Variable `Path` too. 
    - This library path is intended for distribution, including dlls for release build only.


## Configure CMakeLists

The CMakeLists for each project should be like the following template. Remember to add `WIN32` to `add_executable`, and to set `wxRootDir`.

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
set(wxRootDir $ENV{WXWIN})
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

### Running the Samples

To run the sample projects, ensure the following paths are added to your system `PATH` environment variable:
- Release Build: `C:\DevLibs\Cpp\wxWidgets-3.2.6\distrib\vc14x_x64_dll`  
- DebugBuild: `C:\DevLibs\Cpp\wxWidgets-3.2.6\lib\vc14x_x64_dll` 

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
                -manifest ${wxRootDir}/include/wx/msw/wx_dpi_aware.manifest
                -outputresource:$<TARGET_FILE:${PROJECT_NAME}>\;\#1)
    elseif(wxUSE_DPI_AWARE_MANIFEST EQUAL 2)
        add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
                COMMAND mt.exe
                -manifest ${wxRootDir}/include/wx/msw/wx_dpi_aware_pmv2.manifest
                -outputresource:$<TARGET_FILE:${PROJECT_NAME}>\;\#1)
    endif()
endif()
```

## Windows VERSIONINFO Resource

To add a VERSIONINFO resource, include a *.rc file, encoded in UTF-8 with a Byte Order Mark (BOM) signature,  in your project with the following content:

```
#include <windows.h>

#define VER_FILEVERSION             1,0,0,0
#define VER_FILEVERSION_STR         "1.0.0.0\0"
#define VER_PRODUCTVERSION          1,0,0,0
#define VER_PRODUCTVERSION_STR      "1.0.0.0\0"

VS_VERSION_INFO VERSIONINFO
    FILEVERSION VER_FILEVERSION
    PRODUCTVERSION VER_PRODUCTVERSION
    FILEFLAGSMASK 0x3fL
    FILEFLAGS 0x0L
    FILEOS 0x40004L
    FILETYPE 0x1L
    FILESUBTYPE 0x0L

    BEGIN
        BLOCK "StringFileInfo"
        BEGIN
            BLOCK "040904b0"
            BEGIN
                VALUE "CompanyName", "Your Company\0"
                VALUE "FileDescription", "Your Application\0"
                VALUE "FileVersion", VER_FILEVERSION_STR
                VALUE "InternalName", "YourApp.exe\0"
                VALUE "LegalCopyright", "© 2024 Your Company\0"
                VALUE "OriginalFilename", "YourApp.exe\0"
                VALUE "ProductName", "Your Product\0"
                VALUE "ProductVersion", VER_PRODUCTVERSION_STR
            END
        END

        BLOCK "VarFileInfo"
        BEGIN
            VALUE "Translation", 0x0409, 1200
        END
    END
END
```



