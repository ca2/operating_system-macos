cmake_minimum_required(VERSION 3.17)
project(acme_macos CXX)


list(APPEND library_source
        _.h
        _acme_macos.h
        _c_mm.h
        _mm.h
        acme_dir.cpp
        acme_dir.h
        acme_path.cpp
        acme_path.h
        application.cpp
        application.h
        factory_exchange.cpp
        factory_exchange.h
        file.cpp
        file.h
        file.mm
        framework.cpp
        framework.h
        image.cpp
        image.mm
        list_serial_ports.cpp
        main.cpp
        mm.mm
        mmos.h
        mmos.mm
        node.cpp
        node.h
        process.cpp
        process_pid.cpp
        stdio_file.cpp
        stdio_file.h
        thread.cpp
        thread.h
        trace.cpp
        user.h
        util.cpp
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(acme_macos SHARED ${library_source})

target_precompile_headers(acme_macos PRIVATE framework.h)

set_target_properties(acme_macos PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(acme_macos PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(acme_macos PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(acme_macos PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/acme_macos.lib")
    target_link_options(acme_macos PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/acme_macos.def")
    target_link_libraries(acme_macos PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(acme_macos PRIVATE -fpermissive)
    target_compile_options(acme_macos PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(acme_macos PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(acme_macos PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(acme_macos PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(acme_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(acme_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(acme_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(acme_macos PRIVATE _acme_macos_LIBRARY)



