cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_PLATFORM_NAME)
    set(CMAKE_PLATFORM_NAME "x64")
endif()

project(ck CXX)
set(PROJECT_NAME ck)

option(CK_LINUX_PULSE "Use PulseAudio instead of ALSA on Linux")

## helper macro
macro (add_compiler_flags)
    string (REPLACE ";" " " _FLAGS "${ARGV}")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_FLAGS}")
endmacro ()

set(CK_NEON_SRC
        "audio/audioutil.neon.cpp"
        "audio/biquadfilterprocessor.neon.cpp"
        "audio/bitcrusherprocessor.neon.cpp"
        "audio/distortionprocessor.neon.cpp"
        "audio/ringmodprocessor.neon.cpp"
        )

set(CK_SSE_SRC
        "audio/audioutil_sse.cpp"
        "audio/biquadfilterprocessor_sse.cpp"
        "audio/bitcrusherprocessor_sse.cpp"
        "audio/distortionprocessor_sse.cpp"
        "audio/ringmodprocessor_sse.cpp"
        )

set(Headers
    "../../inc/ck/bank.h"
    "../../inc/ck/config.h"
    "../../inc/ck/mixer.h"
    "../../inc/ck/platform.h"
    "../../inc/ck/sound.h"
    "audio/adpcm.h"
    "audio/adpcmdecoder.h"
    "audio/audio.h"
    "audio/audiofileinfo.h"
    "audio/audioformat.h"
    "audio/audiograph.h"
    "audio/audionode.h"
    "audio/audiosource.h"
    "audio/audiostream.h"
    "audio/audioutil.h"
    "audio/audiowriter.h"
    "audio/bank.h"
    "audio/bankdata.h"
    "audio/banksound.h"
    "audio/biquadfilterprocessor.h"
    "audio/bitcrusherprocessor.h"
    "audio/bufferhandle.h"
    "audio/bufferpool.h"
    "audio/buffersource.h"
    "audio/cksaudiostream.h"
    "audio/cksstreamsound.h"
    "audio/commandobject.h"
    "audio/commandparam.h"
    "audio/customaudiostream.h"
    "audio/customstreamsound.h"
    "audio/decoder.h"
    "audio/decoderbuf.h"
    "audio/distortionprocessor.h"
    "audio/effect.h"
    "audio/effectbus.h"
    "audio/effectbusnode.h"
    "audio/effectprocessor.h"
    "audio/fileheader.h"
    "audio/filetype.h"
    "audio/fourcharcode.h"
    "audio/graphoutput.h"
    "audio/graphoutput_dummy.h"
    "audio/graphoutput_win.h"
    "audio/graphsound.h"
    "audio/mixer.h"
    "audio/mixnode.h"
    "audio/pcmf32decoder.h"
    "audio/pcmi16decoder.h"
    "audio/pcmi8decoder.h"
    "audio/rawwriter.h"
    "audio/resampler.h"
    "audio/ringmodprocessor.h"
    "audio/sample.h"
    "audio/sampleinfo.h"
    "audio/sharedbuffer.h"
    "audio/sinenode.h"
    "audio/sinesource.h"
    "audio/sound.h"
    "audio/soundname.h"
    "audio/sourcenode.h"
    "audio/streamsound.h"
    "audio/streamsource.h"
    "audio/volumematrix.h"
    "audio/vorbisaudiostream.h"
    "audio/vorbisstreamsound.h"
    "audio/wavwriter.h"
    "core/allocatable.h"
    "core/allocator.h"
    "core/array.h"
    "core/asyncloader.h"
    "core/atomic.h"
    "core/binarystream.h"
    "core/binarywriter.h"
    "core/bufferstream.h"
    "core/byteorder.h"
    "core/callback.h"
    "core/cond.h"
    "core/customstream.h"
    "core/debug.h"
    "core/deletable.h"
    "core/dir.h"
    "core/filestream.h"
    "core/filewriter.h"
    "core/fixedarray.h"
    "core/fixedpoint.h"
    "core/fixedstring.h"
    "core/funcallocator.h"
    "core/glitchfinder.h"
    "core/list.h"
    "core/listable.h"
    "core/lockfreequeue.h"
    "core/logger.h"
    "core/math.h"
    "core/md5.h"
    "core/mem.h"
    "core/memoryfixup.h"
    "core/memorystream.h"
    "core/mutex.h"
    "core/mutexlock.h"
    "core/path.h"
    "core/pch.h"
    "core/platform.h"
    "core/pool.h"
    "core/profiler.h"
    "core/proxied.h"
    "core/readstream.h"
    "core/ringbuffer.h"
    "core/runningaverage.h"
    "core/sse.h"
    "core/staticsingleton.h"
    "core/stats.h"
    "core/string.h"
    "core/stringwriter.h"
    "core/substream.h"
    "core/swapstream.h"
    "core/system.h"
    "core/system_win.h"
    "core/target.h"
    "core/textwriter.h"
    "core/thread.h"
    "core/timer.h"
    "core/treenode.h"
    "core/types.h"
    "core/vector3.h"
    "core/version.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "api/bank.cpp"
    "api/ck.cpp"
    "api/config.cpp"
    "api/customfile.cpp"
    "api/effect.cpp"
    "api/effectbus.cpp"
    "api/effectprocessor.cpp"
    "api/mixer.cpp"
    "api/sound.cpp"
    "audio/adpcm.cpp"
    "audio/adpcmdecoder.cpp"
    "audio/audio.cpp"
    "audio/audiofileinfo.cpp"
    "audio/audioformat.cpp"
    "audio/audiograph.cpp"
    "audio/audionode.cpp"
    "audio/audiosource.cpp"
    "audio/audiostream.cpp"
    "audio/audioutil.cpp"
    "audio/audioutil_sse.cpp"
    "audio/audiowriter.cpp"
    "audio/bank.cpp"
    "audio/bankdata.cpp"
    "audio/banksound.cpp"
    "audio/biquadfilterprocessor.cpp"
    "audio/bitcrusherprocessor.cpp"
    "audio/bufferhandle.cpp"
    "audio/bufferpool.cpp"
    "audio/buffersource.cpp"
    "audio/cksaudiostream.cpp"
    "audio/cksstreamsound.cpp"
    "audio/commandobject.cpp"
    "audio/customaudiostream.cpp"
    "audio/customstreamsound.cpp"
    "audio/decoder.cpp"
    "audio/decoderbuf.cpp"
    "audio/distortionprocessor.cpp"
    "audio/effect.cpp"
    "audio/effectbus.cpp"
    "audio/effectbusnode.cpp"
    "audio/effectprocessor.cpp"
    "audio/fileheader.cpp"
    "audio/fourcharcode.cpp"
    "audio/graphoutput.cpp"
    "audio/graphoutput_dummy.cpp"
    "audio/graphoutput_win.cpp"
    "audio/graphsound.cpp"
    "audio/mixer.cpp"
    "audio/mixnode.cpp"
    "audio/pcmf32decoder.cpp"
    "audio/pcmi16decoder.cpp"
    "audio/pcmi8decoder.cpp"
    "audio/rawwriter.cpp"
    "audio/resampler.cpp"
    "audio/ringmodprocessor.cpp"
    "audio/sample.cpp"
    "audio/sampleinfo.cpp"
    "audio/sharedbuffer.cpp"
    "audio/sinenode.cpp"
    "audio/sinesource.cpp"
    "audio/sound.cpp"
    "audio/soundname.cpp"
    "audio/sourcenode.cpp"
    "audio/streamsound.cpp"
    "audio/streamsource.cpp"
    "audio/volumematrix.cpp"
    "audio/vorbisaudiostream.cpp"
    "audio/vorbisstreamsound.cpp"
    "audio/wavwriter.cpp"
    "core/allocatable.cpp"
    "core/array.cpp"
    "core/asyncloader.cpp"
    "core/binarystream.cpp"
    "core/binarywriter.cpp"
    "core/bufferstream.cpp"
    "core/byteorder.cpp"
    "core/cond.cpp"
    "core/customstream.cpp"
    "core/debug.cpp"
    "core/deletable.cpp"
    "core/dir.cpp"
    "core/filestream.cpp"
    "core/filewriter.cpp"
    "core/fixedarray.cpp"
    "core/fixedstring.cpp"
    "core/funcallocator.cpp"
    "core/glitchfinder.cpp"
    "core/list.cpp"
    "core/listable.cpp"
    "core/lockfreequeue.cpp"
    "core/logger.cpp"
    "core/math.cpp"
    "core/md5.cpp"
    "core/mem.cpp"
    "core/memoryfixup.cpp"
    "core/memorystream.cpp"
    "core/mutex.cpp"
    "core/path.cpp"
    "core/pch.cpp"
    "core/pool.cpp"
    "core/profiler.cpp"
    "core/proxied.cpp"
    "core/readstream.cpp"
    "core/ringbuffer.cpp"
    "core/runningaverage.cpp"
    "core/sse.cpp"
    "core/staticsingleton.cpp"
    "core/stats.cpp"
    "core/string.cpp"
    "core/stringwriter.cpp"
    "core/substream.cpp"
    "core/swapstream.cpp"
    "core/system.cpp"
    "core/target.cpp"
    "core/textwriter.cpp"
    "core/thread.cpp"
    "core/timer.cpp"
    "core/treenode.cpp"
    "core/types.cpp"
    "core/version.cpp"

    ${CK_NEON_SRC}
    ${CK_SSE_SRC}
)

if (ANDROID)
    if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
        set_property(SOURCE ${CK_NEON_SRC}
                APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon")
    elseif (${ANDROID_ABI} STREQUAL "x86")
        set_property(SOURCE ${CK_SSE_SRC}
                APPEND_STRING PROPERTY COMPILE_FLAGS " -mssse3")
    endif ()

    set (PlatformSources
            "audio/audio_android.cpp"
            "audio/audiodebug_android.cpp"
            "audio/audiotrackproxy_android.cpp"
            "audio/graphoutput_android.cpp"
            "audio/graphoutputjava_android.cpp"
            "audio/nativestreamsound_android.cpp"
            "audio/opensles_android.cpp"
            "core/assetmanager_android.cpp"
            "core/assetstream_android.cpp"
            "core/jnienv_android.cpp"
            "core/system_android.cpp"
            "core/timer_linux.cpp"
            )
elseif (WIN32)
    set (PlatformSources
        "audio/audio_win.cpp"
        "audio/audiohelpers_win7.cpp"
        "audio/audiohelpers_win8.cpp"
        "core/timer_win.cpp"
        "core/system_win.cpp"
    )
elseif(UNIX)
    set (PlatformSources
        "audio/audio_linux.cpp"
        "core/timer_linux.cpp"
        "core/system_linux.cpp"
    )
    if (CK_LINUX_PULSE)
        set ( PlatformSources
             ${PlatformSources}
             "audio/graphoutput_linux_pulse.cpp"
        )
    else()
        set ( PlatformSources
              ${PlatformSources}
              "audio/graphoutput_linux_alsa.cpp"
        )
    endif()
else()
    message( SEND_ERROR "Please configure PlatformSources for this system" )
endif()

source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
    ${PlatformSources}
)

if (WIN32)
   add_compile_definitions(
         CK_ARCH=${CMAKE_PLATFORM_NAME}
         CK_PLATFORM_WIN
         _WIN32
         _WIN32_WINNT=0x0602
         NOMINMAX
         _CRT_SECURE_NO_WARNINGS
    )
    if("${CMAKE_PLATFORM_NAME}" STREQUAL "x64")
           add_compile_definitions(_WIN64)
    endif()
endif()

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

if (NOT MSVC)
    add_compiler_flags (-fno-omit-frame-pointer)
endif()

################################################################################
# Compile definitions
################################################################################
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        ${COMPILE_DEFS}
        _DEBUG
        CK_DEBUG=1
        _LIB)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        ${COMPILE_DEFS}
        NDEBUG
        CK_NDEBUG=1
        _LIB)
endif()

################################################################################
# Include directories
################################################################################
if("${CMAKE_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libogg/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../ext;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../inc"
    )
elseif("${CMAKE_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/..;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../ext/libogg/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../ext;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../inc"
    )
endif()

################################################################################
# Dependencies
################################################################################
if (UNIX AND NOT ANDROID)
   if (CK_LINUX_PULSE)
       target_link_libraries(${PROJECT_NAME} pulse)
       add_compile_definitions(CK_LINUX_PULSEAUDIO)
   else()
       find_package(ALSA REQUIRED)
       if (ALSA_FOUND)
           include_directories(${ALSA_INCLUDE_DIRS})
           target_link_libraries(${PROJECT_NAME} ${ALSA_LIBRARIES})
       endif(ALSA_FOUND)
   endif()
endif()

if (ANDROID)
    target_link_libraries(${PROJECT_NAME} cpufeatures)
endif()

target_link_libraries(${PROJECT_NAME} tremor)
