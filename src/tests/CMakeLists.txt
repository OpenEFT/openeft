
#
# Configure test project and environment
#

# CMake version
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Meta information about the project
set(META_PROJECT_NAME "openeft")

# Declare project
project("${META_PROJECT_NAME}-tests" C CXX)

# Set policies
set_policy(CMP0028 NEW) # ENABLE  CMP0028: Double colon in target name means ALIAS or IMPORTED target.
set_policy(CMP0054 NEW) # ENABLE  CMP0054: Only interpret if() arguments as variables or keywords when unquoted.
set_policy(CMP0042 NEW) # ENABLE  CMP0042: MACOSX_RPATH is enabled by default.
set_policy(CMP0063 NEW) # ENABLE  CMP0063: Honor visibility properties for all target types.
set_policy(CMP0037 OLD) # DISABLE CMP0037: Target names should not be reserved and should match a validity pattern.

# Compiler settings and options

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CompileOptions.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Custom.cmake)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")
else()
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompileOptions.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Custom.cmake)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()


