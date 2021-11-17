cmake_minimum_required(VERSION 3.0)
project(BS)
add_executable(app ../src/main.cpp ../src/functions.cpp ../src/customer.cpp ../src/banktransaction.cpp)
include_directories(../header)