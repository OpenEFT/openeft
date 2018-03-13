# OpenEFT project

OpenEFT is an open source decentralized electronic financial transaction processing system based on 
EFT protocol.

OpenEFT daemon provides following features:
 * Cross Platform
  * Linux
  * Mac
  * Windows

## Programing language
C++ programming lanaguage is used in openeft development.

## Compile and build
Run following commands in bash/console to build the project:
  * "cmake -H. -Bbuild"
  * "cmake --build build -- -j3"

## IDE support
OpenEFT can be imported to any IDEs that are capable of parsing cmake configuration files.
 * Import to Netbeans:
    - In the new project pane, choose C/C++ from existing source code and specify the project path.
    - Right-click on the openeft project in the project pane, click properties and change the working
        directory in Pre-Build and Make configurations to "build/" .
    - Make sure you run execute 'cmake -H. -Bbuild' in bash/console after making any changes in 
        cmake configuration files in the project.
