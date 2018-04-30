# OpenEFT project

OpenEFT is an open source decentralized electronic financial transaction processing system.

OpenEFT daemon provides following features:
 * Cross Platform
    - Linux
    - Mac
    - Windows
 * Crypto-asset driven
 * Smart contract

## Programing language
C++ programming language is used in openeft development.

## Compile and build
Run following commands in bash/console to build the project:
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
