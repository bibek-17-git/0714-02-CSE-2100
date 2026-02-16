cmake_minimum_required(VERSION 3.10)

project(SmartBackupUtility)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/main.cpp
    src/backup.cpp
    src/restore.cpp
)

# Include directories
include_directories(include)

# Create executable
add_executable(SmartBackupUtility ${SOURCES})