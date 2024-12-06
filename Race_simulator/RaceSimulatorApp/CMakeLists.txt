cmake_minimum_required(VERSION 3.10)
project(RaceSimulatorApp)
add_executable(RaceSimulatorApp
"main.cpp" "Presentation.h" "Presentation.cpp")
target_link_libraries(RaceSimulatorApp RaceSimulation)
target_include_directories(RaceSimulatorApp PRIVATE "../RaceSimulation")
