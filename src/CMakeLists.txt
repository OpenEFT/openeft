
# 
# Configuration for all sub-projects
# 

# Generate version-header
configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME}/${META_PROJECT_NAME}-version.h)
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/${META_PROJECT_NAME}-version.h)


SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lboost_system")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Libraries
set(IDE_FOLDER "")

# Tests
if(OPTION_BUILD_TESTS)
    set(IDE_FOLDER "Tests")
    add_subdirectory(tests)
endif()

file(GLOB openeft_src
    "*.h"
    "*.cpp"
    "config/*.h"
    "config/*.cpp"
    "control/*.h"
    "control/*.cpp"
    "log/*.h"
    "log/*.cpp"
)


set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.58.0 REQUIRED date_time filesystem system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    #  The main openeft executableRA
    add_executable(openeft
        ${openeft_src}
        )
    target_link_libraries(openeft ${Boost_LIBRARIES})
endif()

# 
# Deployment
# 

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
