cmake_minimum_required(VERSION 3.5)
project(Survival_Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Agent.cpp AgentPiatra.cpp AgentFoarfeca.cpp AgentHartie.cpp Simulare.cpp map_full_error.cpp map_full_error.h timeout_error.cpp timeout_error.h simulation_error.cpp simulation_error.h)
add_executable(Survival_Game ${SOURCE_FILES})