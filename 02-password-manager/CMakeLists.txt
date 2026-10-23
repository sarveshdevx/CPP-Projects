
cmake_minimum_required(VERSION 3.20)
project(cpp_password_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED IMPORTED_TARGET libsodium)

add_executable(password_manager password_manager.cpp)

target_link_libraries(password_manager PRIVATE PkgConfig::SODIUM)
