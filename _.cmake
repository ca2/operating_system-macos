#Created by camilo on 2025-11-03 21:53 <3ThomasBorregaardSørensen!!
#From operating_system-posix by camilo on 2026-06-05 03:05 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!


set(OPERATING_SYSTEM_POSIX TRUE)
set(OPERATING_SYSTEM_NAME "macos")

enable_language(OBJCXX)


#include_directories(${WORKSPACE_FOLDER})
#include_directories($ENV{HOME}/__config)
#include_directories(${WORKSPACE_FOLDER}/source)
#include_directories(${WORKSPACE_FOLDER}/source/app)
#include_directories(${WORKSPACE_FOLDER}/source/app/include)
#include_directories(${WORKSPACE_FOLDER}/source/include)
#include_directories(${WORKSPACE_FOLDER}/port/_)
#include_directories(${WORKSPACE_FOLDER}/port/include)
#include_directories(${WORKSPACE_FOLDER}/operating_system)
if (${OPERATING_SYSTEM_POSIX})
   include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-posix)
   include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-posix/include)
endif ()
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-darwin)
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-apple)
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME})
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/include)
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/include/configuration_selection/${CMAKE_BUILD_TYPE})
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/operating_system/${SLASHED_OPERATING_SYSTEM})
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/operating_system/${DISTRO})




