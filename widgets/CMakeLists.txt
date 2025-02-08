project(widgets)
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_DIR}/)

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