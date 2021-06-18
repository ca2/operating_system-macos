cmake_minimum_required(VERSION 3.17)
project(windowing_macos CXX)


list(APPEND library_source
        _.h
        _c_mm.h
        _mm.h
        _windowing_macos.h
        clipboard.cpp
        copydesk.cpp
        copydesk.h
        copydesk.mm
        cursor.cpp
        cursor.h
        cursor.mm
        display.cpp
        display.h
        factory_exchange.cpp
        framework.cpp
        framework.h
        icon.cpp
        icon.h
        imm_client.cpp
        imm_client.h
        keyboard.cpp
        keyboard.h
        mm_oswindow.h
        monitor.cpp
        monitor.h
        monitor.mm
        node.cpp
        node.h
        notify_icon.cpp
        notify_icon.h
        notify_icon.mm
        notify_icon_mm.h
        notify_icon_mm_bridge.h
        notify_icon_mm_bridge.mm
        oswindow_data.cpp
        oswindow_data.h
        window.cpp
        window.h
        window_impl.h
        windowing.cpp
        windowing.h
        windowing_c.h
        windowing_keyboard.cpp
        windowing_keyboard.h
        windowing_keyboard.mm
        windowing_macos.cpp
)

list(APPEND library_references
    acme
    apex
    aqua
    aura
    axis
    acme_posix
    acme_apple
    acme_macos
    apex_posix
    apex_apple
    apex_macos
    aura_posix
    aura_apple
    aura_macos
    )

add_library(windowing_macos SHARED ${library_source})

target_precompile_headers(windowing_macos PRIVATE framework.h)

set_target_properties(windowing_macos PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(windowing_macos PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(windowing_macos PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(windowing_macos PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/windowing_macos.lib")
    target_link_options(windowing_macos PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/windowing_macos.def")
    target_link_libraries(windowing_macos PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(windowing_macos PRIVATE -fpermissive)
    target_compile_options(windowing_macos PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(windowing_macos PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(windowing_macos PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(windowing_macos PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(windowing_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(windowing_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(windowing_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(windowing_macos PRIVATE _windowing_macos_LIBRARY)



