cmake_minimum_required (VERSION 3.8)

set(BINARY ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)


add_executable(${BINARY}_run ${SOURCES})

IF (WIN32)
    set_target_properties(${BINARY}_run PROPERTIES
    LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
ENDIF()

target_link_libraries(${BINARY}_run
    PUBLIC
    glad::glad
    glfw)

add_library(${BINARY}_lib STATIC ${SOURCES} ${SOURCES})