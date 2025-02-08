project(widgets)
set(SRC_FILES
        activityindicator.cpp
        bmpcombobox.cpp
        button.cpp
        checkbox.cpp
        choice.cpp
        clrpicker.cpp
        combobox.cpp
        datepick.cpp
        dirctrl.cpp
        dirpicker.cpp
        editlbox.cpp
        filectrl.cpp
        filepicker.cpp
        fontpicker.cpp
        gauge.cpp
        headerctrl.cpp
        hyperlnk.cpp
        itemcontainer.cpp
        listbox.cpp
        native.cpp
        notebook.cpp
        odcombobox.cpp
        radiobox.cpp
        searchctrl.cpp
        slider.cpp
        spinbtn.cpp
        static.cpp
        statbmp.cpp
        textctrl.cpp
        timepick.cpp
        toggle.cpp
        widgets.cpp)

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

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