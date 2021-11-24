cmake_minimum_required(VERSION 3.17)
project(aura_macos CXX)


#include(../../../objc++.cmake)


list(APPEND library_source
        _.h
        _aura_macos.h
        _c_mm.h
        _mm.h
        _factory.cpp
        factory_exchange.h
        framework.cpp
        framework.h
        image.cpp
        interaction_impl.cpp
        interaction_impl.h
        node.cpp
        node.h
)

list(APPEND library_references
   acme apex aqua aura axis)

add_library(aura_macos SHARED ${library_source})

target_precompile_headers(aura_macos PRIVATE framework.h)

set_target_properties(aura_macos PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(aura_macos PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(aura_macos PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(aura_macos PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/aura_macos.lib")
    target_link_options(aura_macos PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/aura_macos.def")
    target_link_libraries(aura_macos PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(aura_macos PRIVATE -fpermissive)
    target_compile_options(aura_macos PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(aura_macos PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(aura_macos PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(aura_macos PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(aura_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(aura_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(aura_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(aura_macos PRIVATE _aura_macos_LIBRARY)



