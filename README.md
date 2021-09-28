# OpenEFT project

OpenEFT is an open source electronic financial transaction processing system.

OpenEFT daemon provides following major features:
 * Cross Platform
    - Linux
    - Mac
    - Windows
 * Eftpos, ATM, POS payment gateway
 * Crypto Asset
 * Smart Contract
 * Tokenization
 * Payment protocol conversion
 * Data collection and analythics

 ## Official links
https://www.macronodes.com/ <br />


## Programing language
C++ programming language is used in development of openeft.

## Compile and build
Run following commands in bash/console to build the project:
  * Minimum required development libraries
    - Boost 1.66.0
    - OpenSSL 1.0.2g
    - RocksDb 5.12.4
    - Protobuf 3.5.1
    - GRPC 1.12.0
      - https://github.com/grpc/grpc/blob/master/BUILDING.md
    - Cmake 3.9.1
    - GCC 7.2.0

  * "cmake -H. -Bbuild"
  * "cmake --build build -- -j3"
  * Make sure you run execute 'cmake -H. -Bbuild' in bash/console after making any changes in 
    cmake configuration files in the project.
  * Make sure to always add unnecessary IDE files, temporary auto generated files, etc to .gitignore
    and be cautious to keep a clean git repository.

## IDE support
OpenEFT can be imported to any IDEs that are capable of parsing cmake configuration files.
Make sure that .editorconfig is correctly read by the IDE. You can test TAB and indentations
    to verify it.
 * Import to Netbeans:
    - In the new project pane, choose C/C++ from existing source code and specify the project path.
    - Right-click on the openeft project in the project pane, click properties and change the working
      directory in Pre-Build and Make configurations to "build/".
 * Import to VS Code:
    - Open VS code in Linux, click on File, Add Folder to Workspace. Select openeft root directory.
      Save the workspace inside the root directory by clicking on File/Save Workspace As.
    - Install VS code plugins for C/C++, python, git etc support.

## List of output products
  * openeft
    - Main daemon that represents a full node in an EFT network.
  * eftconsole
    - Secure permissive access to a full node to perform administrative and reporting tasks.
  * openeft-cli
    - Peer client application. Can perform all sort of financial interactions within the EFT network.
    - It can also represent a full-featured openeft wallet.
  * eftminer
    - OpenEFT mining application.

## How to join the OpenEFT development team
There are a number of ways to contribute to the project without joining the development team. We welcome such contributions:
  * Bug fixes and enhancements to the code and documentation can be submitted via GitHub as issues or pull requests.
  * We are always looking for good people to help us build up the information held in our wiki. Documentation if a crucial area for us to improve. Please contact to info@openeft.org for details on how to contribute to the project's documentation.
  
## Sponsors
Macronodes PTY LTD 
L32 101 Miller St. North Sydney, NSW 2060 Australia

## Contributors
Reza Shadmani
info@macronodes.com

