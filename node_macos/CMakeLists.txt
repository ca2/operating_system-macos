cmake_minimum_required(VERSION 3.17)
project(node_macos CXX)


list(APPEND library_source
        _.h
        #_node_macos.h
        factory_exchange.cpp
        framework.cpp
        framework.h
)

list(APPEND library_references
   acme apex aqua aura axis
        windowing_macos
        )

add_library(node_macos SHARED ${library_source})

target_precompile_headers(node_macos PRIVATE framework.h)

set_target_properties(node_macos PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(node_macos PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(node_macos PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(node_macos PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/node_macos.lib")
    target_link_options(node_macos PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/node_macos.def")
    target_link_libraries(node_macos PRIVATE ${library_references})
elseif(LINUX)
    pkg_check_modules(PKGCONFIG sqlite3)
    target_compile_options(node_macos PRIVATE -fpermissive)
    target_compile_options(node_macos PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(node_macos PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(node_macos PRIVATE ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(node_macos PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(node_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_macos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_macos PRIVATE _node_macos_LIBRARY)



