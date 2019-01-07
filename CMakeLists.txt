cmake_minimum_required(VERSION 3.13)
project(myjni)

set(CMAKE_CXX_STANDARD 17)

set(JVM_HOME /Users/rbe/.sdkman/candidates/java/8.0.191-oracle)
include_directories(${JVM_HOME}/include)
include_directories(${JVM_HOME}/include/darwin)
link_directories(${JVM_HOME}/jre/lib/server)

add_executable(myjni main.cpp main.hpp)
target_link_libraries(myjni jvm)

execute_process(COMMAND mkdir classes)
execute_process(COMMAND ${JVM_HOME}/bin/javac -d classes Demo.java WORKING_DIRECTORY ..)
execute_process(COMMAND mkdir jars)
execute_process(COMMAND ${JVM_HOME}/bin/jar cf ../jars/Demo.jar Demo.class WORKING_DIRECTORY ../classes)
