cmake_minimum_required(VERSION 3.25)
project(server_side)

set(CMAKE_CXX_STANDARD 17)

include_directories("ext/")
include_directories("inc/")
file(COPY data.db DESTINATION "/" )

add_executable(server_side main.cpp ext/httplib/httplib.h ext/json/json.hpp inc/Utils.hpp src/Utils.cpp ext/sqlite/sqlite3.h ext/sqlite/sqlite3.c inc/network/Server.hpp src/network/Server.cpp inc/repositories/LocalDataRepository.hpp inc/repositories/LocalDataRepositoryImpl.hpp src/repositories/LocalDataRepositoryImpl.cpp src/database/Database.cpp inc/database/Database.hpp inc/entities/Student.h)
