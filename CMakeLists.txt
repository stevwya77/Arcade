cmake_minimum_required(VERSION 3.28)
project(ArcadeEngine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SFML_BUILD_NETWORK OFF)

include(FetchContent)
FetchContent_Declare(sfml URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(sfml json)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Engine/Source/*.cpp)
add_executable(ArcadeEngine ${SOURCES})

target_include_directories(ArcadeEngine PRIVATE Engine/Include)
target_compile_options(ArcadeEngine PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>, /W4, -Wall -Wextra>)
target_link_libraries(ArcadeEngine PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)