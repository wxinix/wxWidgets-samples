cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)

project(wxWidgets-samples)

# wxWidgets
# Set wxWidgets_ROOT_DIR using environmental variable value.
set(wxWidgets_ROOT_DIR $ENV{WXWIDGETS_ROOT})
find_package(wxWidgets REQUIRED COMPONENTS core base)
include("${wxWidgets_USE_FILE}")

message("--wxWidget_USE_FILE-- ${wxWidgets_USE_FILE}")
#message("--wxWidgets_LIBRARIES--  ${wxWidgets_LIBRARIES}")

#DPI AWARE
set(wxUSE_DPI_AWARE_MANIFEST 2)
message("wxUSE_DPI_AWARE_MANIFEST is set to ${wxUSE_DPI_AWARE_MANIFEST}")

# Add sub directories of various samples.
add_subdirectory(hello)
add_subdirectory(access)
add_subdirectory(minimal)
add_subdirectory(widgets)
add_subdirectory(notebook)
add_subdirectory(dialogs)

