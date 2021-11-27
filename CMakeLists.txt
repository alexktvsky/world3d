cmake_minimum_required(VERSION 3.16.0)

project(world3d
    LANGUAGES CXX
    DESCRIPTION "world3d"
)

include(cmake/find_opengl.cmake)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
PRIVATE
    include
)

target_sources(${PROJECT_NAME}
PRIVATE
    src/main.cpp
    src/actor.cpp
    src/camera.cpp
    src/scene.cpp
    src/window.cpp
)

target_compile_options(${PROJECT_NAME}
PRIVATE
    -Wall
    -Wextra
    -Wuninitialized
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if (NOT CMAKE_BUILD_TYPE)
    set (build_type release)
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
endif()

if (build_type STREQUAL debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O0 -ggdb3)
elseif (build_type STREQUAL release)
    target_compile_options(${PROJECT_NAME} PRIVATE -g0 -O3)
endif()

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)
