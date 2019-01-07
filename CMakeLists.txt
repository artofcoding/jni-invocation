cmake_minimum_required(VERSION 3.13)
project(myjni)

set(CMAKE_CXX_STANDARD 17)

# https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/Checking-Platform
# UNIX, WIN32, APPLE, MINGW, MSYS, CYGWIN

#
# Java VM
#

if (UNIX)
    # Ubuntu Java 11
    #set(JVM_HOME /usr/lib/jvm/java-1.11.0-openjdk-amd64)
    #link_directories(${JVM_HOME}/lib/server)
    # Oracle JDK 8u192
    set(JVM_HOME /opt/jdk1.8.0_192)
    link_directories(${JVM_HOME}/jre/lib/amd64/server)
    # General
    include_directories(${JVM_HOME}/include/linux)
endif (UNIX)

if (APPLE)
    set(JVM_HOME /Users/rbe/.sdkman/candidates/java/8.0.191-oracle)
    include_directories(${JVM_HOME}/include/darwin)
    link_directories(${JVM_HOME}/jre/lib/server)
endif (APPLE)

if (WIN32)
    set(JVM_HOME C:/Program Files/Java/jdk1.8.0_191)
    include_directories(${JVM_HOME}/include/win32)
    link_directories(${JVM_HOME}/jre/bin/server)
endif (WIN32)

include_directories(${JVM_HOME}/include)

add_executable(myjni main.cpp main.hpp)
target_link_libraries(myjni jvm)

execute_process(COMMAND mkdir classes)
execute_process(COMMAND ${JVM_HOME}/bin/javac -d classes ../Demo.java WORKING_DIRECTORY .)
execute_process(COMMAND mkdir jars)
execute_process(COMMAND ${JVM_HOME}/bin/jar cf ../jars/Demo.jar Demo.class WORKING_DIRECTORY classes)

