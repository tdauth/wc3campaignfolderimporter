cmake_minimum_required(VERSION 3.5)

project(wc3campaignfolderimporter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ExternalProject_Add(StormLib
    GIT_REPOSITORY "https://github.com/ladislav-zezula/StormLib"
)

add_executable(wc3campaignfolderimporter main.cpp)
add_dependencies(wc3campaignfolderimporter StormLib)
