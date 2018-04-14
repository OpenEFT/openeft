
# 
# Configuration for all sub-projects
# 

# Generate version-header
configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME}/${META_PROJECT_NAME}-version.h)
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/${META_PROJECT_NAME}-version.h)

IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/WX" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

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
    "eftclass.h"
    "eftclass.cpp"
    "global.h"
    "openeft-version.h"
    "openeft.cpp"
    "openeft.h"
    "comms/*.h"
    "comms/*.cpp"
    "config/*.h"
    "config/*.cpp"
    "control/*.h"
    "control/*.cpp"
    "log/*.h"
    "log/*.cpp"
    "utils/*.cpp"
    "utils/*.h"
    "tests/*.cpp"
    "tests/*.h"
)

file(GLOB openeft_cli_src
    "eftclass.h"
    "eftclass.cpp"
    "global.h"
    "openeft-version.h"
    "openeft_cli.cpp"
    "openeft_cli.h"
    "comms/*.h"
    "comms/*.cpp"
    "config/*.h"
    "config/*.cpp"
    "control/*.h"
    "control/*.cpp"
    "log/*.h"
    "log/*.cpp"
    "utils/*.cpp"
    "utils/*.h"
    "tests/*.cpp"
    "tests/*.h"
)


set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
find_package(Boost 1.66.0 COMPONENTS
        date_time
        filesystem
        thread
        system
        regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIRS})
endif()
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
find_package(GRPC REQUIRED)
include_directories(${GRPC_INCLUDE_DIR})

file(GLOB CONTROL_PROTOS
    "${CMAKE_CURRENT_SOURCE_DIR}/control/protos/*.proto")
file(GLOB ISO20022_PROTOS
    "${CMAKE_CURRENT_SOURCE_DIR}/transaction/iso20022/protos/*.proto")

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto_src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
set(PROTO_SRC_DIR_CTRL ${CMAKE_CURRENT_BINARY_DIR}/proto_src/control)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR_CTRL})
set(PROTO_SRC_DIR_ISO20022 ${CMAKE_CURRENT_BINARY_DIR}/proto_src/iso_20022)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR_ISO20022})

include_directories(${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR_CTRL})
include_directories(${PROTO_SRC_DIR_ISO20022})

if(CONTROL_PROTOS)
foreach(PROTO ${CONTROL_PROTOS})
protobuf_generate_cpp(CONTROL_PROTO_SRCS CONTROL_PROTO_HDRS ${PROTO_SRC_DIR_CTRL} ${PROTO})
grpc_generate_cpp(CONTROL_GRPC_SRCS CONTROL_GRPC_HDRS ${PROTO_SRC_DIR_CTRL} ${PROTO})
endforeach()
endif()
if(ISO20022_PROTOS)
foreach(PROTO ${ISO20022_PROTOS})
protobuf_generate_cpp(ISO20022_PROTO_SRCS ISO20022_PROTO_HDRS ${PROTO_SRC_DIR_ISO20022} ${PROTO})
grpc_generate_cpp(ISO20022_GRPC_SRCS ISO20022_GRPC_HDRS ${PROTO_SRC_DIR_ISO20022} ${PROTO})
endforeach()
endif()
#  The main openeft executable
add_executable(openeft
    ${openeft_src} ${CONTROL_PROTO_SRCS} ${CONTROL_GRPC_SRCS} ${ISO20022_PROTO_SRCS} ${ISO20022_GRPC_SRCS}
    )
target_link_libraries(openeft
   ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${PROTOBUF_LIBRARY} ${GRPC_LIBRARY})

#  The main openeft executable
add_executable(openeft-cli
    ${openeft_cli_src} ${CONTROL_PROTO_SRCS} ${CONTROL_GRPC_SRCS}
    )
target_link_libraries(openeft-cli
   ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${PROTOBUF_LIBRARY} ${GRPC_LIBRARY})


# 
# Deployment
# 

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
