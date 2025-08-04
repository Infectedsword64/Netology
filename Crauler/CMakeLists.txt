cmake_minimum_required(VERSION 3.16)
project(SearchEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Boost через vcpkg
find_package(Boost REQUIRED COMPONENTS system locale thread beast)

# Поиск libpqxx через vcpkg
find_package(libpqxx CONFIG REQUIRED)

# Поиск OpenSSL через vcpkg
find_package(OpenSSL REQUIRED)

include_directories(include)

set(COMMON_SOURCES
    src/config.cpp
    src/database.cpp
)
set(SPIDER_SOURCES
    ${COMMON_SOURCES}
    src/spider.cpp
    src/spider/main.cpp
)
set(SEARCH_ENGINE_SOURCES
    ${COMMON_SOURCES}
    src/search_engine.cpp
    src/search_engine/main.cpp
)

add_executable(spider ${SPIDER_SOURCES})
target_link_libraries(spider PRIVATE Boost::boost Boost::system Boost::locale Boost::thread Boost::beast libpqxx::pqxx OpenSSL::SSL OpenSSL::Crypto)

add_executable(search_engine ${SEARCH_ENGINE_SOURCES})
target_link_libraries(search_engine PRIVATE Boost::boost Boost::system Boost::locale Boost::thread Boost::beast libpqxx::pqxx OpenSSL::SSL OpenSSL::Crypto) 