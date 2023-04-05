cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)

project(wxWidgets-samples)

# wxWidgets
set(wxWidgets_ROOT_DIR $ENV{WXWIDGETS_ROOT})
find_package(wxWidgets REQUIRED COMPONENTS core base)
include("${wxWidgets_USE_FILE}")
# message("wxWidget_USE_FILE ${wxWidgets_USE_FILE}")
# message("wxWidgets_LIBRARIES ${wxWidgets_LIBRARIES}")

# Add sub directories of various samples.
add_subdirectory(hello)
add_subdirectory(access)

