cmake_minimum_required (VERSION 3.8)

IF (WIN32)
    SET(DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake)
ELSE ()
    SET(DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake)
ENDIF()

project ("sort_analyzer")

add_subdirectory (src)