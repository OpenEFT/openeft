
# 
# Configuration for all sub-projects
# 

# Generate version-header
configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME}/${META_PROJECT_NAME}-version.h)
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/${META_PROJECT_NAME}-version.h)

# 
# Sub-projects
# 

# Libraries
set(IDE_FOLDER "")

# Tests
if(OPTION_BUILD_TESTS)
    set(IDE_FOLDER "Tests")
    add_subdirectory(tests)
endif()

#  The main openeft executableRA
add_executable( openeft
    openeft.cpp
    openeft.h
)

# 
# Deployment
# 

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
