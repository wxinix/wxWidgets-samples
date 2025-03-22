cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)

project(wxWidgets-samples)

set(wxRootDir $ENV{WXWIN})
set(wxCompilerPrefix vc14x)
set(wxArchSuffix x64)
set(wxToolkitPrefix msw)

set(wxUSINGDLL false) #Change this to enable static static lib or DLL

# Determine whether to use DLL or static libraries
if (wxUSINGDLL)
    set(wxLibTypeSuffix dll)
    add_definitions(-DWXUSINGDLL)
else()
    set(wxLibTypeSuffix lib)
endif()

add_definitions(-D_UNICODE -D__WXMSW__ -DwxMSVC_VERSION_AUTO -DwxMSVC_VERSION_ABI_COMPAT -DwxUSE_GUI)

set(wxWidgets_INCLUDE_DIRS
        "${wxRootDir}/include/msvc"
        "${wxRootDir}/include"
)
include_directories(${wxWidgets_INCLUDE_DIRS})

set(wxWidgets_LIBRARIES_DIR
        "${wxRootDir}/lib/${wxCompilerPrefix}_${wxArchSuffix}_${wxLibTypeSuffix}"
)
link_directories(${wxWidgets_LIBRARIES_DIR})

#DPI AWARE
set(wxUSE_DPI_AWARE_MANIFEST 2)
message("wxUSE_DPI_AWARE_MANIFEST is set to ${wxUSE_DPI_AWARE_MANIFEST}")

# Add sub directories of various samples.
add_subdirectory(access)
add_subdirectory(dialogs)
add_subdirectory(hello)
add_subdirectory(ipc_client)
add_subdirectory(ipc_server)
add_subdirectory(layout)
add_subdirectory(minimal)
add_subdirectory(notebook)
add_subdirectory(oleauto)
add_subdirectory(sashtest)
add_subdirectory(scroll)
add_subdirectory(widgets)