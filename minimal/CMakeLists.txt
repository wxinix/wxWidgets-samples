
# Name the project
project(minimal)

# Define a variable containing a list of source files for the project
set(SRC_FILES
    minimal.cpp
    ${CMAKE_SOURCE_DIR}/sample.rc)

# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

if (WIN32)
    if (wxUSE_DPI_AWARE_MANIFEST EQUAL 1)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND mt.exe
                -manifest ${wxRootDir}/include/wx/msw/wx_dpi_aware.manifest
                -outputresource:$<TARGET_FILE:${PROJECT_NAME}>\;\#1)
    elseif (wxUSE_DPI_AWARE_MANIFEST EQUAL 2)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND mt.exe
                -manifest ${wxRootDir}/include/wx/msw/wx_dpi_aware_pmv2.manifest
                -outputresource:$<TARGET_FILE:${PROJECT_NAME}>\;\#1)
    endif ()
endif ()