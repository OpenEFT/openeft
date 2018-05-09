# Extend this file to cover clean ups for all temporary files.
# Please pay extra attentions to test this file before any usage as you might
# inadvertently remove source files. 

import os

ANSI_COLOR_GREEN = "\x1b[32m"
ANSI_COLOR_RESET = "\x1b[0m"

def scandirs(path):
    for root, dirs, files in os.walk(path):
        for currentFile in files:
            exts = ('.pb.h', '.pb.cc') # Only protobuf files
            if any(currentFile.lower().endswith(ext) for ext in exts):
                os.remove(os.path.join(root, currentFile))
                print "Removing " + ANSI_COLOR_GREEN + (os.path.join(root, currentFile)) + ANSI_COLOR_RESET

scandirs('src/')