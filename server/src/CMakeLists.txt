cmake_minimum_required(VERSION 3.0)

set(DCMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(server)

find_path(ActiveMQ-CPP_INCLUDE_DIR cms/Config.h
          DOC "ActiveMQ-CPP include files"
          HINTS ${ActiveMQ-CPP_PKGCONF_INCLUDE_DIRS})

find_library(ActiveMQ-CPP_LIBRARY NAMES activemq-cpp
             DOC "ActiveMQ-CPP library file"
             HINTS ${ActiveMQ-CPP_PKGCONF_LIBRARY_DIRS} )

include_directories(${ActiveMQ-CPP_INCLUDE_DIR})
link_libraries(${ActiveMQ-CPP_LIBRARY})

add_executable(server server.cpp)

target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)