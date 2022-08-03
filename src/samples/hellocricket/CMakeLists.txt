cmake_minimum_required(VERSION 3.4.1)

project(hellocricket CXX)

set(CK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_CURRENT_BINARY_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})
if(UNIX AND NOT ANDROID)
    set(CK_HELLOCRICKET_SRC "linux/hellocricket.cpp")

    include_directories(${CK_ROOT}/inc)
    add_executable(hellocricket ${CK_HELLOCRICKET_SRC})

    target_link_libraries(hellocricket PRIVATE ck)

    # copy assets
    add_custom_command(
            TARGET hellocricket POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/hellocricket.ckb
            ${CMAKE_CURRENT_BINARY_DIR})
else()
    message("WARNING! No samples available for this platform")
endif()