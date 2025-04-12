cmake_minimum_required(VERSION 3.20)
project(CPPSQL7_4)
add_executable(CPPSQL7_4 CPPSQL7_4.cpp MySQL.cpp)
add_subdirectory("C:/Users/semen karpov/Desktop/CPPSQL7_4-master/libpqxx-7.10.1" libpqxx-build) # Укажите путь к libpq++
target_compile_features(CPPSQL7_4 PRIVATE cxx_std_17) # Включите C++17
target_link_libraries(CPPSQL7_4 pqxx) # Слинкуйте libpq++ к проекту