cmake_minimum_required(VERSION 3.25)
project(UIN-Campus VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(uincampus_options INTERFACE)
target_compile_features(uincampus_options INTERFACE cxx_std_23)
target_compile_options(uincampus_options INTERFACE -Wall -Wextra -Wpedantic)

add_library(uincampus_core
    src/version.cpp
    src/regles.cpp
    src/saisie.cpp
)

target_include_directories(uincampus_core PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(uincampus_core PRIVATE UIN_VERSION="${PROJECT_VERSION}")

add_executable(uin-campus app/main.cpp)
target_link_libraries(uin-campus PRIVATE uincampus_core uincampus_options)
