#!/usr/bin/python

import os,sys
from subprocess import Popen, STDOUT, PIPE
from os.path import basename

# make sure xsd2thrift-1.0-onejar.jar is in the path

folder = './'
for filename in os.listdir(folder):
    if filename.endswith('.xsd'):
        print('java -jar xsd2thrift-1.0-onejar.jar --protobuf ./' + filename + ' > ./' + os.path.splitext(filename)[0] + '.proto')
        handle = Popen('java -jar xsd2thrift-1.0-onejar.jar --protobuf ./' + filename + ' > ./' + os.path.splitext(filename)[0] + '.proto', shell=True, stdout=PIPE, stderr=STDOUT, stdin=PIPE)
        print(handle.stdout.read())
