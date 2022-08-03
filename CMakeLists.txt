cmake_minimum_required(VERSION 3.4.1)
project(cricket-audio)

option(BUILD_SAMPLES "Build Cricket-Audio samples" ON)
# option(BUILD_TOOLS "Build Cricket-Audio tools" ON)

if (WIN32)
   add_compile_definitions(CK_PLATFORM_WIN)
elseif(UNIX)
   set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
endif()

# external libraries
option(INSTALL_DOCS "" OFF)
option(INSTALL_PKG_CONFIG_MODULE "" OFF)
option(INSTALL_CMAKE_PACKAGE_MODULE "" OFF)

add_subdirectory(ext/libogg)
add_subdirectory(ext/tremor)

set_property(TARGET ogg PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET tremor PROPERTY POSITION_INDEPENDENT_CODE ON)

# source
add_subdirectory(src/ck)

# optional: samples
if (BUILD_SAMPLES)
   # TODO: add support for all samples
   add_subdirectory(src/samples/hellocricket)
endif()