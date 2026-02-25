cmake_minimum_required(VERSION 3.16)
project(FIXEDSIZEHEADER LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(fixed_size_header
    src/Page.cpp
    src/main.cpp
)

target_include_directories(fixed_size_header PRIVATE include)

target_compile_features(fixed_size_header PRIVATE cxx_std_17)

set_target_properties(fixed_size_header PROPERTIES
    CXX_EXTENSIONS OFF
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(fixed_size_header PRIVATE
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -pedantic
        -Wformat=2
        -Wshadow
        -Wnull-dereference
        -fno-omit-frame-pointer
    )

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(fixed_size_header PRIVATE
            -g
            -fsanitize=address,undefined
        )
        target_link_options(fixed_size_header PRIVATE
            -fsanitize=address,undefined
        )
    endif()
endif()