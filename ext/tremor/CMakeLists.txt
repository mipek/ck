cmake_minimum_required(VERSION 3.4.1)
project(tremor)

file(GLOB tremor_SRC
    "*.h"
    "*.c"
)

add_library(tremor STATIC
    block.c
    codebook.c
    floor0.c
    floor1.c
    info.c
    mapping0.c
    mdct.c
    registry.c
    res012.c
    sharedbook.c
    synthesis.c
    vorbisfile.c
    window.c)

target_link_libraries(tremor
    ogg)