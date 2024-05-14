cmake_minimum_required(VERSION 3.16)
project(space_invaders LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SRC_FILES
    src/main.cpp
    src/game.cpp
)

add_executable(space_invaders ${SRC_FILES})
target_link_libraries(space_invaders PRIVATE sfml-graphics)
target_compile_features(space_invaders PRIVATE cxx_std_17)

target_include_directories(space_invaders PRIVATE ${CMAKE_SOURCE_DIR}/inc)

if(WIN32)
    add_custom_command(
        TARGET space_invaders
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:space_invaders>
        VERBATIM)
endif()

install(TARGETS space_invaders)
