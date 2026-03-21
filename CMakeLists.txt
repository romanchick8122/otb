cmake_minimum_required(VERSION 3.6)
project(otb C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

cmake_policy(SET CMP0069 NEW) 
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c" "${CMAKE_SOURCE_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

set_target_properties(raylib PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:raylib,INTERFACE_INCLUDE_DIRECTORIES>)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PUBLIC OTB_ASSETS_DIRECTORY="assets/")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC OTB_ASSETS_DIRECTORY=\"${CMAKE_CURRENT_LIST_DIR}/assets\")
    target_compile_definitions(${PROJECT_NAME} PUBLIC OTB_DEBUG)
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    install(
        TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}Targets"
        COMPONENT ${PROJECT_NAME}
    )
    install(
        DIRECTORY assets/
        DESTINATION ${CMAKE_INSTALL_BINDIR}/assets/
    )

    set(CPACK_PACKAGE_NAME "otb")
    set(CPACK_PACKAGE_VENDOR "Fallen Kingdom of Bruhland")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "otb")
    set(CPACK_PACKAGE_VERSION "0.1.0")
    set(CPACK_PACKAGE_VERSION_MAJOR "0")
    set(CPACK_PACKAGE_VERSION_MINOR "1")
    set(CPACK_PACKAGE_VERSION_PATCH "0")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "otb")

    include(CPack)
endif()