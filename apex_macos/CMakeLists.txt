cmake_minimum_required(VERSION 3.17)
project(apex_macos CXX)


list(APPEND library_source
        _.h
        _apex_macos.h
        _mm.h
        app.mm
        application.cpp
        application.h
        dir_context.cpp
        dir_context.h
        dir_system.cpp
        dir_system.h
        factory_exchange.cpp
        factory_exchange.h
        file.mm
        file_context.cpp
        file_context.h
        file_system.cpp
        file_system.h
        framework.cpp
        framework.h
        interprocess_communication.cpp
        interprocess_communication.h
        keyboard.cpp
        keyboard.h
        keyboard_mm.mm
        launcher.cpp
        launcher.h
        mm_graphics.mm
        mm_oswindow.h
        node.cpp
        node.h
        NSPasteboard++.mm
        os_context.cpp
        os_context.h
        shell_launcher.cpp
        shell_launcher.h
        shell_macos_mm.mm
        simple_shell_launcher.cpp
        small_ipca_channel.cpp
        thread.cpp
        thread.h
        trace.cpp
        user.cpp
        user.h
        user.mm
        util.cpp
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(apex_macos SHARED ${library_source})

target_precompile_headers(apex_macos PRIVATE framework.h)

set_target_properties(apex_macos PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(apex_macos PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(apex_macos PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(apex_macos PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/apex_macos.lib")
    target_link_options(apex_macos PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/apex_macos.def")
    target_link_libraries(apex_macos PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(apex_macos PRIVATE -fpermissive)
    target_compile_options(apex_macos PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(apex_macos PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(apex_macos PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(apex_macos PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(apex_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(apex_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(apex_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(apex_macos PRIVATE _apex_macos_LIBRARY)



