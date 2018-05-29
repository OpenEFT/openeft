
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
    "blockchain/*.cpp"
    "blockchain/*.h"
    "blockchain/backends/*.cpp"
    "blockchain/backends/*.h"
    "comms/*.h"
    "comms/*.cpp"
    "config/*.h"
    "config/*.cpp"
    "control/*.h"
    "control/*.cpp"
    "kernel/*.h"
    "kernel/*.cpp"
    "log/*.h"
    "log/*.cpp"
    "network/*.h"
    "network/*.cpp"
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
    "kernel/*.h"
    "kernel/*.cpp"
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
find_package(RocksDb REQUIRED)
if(ROCKSDB_FOUND)
    include_directories(${ROCKSDB_INCLUDE_DIRS})
endif()
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
find_package(GRPC REQUIRED)
include_directories(${GRPC_INCLUDE_DIR})

set(PROTO_SRC_DIR_CTRL "${CMAKE_CURRENT_SOURCE_DIR}/control/protos")
set(PROTO_SRC_DIR_BLOCKCHAIN "${CMAKE_CURRENT_SOURCE_DIR}/blockchain/protos")
set(PROTO_SRC_DIR_EFT "${CMAKE_CURRENT_SOURCE_DIR}/transaction/eft/protos")
set(PROTO_SRC_DIR_ISO20022 "${CMAKE_CURRENT_SOURCE_DIR}/transaction/iso20022/protos")
set(PROTO_SRC_DIR_FIX "${CMAKE_CURRENT_SOURCE_DIR}/transaction/fix/protos")
set(PROTO_SRC_DIR_KERNEL "${CMAKE_CURRENT_SOURCE_DIR}/kernel/protos")
set(PROTO_SRC_DIR_NETWORK "${CMAKE_CURRENT_SOURCE_DIR}/network/protos")

set(GRPC_GENERATE_CPP_APPEND_PATH FALSE)
set(PROTOBUF_GENERATE_CPP_APPEND_PATH FALSE)

include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB CONTROL_PROTOS
    "${PROTO_SRC_DIR_CTRL}/*.proto")
file(GLOB BLOCKCHAIN_PROTOS
    "${PROTO_SRC_DIR_BLOCKCHAIN}/*.proto")
file(GLOB EFT_PROTOS
    "${PROTO_SRC_DIR_EFT}/*.proto")
file(GLOB ISO20022_PROTOS
    "${PROTO_SRC_DIR_ISO20022}/*.proto")
file(GLOB FIX_PROTOS
    "${PROTO_SRC_DIR_FIX}/*.proto")
file(GLOB KERNEL_PROTOS
    "${PROTO_SRC_DIR_KERNEL}/*.proto")
file(GLOB NETWORK_PROTOS
    "${PROTO_SRC_DIR_NETWORK}/*.proto")

if(KERNEL_PROTOS)
foreach(PROTO ${KERNEL_PROTOS})
protobuf_generate_cpp(KERNEL_PROTO_SRCS KERNEL_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(KERNEL_GRPC_SRCS KERNEL_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${KERNEL_PROTO_SRCS})
list(APPEND proto_list ${KERNEL_GRPC_SRCS})
endforeach()
endif()
if(CONTROL_PROTOS)
foreach(PROTO ${CONTROL_PROTOS})
protobuf_generate_cpp(CONTROL_PROTO_SRCS CONTROL_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(CONTROL_GRPC_SRCS CONTROL_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${CONTROL_PROTO_SRCS})
list(APPEND proto_list ${CONTROL_GRPC_SRCS})
endforeach()
endif()
if(BLOCKCHAIN_PROTOS)
foreach(PROTO ${BLOCKCHAIN_PROTOS})
protobuf_generate_cpp(BLOCKCHAIN_PROTO_SRCS BLOCKCHAIN_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(BLOCKCHAIN_GRPC_SRCS BLOCKCHAIN_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${BLOCKCHAIN_PROTO_SRCS})
list(APPEND proto_list ${BLOCKCHAIN_GRPC_SRCS})
endforeach()
endif()
if(EFT_PROTOS)
foreach(PROTO ${EFT_PROTOS})
protobuf_generate_cpp(EFT_PROTO_SRCS EFT_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(EFT_GRPC_SRCS EFT_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${EFT_PROTO_SRCS})
list(APPEND proto_list ${EFT_GRPC_SRCS})
endforeach()
endif()
if(ISO20022_PROTOS)
foreach(PROTO ${ISO20022_PROTOS})
protobuf_generate_cpp(ISO20022_PROTO_SRCS ISO20022_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(ISO20022_GRPC_SRCS ISO20022_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${ISO20022_PROTO_SRCS})
list(APPEND proto_list ${ISO20022_GRPC_SRCS})
endforeach()
endif()
if(FIX_PROTOS)
foreach(PROTO ${FIX_PROTOS})
protobuf_generate_cpp(FIX_PROTO_SRCS FIX_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(FIX_GRPC_SRCS FIX_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${FIX_PROTO_SRCS})
list(APPEND proto_list ${FIX_GRPC_SRCS})
endforeach()
endif()
if(NETWORK_PROTOS)
foreach(PROTO ${NETWORK_PROTOS})
protobuf_generate_cpp(NETWORK_PROTO_SRCS NETWORK_PROTO_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
grpc_generate_cpp(NETWORK_GRPC_SRCS BLOCKCHAIN_GRPC_HDRS ${CMAKE_CURRENT_LIST_DIR} ${PROTO})
list(APPEND proto_list ${NETWORK_PROTO_SRCS})
list(APPEND proto_list ${NETWORK_GRPC_SRCS})
endforeach()
endif()


#  The main openeft executable
add_executable(openeft
    ${openeft_src} ${proto_list}
    )
target_link_libraries(openeft
   ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${PROTOBUF_LIBRARY} ${ROCKSDB_LIBRARY} gRPC::grpc++_reflection)

#  The main openeft-cli executable
add_executable(openeft-cli
    ${openeft_cli_src} ${proto_list} 
    )
target_link_libraries(openeft-cli
   ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${PROTOBUF_LIBRARY} gRPC::grpc++_reflection)


# 
# Deployment
# 

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
